#include <string>
#include <iostream>
#include <fstream>
#include <filesystem>
#include <cstdlib>

#include "project/FactoryRegister.h"

class CreateClassFileCommand {
public:

	void Execute(const std::string& _className, const std::string& _directory = "./") {
		///< ファイル名を作成
		std::string&& headerFilepath = _directory + "/" + _className + ".h";
		std::string&& cppFilepath = _directory + "/" + _className + ".cpp";

		/// .hファイルの作成
		std::ifstream templateHeaderFile(templateHeaderFilepath_, std::ios::binary);
		std::ofstream newHeaderFile(headerFilepath, std::ios::binary);
		std::string headerContent((std::istreambuf_iterator<char>(templateHeaderFile)), std::istreambuf_iterator<char>());
		size_t pos = 0;
		while ((pos = headerContent.find("Template", pos)) != std::string::npos) {
			headerContent.replace(pos, 8, _className);
			pos += _className.length();
		}
		newHeaderFile << headerContent;

		///< cppファイルの作成
		std::ifstream templateCppFile(templateCppFilepath_, std::ios::binary);
		std::ofstream newCppFile(cppFilepath, std::ios::binary);
		std::string cppContent((std::istreambuf_iterator<char>(templateCppFile)), std::istreambuf_iterator<char>());
		pos = 0;
		while ((pos = cppContent.find("Template", pos)) != std::string::npos) {
			cppContent.replace(pos, 8, _className);
			pos += _className.length();
		}
		newCppFile << cppContent;

		system("premake5 vs2022");
	}

private:
	std::string templateHeaderFilepath_ = "./project/Template.h";
	std::string templateCppFilepath_ = "./project/Template.cpp";

	std::string projectStr = "2024_PG3";

	void AddFileToProject(const std::string& filepath) {
		// premakeを使用してプロジェクトファイルにファイルを追加する処理をここに実装
		std::string command = "premake5 --file=premake5.lua vs2019";
		if (std::system(command.c_str()) != 0) {
			std::cerr << "premakeコマンドの実行に失敗しました: " << command << std::endl;
		}
	}
};

void ModifyFactoryRegister(const std::string& filePath, const std::string& includePath, const std::string& registerCall) {
	std::ifstream inFile(filePath);
	if (!inFile) {
		std::cerr << "ファイルを開けませんでした: " << filePath << std::endl;
		return;
	}

	std::string fileContent;
	std::string line;
	bool includeAdded = false;
	bool registerAdded = false;

	while (std::getline(inFile, line)) {
		// `/// include` の直後に `#include` を追加
		if (line.find("/// include") != std::string::npos && !includeAdded) {
			fileContent += line + "\n";
			fileContent += "#include \"" + includePath + "\"\n";
			includeAdded = true;
			continue;
		}

		// `void FactoryRegister::Registers()` の中に処理を追加
		if (line.find("void FactoryRegister::Registers() {") != std::string::npos && !registerAdded) {
			fileContent += line + "\n";
			fileContent += "    " + registerCall + ";\n";
			registerAdded = true;
			continue;
		}

		fileContent += line + "\n";
	}

	inFile.close();

	// ファイルを上書き
	std::ofstream outFile(filePath);
	if (!outFile) {
		std::cerr << "ファイルを書き込めませんでした: " << filePath << std::endl;
		return;
	}
	outFile << fileContent;
	outFile.close();
}

int main() {

	FactoryRegister factory;
	factory.Registers();
	CreateClassFileCommand command;

	auto CreateAndRegisterMesthodCreate = [&factory, &command](const std::string& _className) {
		command.Execute(_className, "./project/createClass");
		ModifyFactoryRegister("./project/FactoryRegister.cpp", "./createClass/" + _className + ".h", "factory_.Register<" + _className + ">()");
	};

	while (true) {
		std::string className;
		std::cout << "クラス名を入力してください (終了するには 'exit' と入力): ";
		std::cin >> className;

		if (className == "exit") {
			break;
		}

		CreateAndRegisterMesthodCreate(className);
	}

	return 0;
}
