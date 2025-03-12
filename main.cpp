#include <Windows.h>
#include <commdlg.h>
#include <string>

std::string OpenFileDialog() {
	OPENFILENAME ofn;       // コモンダイアログボックス構造体
	wchar_t szFile[260];    // ファイル名を格納するバッファ
	ZeroMemory(&ofn, sizeof(ofn));
	ofn.lStructSize = sizeof(ofn);
	ofn.hwndOwner = nullptr;
	ofn.lpstrFile = szFile;
	ofn.lpstrFile[0] = '\0';
	ofn.nMaxFile = sizeof(szFile);
	ofn.lpstrFilter = L"All\0*.*\0Text\0*.TXT\0";
	ofn.nFilterIndex = 1;
	ofn.lpstrFileTitle = nullptr;
	ofn.nMaxFileTitle = 0;
	ofn.lpstrInitialDir = nullptr;
	ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;

	if (GetOpenFileName(&ofn) == TRUE) {
		// wchar_t* から std::string への変換
		std::wstring ws(szFile);
		return std::string(ws.begin(), ws.end());
	}
	return "";
}

int main() {
	// テスト用コード
	std::string filePath = OpenFileDialog();
	if (!filePath.empty()) {
		MessageBoxA(nullptr, filePath.c_str(), "選択されたファイル", MB_OK);
	}
}