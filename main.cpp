#include <algorithm>
#include <fstream>
#include <iostream>
#include <map>
#include <string>
#include <vector>
//
// using Key = std::pair<int, int>;
// using Map = std::map<Key, int>;
//
// void print(const Map& m) {
//  for (auto& [key, value] : m) {
//    std::cout << "Key: (" << key.first << ", " << key.second
//              << "), Value: " << value << std::endl;
//  }
//}
//
// int main(void) {
//  Map map;
//  map[std::make_pair(1, 2)] = 3;
//  map[std::make_pair(4, 5)] = 6;
//  map[std::make_pair(7, 8)] = 9;
//
//  print(map);
//
//  return 0;
//}

// class A {
//  public:
//   A() { printf("A::A()\n"); }
// };
//
// class B {
//  public:
//   B() { printf("B::B()\n"); }
// };
// class C : public A, public B {
//  public:
//   C() { printf("C::C()\n"); }
// };
//
// int main() {
//   C c;
//   return 0;
// }

/// ファイル数をカウントする

#include <filesystem>
#include <iostream>

namespace fs = std::filesystem;

class FileCounter {
 public:
  FileCounter() : count_(0), total_lines_(0) {}

  int count() const { return count_; }
  long long totalLines() const { return total_lines_; }
  void reset() {
    count_ = 0;
    total_lines_ = 0;
    extensions_.clear();
  }

  void addExtension(const std::string& ext) {
    // 拡張子は小文字/大文字の区別をそのまま扱うが、必要なら正規化可能
    extensions_.push_back(ext);
  }

  void countFilesWithExtensions(const fs::path& root) {
    try {
      if (!fs::exists(root)) {
        std::cerr << "Path does not exist: " << root << '\n';
        return;
      }

      // 再帰的に走査
      for (auto const& entry : fs::recursive_directory_iterator(
               root, fs::directory_options::skip_permission_denied)) {
        try {
          if (!entry.is_regular_file()) continue;

          std::string ext = entry.path().extension().string();
          if (std::find(extensions_.begin(), extensions_.end(), ext) !=
              extensions_.end()) {
            ++count_;
            long long lines = countLinesInFile(entry.path());
            total_lines_ += lines;
          }
        } catch (const fs::filesystem_error& e) {
          // 個々のエントリでアクセスエラーなどが起きた場合は警告を出して続行
          std::cerr << "Filesystem error for entry: " << e.what() << '\n';
        }
      }
    } catch (const fs::filesystem_error& e) {
      std::cerr << "Failed to iterate directory: " << e.what() << '\n';
    }
  }

 private:
  long long countLinesInFile(const fs::path& filepath) {
    std::ifstream ifs(filepath, std::ios::in);
    if (!ifs) {
      std::cerr << "Failed to open file: " << filepath << '\n';
      return 0;
    }
    long long lines = 0;
    std::string line;
    while (std::getline(ifs, line)) {
      ++lines;
    }
    return lines;
  }

  int count_;
  long long total_lines_;
  std::vector<std::string> extensions_;
};

int main(int argc, char* argv[]) {
  FileCounter counter;
  counter.addExtension(".cpp");
  counter.addExtension(".h");
  // counter.addExtension(".hpp");
  // counter.addExtension(".c");
  // counter.addExtension(".txt");  // 必要なら追加

  fs::path target;
  if (argc > 1) {
    target = fs::path(argv[1]);
  } else {
    // デフォルトパスを必要に応じて変更してください
    target = "C:\\Users\\k023g\\source\\repos\\ONEngine\\Project\\Engine";
  }

  counter.countFilesWithExtensions(target);

  std::cout << "Number of matching files: " << counter.count() << std::endl;
  std::cout << "Total lines across matched files: " << counter.totalLines()
            << std::endl;

  return 0;
}