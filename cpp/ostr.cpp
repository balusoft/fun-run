#include <sstream>
#include <iostream>
int main() {
  std::ostringstream ostr;
  ostr << "Yeah";
  if (!ostr.str().empty()) {
    std::cout << "Hell " << ostr.str();
  }
}
