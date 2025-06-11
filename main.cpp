
/// std
#include <iostream>
#include <vector>
#include <unordered_map>

/// externals
#include "Externals/mono/jit/jit.h"
#include "Externals/mono/metadata/assembly.h"
#include "Externals/mono/metadata/debug-helpers.h"



// グローバル変数でMonoの状態を保持
MonoObject* playerInstance = nullptr;
MonoMethod* updateMethod = nullptr;


struct Script {
	MonoClass* monoClass;
	MonoObject* instance;
	
	MonoMethod* initMethod = nullptr;
	MonoMethod* updateMethod = nullptr;
};


class ScriptManager {

	MonoDomain* domain;
	MonoImage* image;
	MonoAssembly* assembly = nullptr;
	std::vector<Script> scripts;

public:

	void Initialize() {
		mono_set_dirs("./Externals/mono/lib", "./Externals/mono/etc");
		domain = mono_jit_init("MyDomain");
		if (!domain) {
			std::cerr << "Failed to initialize Mono JIT" << std::endl;
			return;
		}

		assembly = mono_domain_assembly_open(domain, "./Resources/CSharpLibrary.dll");
		if (!assembly) {
			std::cerr << "Failed to load CSharpLibrary.dll" << std::endl;
			return;
		}

		image = mono_assembly_get_image(assembly);
		if (!image) {
			std::cerr << "Failed to get image from assembly" << std::endl;
			return;
		}
	}

	void Finalize() {
		if (domain) {
			mono_jit_cleanup(domain);
			domain = nullptr;
		}
		scripts.clear();
	}

	void AddScript(const std::string& _className) {

		/// MonoImageから指定されたクラスを取得(namespaceは""で省略)
		MonoClass* monoClass = mono_class_from_name(image, "", _className.c_str());
		if (!monoClass) {
			std::cerr << "Failed to find class: " << _className << std::endl;
			return;
		}

		/// クラスのインスタンスを生成
		MonoObject* obj = mono_object_new(domain, monoClass);
		mono_runtime_object_init(obj); /// クラスの初期化、コンストラクタをイメージ


		/// 先に定義しておく
		MonoMethodDesc* desc = nullptr;

		/// Updateメソッドを取得
		desc = mono_method_desc_new(":Initialize()", false);
		MonoMethod* initMethod = mono_method_desc_search_in_class(desc, monoClass);
		mono_method_desc_free(desc);
		if (!initMethod) {
			std::cerr << "Failed to find method Initialize in class: " << _className << std::endl;
			return;
		}

		/// Updateメソッドを取得
		desc = mono_method_desc_new(":Update()", false);
		MonoMethod* updateMethod = mono_method_desc_search_in_class(desc, monoClass);
		mono_method_desc_free(desc);

		if (!updateMethod) {
			std::cerr << "Failed to find method Update in class: " << _className << std::endl;
			return;
		}

		if (initMethod && obj) {
			mono_runtime_invoke(initMethod, obj, nullptr, nullptr);
		}

		scripts.push_back({ monoClass, obj, initMethod, updateMethod });
	}


	void UpdateAll() {
		for (auto& script : scripts) {
			if (script.updateMethod && script.instance) {
				mono_runtime_invoke(script.updateMethod, script.instance, nullptr, nullptr);
			}
		}
	}

};


ScriptManager scriptManager;

// 初期化処理（一度だけ呼ぶ）
void InitializeMono() {
	scriptManager.Initialize();

	scriptManager.AddScript("Player");
	scriptManager.AddScript("Enemy");

}

// 毎フレーム呼ぶ更新処理
void Update() {
	scriptManager.UpdateAll();
}

// 終了処理（一度だけ呼ぶ）
void ShutdownMono() {
	scriptManager.Finalize();
}

int main() {
	InitializeMono();

	// ゲームループ的に何度もUpdateを呼ぶ例（ここでは3回だけ）
	for (int i = 0; i < 3; ++i) {
		Update();
	}

	ShutdownMono();
	return 0;
}
