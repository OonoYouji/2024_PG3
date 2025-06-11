#include "Externals/Lua/src/lua.hpp"
//#include "Externals/sol/sol.hpp"
#include <string>


struct Transform {
	float x, y, z;
};



int main() {
	lua_State* L = luaL_newstate();       // Luaインタープリタ生成
	luaL_openlibs(L);                     // 標準ライブラリを開く


	/// Lua側にC++の構造体を登録する
	luaL_newmetatable(L, "Transform"); // メタテーブルを作成

	/// スクリプトの読み込み
	if (luaL_dofile(L, "./project/LuaScripts/script.lua") != LUA_OK) {
		const char* error = lua_tostring(L, -1);
		printf("Lua error: %s\n", error);
		lua_pop(L, 1); // エラーメッセージをスタックから除去
	}

	/// 関数をスタックにプッシュ
	lua_getglobal(L, "main"); // Luaのグローバル関数を取得

	/// 呼び出し
	if (lua_pcall(L, 0, 0, 0) != LUA_OK) { // 1つの引数、1つの戻り値
		const char* error = lua_tostring(L, -1);
		printf("Lua error: %s\n", error);
		lua_pop(L, 1); // エラーメッセージをスタックから除去
	}

	lua_close(L); // 終了処理
	return 0;
}