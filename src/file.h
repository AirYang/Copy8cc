#include <ctime>

#include <memory>
#include <string>
#include <vector>

#ifndef SRC_FILE_
#define SRC_FILE_

class File {
 public:
  File(const std::string& name);
  File(const std::vector<char>& buffer);

 public:
  static void streamStash(std::shared_ptr<File> f);
  static void streamUnstash();
  static void streamPush(std::shared_ptr<File> f);
  static std::shared_ptr<File> currentFile();
  static size_t streamDepth();
  static void unreadc(char c);
  static char readc();
  static std::string getPosition();

 private:
  static char get();

 private:
  std::vector<char> buffer_;
  std::string name_;
  size_t line_;
  size_t column_;
  size_t ntok_;
  char last_;
  time_t mtime_;

 private:
  static std::vector<std::shared_ptr<File>> files_;
  static std::vector<std::vector<std::shared_ptr<File>>> stashed_;
};

#endif  // SRC_FILE_