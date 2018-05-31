// copy 8cc include
#include "copy_8cc.h"

// standard C
#include <cassert>
// standard C++
// other include

// this project other include
#include "para_init.h"

Copy8cc::Copy8cc(int argc, char** argv) : file_(), need_lexer_(false) {
  ParaInit pinit(argc, argv);
  file_ = pinit.getFile();
  need_lexer_ = pinit.needLexer();

  // input only *.c file
  assert((file_.size() > 1) && (file_.find_last_of(".c") == file_.size() - 1));
}

void Copy8cc::run() {}