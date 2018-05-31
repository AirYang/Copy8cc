#include <string>

#ifndef SRC_COPY_8CC_
#define SRC_COPY_8CC_

class Copy8cc {
 public:
  Copy8cc(int argc, char** argv);

  void run();

 private:
  std::string file_;
  bool need_lexer_;
};

#endif  // SRC_COPY_8CC_