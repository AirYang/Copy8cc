#include "file.h"

#include <cassert>

#include <fstream>

std::vector<std::shared_ptr<File>> File::files_ = {};
std::vector<std::vector<std::shared_ptr<File>>> File::stashed_ = {};

File::File(const std::string& name)
    : buffer_(),
      name_(name),
      line_(1),
      column_(1),
      ntok_(0),
      last_(0),
      mtime_(time(0)) {
  std::ifstream filein(name_);
  assert(filein.is_open());
  for (char c; filein.get(c); buffer_.push_back(c))
    ;
  filein.close();
}

File::File(const std::vector<char>& buffer)
    : buffer_(buffer),
      name_(""),
      line_(1),
      column_(1),
      ntok_(0),
      last_(0),
      mtime_(time(0)) {}

void File::streamStash(std::shared_ptr<File> f) {
  stashed_.push_back(files_);
  files_.clear();
  files_.push_back(f);
}

void File::streamUnstash() {
  assert(stashed_.size() > 0);
  files_ = stashed_.back();
  stashed_.pop_back();
}

void File::streamPush(std::shared_ptr<File> f) { files_.push_back(f); }

std::shared_ptr<File> File::currentFile() {
  assert(files_.size() > 0);
  return files_.back();
}

std::string File::getPosition() {
  if (files_.size() == 0) {
    return "(unknown)";
  }
  std::shared_ptr<File> f = files_.back();
  return f->name_ + ":" + std::to_string(f->line_) + ":" +
         std::to_string(f->column_);
}

size_t File::streamDepth() { return files_.size(); }

void File::unreadc(char c) {
  if (c == EOF) {
    return;
  }
  assert(files_.size() > 0);
  std::shared_ptr<File> f = files_.back();
  f->buffer_.push_back(c);
  if (c == '\n') {
    f->column_ = 1;
    --f->line_;
  } else {
    --f->column_;
  }
}

char File::readc() {
  for (int c = get();; c = get()) {
    if (c == EOF) {
      if (files_.size() == 1) {
        return c;
      }
      files_.pop_back();
      continue;
    }

    if (c != '\\') {
      return c;
    }

    char c2 = get();
    if (c2 == '\n') {
      continue;
    }

    unreadc(c2);
    return c;
  }
}

char File::get() {
  assert(files_.size() > 0);
  std::shared_ptr<File> f = files_.back();
  char c;

  if (f->buffer_.size() > 0) {
    c = f->buffer_.back();
    f->buffer_.pop_back();
  } else {
    c = (f->last_ == EOF || f->last_ == '\n') ? EOF : '\n';
  }

  if (c == '\n') {
    f->column_ = 1;
    ++f->line_;
  } else if (c != EOF) {
    ++f->column_;
  }

  f->last_ = c;
  return c;
}
