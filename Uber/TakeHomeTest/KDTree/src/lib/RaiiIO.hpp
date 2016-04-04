#ifndef _UBER_LIB_RAII_IO_H_
#define _UBER_LIB_RAII_IO_H_
#include <iostream>
#include <fstream>
#include <cassert>
#include <lib/Noncopyable.hpp>
namespace uber {
class Istream : public Noncopyable {
public:
  Istream(const std::string &filename)
      : ifstr_(filename), filename_(filename) {
    assert(ifstr_.is_open());
  }
  ~Istream() {
    ifstr_.close();
  }
  //XXX: Ideally we should override all operators what std::ifstream provides.
  std::ifstream& get() {
    return ifstr_;
  }
private:
  std::ifstream ifstr_;
  std::string filename_;
};

class Ostream : public Noncopyable {
public:
  Ostream(const std::string &filename)
      : ofstr_(filename, std::ios::out | std::ios::trunc), filename_(filename) {
  }
  ~Ostream() {
    ofstr_.close();
    //Istream istr(filename_);
    //std::ifstream &ifs = istr.get();
    //std::cout << "\n\nostream contents: " << ifs.rdbuf() << "\n";
  }
  //XXX: Ideally we should override all operators what std::ifstream provides.
  std::ofstream& get() {
    return ofstr_;
  }
private:
  std::ofstream ofstr_;
  std::string filename_;
};
};
#endif //_UBER_LIB_RAII_IO_H_
