#include <iostream>
#include "nlohmann/json.hpp"

struct Vector3 {
	float x, y, z;
};

struct Vector4 {
	float x, y, z, w;
};

struct Transform {
	Vector3 position;
	Vector3 rotation;
	Vector3 scale;
};

struct Vertex {
	float height;
	Vector4 color;
};

NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(Vector3, x, y, z)
NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(Vector4, x, y, z, w)
NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(Vertex, height, color)
NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(Transform, position, scale, rotation)

//int main() {
//
//	size_t hash = typeid(Transform).hash_code();
//	size_t stringHash = std::hash<std::string>{}("Transform");
//	
//	std::string compName = typeid(Transform).name();
//	size_t pos = compName.find("struct ");
//	if (pos != std::string::npos) {
//		compName.erase(pos, std::string("struct ").length());
//	}
//	size_t compNameHash = std::hash<std::string>{}(compName);
//
//	std::cout << "Component name: " << compName << std::endl;
//
//	std::cout << "Hash of Transform type: " << hash << std::endl;
//	std::cout << "Hash of 'Transform' string: " << stringHash << std::endl;
//	std::cout << "Hash of component name: " << compNameHash << std::endl;
//
//	return 0;
//}


using json = nlohmann::json;


int main() {
	std::vector<Vertex> vertices = {
		{ 1.0f, { 1.0f, 0.0f, 0.0f, 1.0f } },
		{ 2.0f, { 0.0f, 1.0f, 0.0f, 1.0f } },
		{ 3.0f, { 0.0f, 0.0f, 1.0f, 1.0f } }
	};

	// Vertexをバイナリに変換
	std::vector<uint8_t> vec(
		reinterpret_cast<const uint8_t*>(vertices.data()),
		reinterpret_cast<const uint8_t*>(vertices.data()) + vertices.size() * sizeof(Vertex)
	);

	// バイナリをJSONに詰める
	json j;
	j["bin"] = json::binary(vec);

	std::cout << j.dump(2) << "\n";

	// BSON化 → 転送処理の代替
	std::vector<uint8_t> bson = json::to_bson(j);
	std::vector<uint8_t> bson2(bson.begin(), bson.end());

	// 復元
	json j2 = json::from_bson(bson2);
	auto bin = j2["bin"].get_binary();

	// バイナリデータを表示
	std::cout << "復元したバイナリ (byte数: " << bin.size() << "):\n";
	for (uint8_t b : bin) std::printf("%02d ", b);
	std::cout << "\n";

	return 0;
}