#include "cmd_parser.h"

#ifndef SRC_PARA_INIT_
#define SRC_PARA_INIT_

class ParaInit {
 public:
  ParaInit(int argc, char** argv);

 public:
  std::string getFile();
  bool needLexer();

 private:
  void parserInit();

 private:
  cli::Parser parser_;
};
#endif  // SRC_PARA_INIT_
