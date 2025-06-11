
/// std
#include <iostream>

/// externals
#include "Externals/mono/jit/jit.h"
#include "Externals/mono/metadata/assembly.h"
#include "Externals/mono/metadata/debug-helpers.h"



//int main() {
//	// 1. Monoドメインの作成
//	MonoDomain* domain = mono_jit_init("MyMonoDomain");
//
//	// 2. C#アセンブリ（exeやdll）をロード
//	MonoAssembly* assembly = mono_domain_assembly_open(domain, "SampleScript.exe");
//	if (!assembly) {
//		printf("Failed to load assembly\n");
//		return -1;
//	}
//
//	// 3. アセンブリからMonoImageを取得
//	MonoImage* image = mono_assembly_get_image(assembly);
//
//	// 4. 実行したいメソッドを取得
//	// 例: namespace=SampleNamespace, class=Program, method=Main
//	MonoMethodDesc* methodDesc = mono_method_desc_new("SampleNamespace.Program:Main", /*include_namespace=*/true);
//	MonoMethod* method = mono_method_desc_search_in_image(methodDesc, image);
//	mono_method_desc_free(methodDesc);
//
//	if (!method) {
//		printf("Failed to find method\n");
//		return -1;
//	}
//
//	// 5. メソッドの呼び出し（引数なしの場合）
//	MonoObject* exception = nullptr;
//	mono_runtime_invoke(method, nullptr, nullptr, &exception);
//
//	if (exception) {
//		printf("Exception occurred during method invoke\n");
//		return -1;
//	}
//
//	// 6. 終了処理
//	mono_jit_cleanup(domain);
//
//	return 0;
//}



int main() {
    // 初期化
    mono_set_dirs("./Externals/mono/lib", "./Externals/mono/etc"); // Monoのパスに合わせて
    MonoDomain* domain = mono_jit_init("MyDomain");

    // DLLをロード
    MonoAssembly* assembly = mono_domain_assembly_open(domain, "Player.dll");
    if (!assembly) {
        std::cerr << "Failed to load Player.dll" << std::endl;
        return 1;
    }

    // Image取得
    MonoImage* image = mono_assembly_get_image(assembly);

    // クラス取得（namespaceが空文字の場合 ""）
    MonoClass* playerClass = mono_class_from_name(image, "", "Player");
    if (!playerClass) {
        std::cerr << "Failed to find Player class" << std::endl;
        return 1;
    }

    // インスタンス作成
    MonoObject* playerInstance = mono_object_new(domain, playerClass);
    mono_runtime_object_init(playerInstance);

    // メソッド取得＆呼び出し
    MonoMethodDesc* methodDesc = mono_method_desc_new(":Update()", /*include_namespace=*/false);
    MonoMethod* method = mono_method_desc_search_in_class(methodDesc, playerClass);

    if (!method) {
        std::cerr << "Failed to find Update() method" << std::endl;
        return 1;
    }

    mono_runtime_invoke(method, playerInstance, nullptr, nullptr);
    mono_method_desc_free(methodDesc);

    // 終了処理
    mono_jit_cleanup(domain);
    return 0;
}
