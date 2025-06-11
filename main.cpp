
/// std
#include <iostream>
#include <vector>
#include <unordered_map>

/// externals
#include "Externals/mono/jit/jit.h"
#include "Externals/mono/metadata/assembly.h"
#include "Externals/mono/metadata/debug-helpers.h"


struct Vector3 {
	float x, y, z;
};

class Transform {
public:
	Vector3 position;
	Vector3 rotate;
	Vector3 scale;
};

class Entity {
public:
	int id;
	Transform transform;
};


std::unordered_map<int, Entity> entities;
int nextEntityId = 1;

Entity* CreateEntity() {
	Entity entity;
	entity.id = nextEntityId++;
	entity.transform.position = { 0.0f, 0.0f, 0.0f };
	entity.transform.rotate = { 0.0f, 0.0f, 0.0f };
	entity.transform.scale = { 1.0f, 1.0f, 1.0f };
	entities[entity.id] = entity;
	return &entities[entity.id];
}


extern "C" {
	Transform* Internal_GetTransform(int entityId) {
		auto it = entities.find(entityId);
		if (it != entities.end()) {
			return &it->second.transform;
		}
		return nullptr; // エンティティが見つからない場合はnullptrを返す
	}

	void Internal_SetTransform(int entityId, Transform* transform) {
		auto it = entities.find(entityId);
		if (it != entities.end()) {
			it->second.transform = *transform; // エンティティのTransformを更新
		} else {
			std::cerr << "Entity with ID " << entityId << " not found." << std::endl;
		}
	}

}


void BindInternalCalls() {
	mono_add_internal_call("ONEngine.ScriptComponent::Internal_GetTransform", (void*)Internal_GetTransform);
	mono_add_internal_call("ONEngine.ScriptComponent::Internal_SetTransform", (void*)Internal_SetTransform);
}


struct Script {

	uint32_t gcHandle;

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

		for (auto& script : scripts) {
			mono_gchandle_free(script.gcHandle);
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
		uint32_t gcHandle = mono_gchandle_new(obj, false); /// GCハンドルを取得（必要に応じて）

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

		Entity* entity = CreateEntity();
		int entityId = entity->id;


		MonoClassField* field = nullptr;
		MonoClass* currentClass = monoClass;
		while (currentClass && !field) {
			field = mono_class_get_field_from_name(currentClass, "entityId");
			currentClass = mono_class_get_parent(currentClass); // 親クラスを探索
		}

		if (field) {
			mono_field_set_value(obj, field, &entityId);
		} else {
			std::cerr << "Failed to find field entityId in class: " << _className << std::endl;
		}

		if (initMethod && obj) {
			mono_runtime_invoke(initMethod, obj, nullptr, nullptr);
		}


		scripts.push_back({ gcHandle, monoClass, obj, initMethod, updateMethod });
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
	BindInternalCalls();

	scriptManager.AddScript("Player");
	//scriptManager.AddScript("Enemy");

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
