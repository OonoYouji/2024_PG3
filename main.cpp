/// std
#include <string>
#include <vector>
#include <format>
#include <iostream>
#include <fstream>
#include <cassert>
#include <algorithm>


std::string LoadTxt(const std::string& _filePath);
std::string SamplingText(const std::string& _text, const std::string& _startText, const std::string& _endText);

std::vector<std::string> SplitText(const std::string& _text, char _delimiter);

void PrintStringVector(const std::vector<std::string>& _texts);

int main() {

	/// ================================================
	/// 変数宣言
	/// ================================================

	/// ファイルを読み込んで学籍番号ごとの配列を作る
	std::string loadText = LoadTxt("PG3_2024_03_02.txt");
	std::string sampleText = SamplingText(loadText, "[", "]");
	std::vector<std::string> studentIdNumbers = SplitText(sampleText, ',');

	/// ""の間の文字列を得る
	for(auto& text : studentIdNumbers) {
		text = SamplingText(text, "\"", "\"");
	}

	
	/// 学籍番号を見る
	auto ExtractId = [](const std::string& _text) -> int {
		return std::stoi(SamplingText(_text, "g", "@"));
	};

	/// 年を見る
	auto ExtractYear = [](const std::string& _text) -> int {
		return std::stoi(SamplingText(_text, "k", "g"));
	};

	std::sort(studentIdNumbers.begin(), studentIdNumbers.end(), [&](const std::string& _a, const std::string& _b) {

		/// "k022g"の部分でソート
		int aYear = ExtractYear(_a);
		int bYear = ExtractYear(_b);
		if(aYear != bYear) {
			return aYear < bYear;
		}

		
		/// "g0001@"の部分でソート
		int aId = ExtractId(_a);
		int bId = ExtractId(_b);
		return aId < bId;

	});
	



	/// 文字列配列をptintfする
	PrintStringVector(studentIdNumbers);


	return 0;
}

std::string LoadTxt(const std::string& _filePath) {
	std::ifstream file(_filePath);

	/// ファイルがなかった
	if(!file) {
		printf("no file was found...");
		assert(false);
	}

	std::string fileContents(
		(std::istreambuf_iterator<char>(file)),
		std::istreambuf_iterator<char>()
	);

	file.close();

	return fileContents;
}

std::string SamplingText(const std::string& _text, const std::string& _startText, const std::string& _endText) {

	size_t startPos = _text.find(_startText);
	/// startTextが見つからなければ引数のtextをそのまま返す
	if(startPos == std::string::npos) {
		return _text;
	}

	startPos += _startText.length();
	size_t endPos = _text.find(_endText, startPos);

	/// endTextが見つからなければ引数のtextをそのまま返す
	if(endPos == std::string::npos) {
		return _text;
	}

	return _text.substr(startPos, endPos - startPos);
}

std::vector<std::string> SplitText(const std::string& _text, char _delimiter) {
	std::vector<std::string> result;
	size_t startPos = 0;
	size_t endPos   = 0;

	while((endPos = _text.find(_delimiter, startPos)) != std::string::npos) {
		result.push_back(_text.substr(startPos, endPos - startPos));
		startPos = endPos + 1;
	}

	result.push_back(_text.substr(startPos));

	return result;
}

void PrintStringVector(const std::vector<std::string>& _texts) {
	for(auto& text : _texts) {
		printf(std::format("{}\n", text).c_str());
	}
}
