/// std
#include <list>
#include <format>

void PrintStringList(const std::list<const char*>& _stringList);


int main() {

	/// ================================================
	/// 変数宣言
	/// ================================================


	/// 2022年
	/*std::list<const char*> stations{
		"Tokyo", "Kanda", "Akihabara", "Okachimati", "Ueno",
		"Uguisudani", "Nippori", "Nishi-Nippori", "Tabata", "Komagome",
		"Sugamo", "Otsuka", "Ikebukuro", "Mejiro", "Takadanobaba", 
		"Shin-Okubo", "Shinjuku", "Yoyogi", "Harajuku", "Shibuya",
		"Ebisu", "Meguro", "Gotanda", "Osaki", "Shinagawa", 
		"Takanawa-Gateway", "Tamachi", "Hamamatsucho", "Shimbashi", "Yurakucho"
	};*/

	/// 1970
	std::list<const char*> stations{
		"Tokyo", "Kanda", "Akihabara", "Okachimati", "Ueno",
		"Uguisudani", "Nippori", "Tabata", "Komagome",
		"Sugamo", "Otsuka", "Ikebukuro", "Mejiro", "Takadanobaba", 
		"Shin-Okubo", "Shinjuku", "Yoyogi", "Harajuku", "Shibuya",
		"Ebisu", "Meguro", "Gotanda", "Osaki", "Shinagawa", 
		"Tamachi", "Hamamatsucho", "Shimbashi", "Yurakucho"
	};


	/// ================================================
	/// 実行
	/// ================================================


	/// 1970
	printf("1970 year\n");
	PrintStringList(stations);
	

	size_t nisiNipporiInsertPos = 8 - 1; 
	for(auto itr = stations.begin(); itr != stations.end();) {
		nisiNipporiInsertPos--;
		itr++;

		if(nisiNipporiInsertPos == 0) {
			stations.insert(itr, "Nisi-Nippori");
			break;
		}
	}

	printf("\n\n");


	/// 2019
	printf("2019 year\n");
	PrintStringList(stations);
	

	size_t takanawaGatewayInsertPos = 26 - 1;
	for(auto itr = stations.begin(); itr != stations.end();) {
		takanawaGatewayInsertPos--;
		itr++;

		if(takanawaGatewayInsertPos == 0) {
			stations.insert(itr, "Takanawa-Gateway");
			break;
		}
	}

	printf("\n\n");


	/// 2022
	printf("2022 year\n");
	PrintStringList(stations);

	std::list<const char*>::iterator beginItr = stations.begin();

	return 0;
}

void PrintStringList(const std::list<const char*>& _stringList) {
	uint32_t index = 1;
	for(auto& string : _stringList) {
		printf(std::format("    JY{:2}, {}\n", index, string).c_str());
		index++;
	}
}
