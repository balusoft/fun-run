/**
 * Goal of this is to generalte all permutations of number say 123.
 * Here input is say integer '3', then possible outcome should be
 * 123, 132, 213, 231, 312, 321
 */

#include <iostream>
#include <cassert>
#include <vector>

// API to provide next_numbers, say current num is 1 then next possible numbers
// are 2, 3, in other words all possible numbers from 1 to n except given number
// Here we can use iterator pattern rather returning whole vector. This design
// will ensure we are not creating 'n' sized array

// we need to implement operators: */get, begin(), next()
class NextNumsItr {
public:
  NextNumsItr(const std::vector<bool>& inUse)
    : _inUse(inUse), _curNum(0) {
  }
  uint32_t operator*() const {
    return _curNum;
  }
  bool next() {
    uint32_t tmp = _curNum + 1;
    // skp n'th number
    while (tmp < _inUse.size() && _inUse[tmp]) {
      ++tmp;
    }
    if (tmp >= _inUse.size()) {
      return false;
    }
    _curNum = tmp;
    return true;
  }
private:
  const std::vector<bool>& _inUse;
  uint32_t _curNum;
};

void print_next_nums (const std::vector<bool>& inUse) {
  NextNumsItr itr(inUse);
  std::cout << "inUse: ";
  for (size_t idx=1; idx<inUse.size(); ++idx)  {
    std::cout << std::boolalpha << idx << ":" << inUse[idx] << " ";
  }
  std::cout << ":: ";
  while (itr.next()) {
    std::cout << *itr << " ";
  }
  std::cout << "\n";
}

int main() {
  {
    const std::vector<bool> inUse = {false/*disc*/, false, true, false, true, false, false, true, false, false, true, false, false};
    print_next_nums(inUse);
  }

  {
    const std::vector<bool> inUse = {false/*disc*/, false, true, false};
    print_next_nums(inUse);
  }
}
