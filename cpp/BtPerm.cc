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

void backtrack(
  std::vector<uint32_t> &perm,
  std::vector<bool> &inUse,
  uint32_t &level,
  std::vector<std::vector<uint32_t>> &solutions) {
  if (perm.size()-1 == level) {
    solutions.push_back(perm);
  } else {
    NextNumsItr itr(inUse);
    ++level;
    while (itr.next()) {
      perm[level] = *itr;
      inUse[*itr] = true;
      backtrack(perm, inUse, level, solutions);
      perm[level] = 0;
      inUse[*itr] = false;
    }
    --level;
  }
}

void genPerm(uint32_t num) {
  std::vector<std::vector<uint32_t>> perms;
  // discard '0' to avoid nastiness
  std::vector<uint32_t> perm(num+1, 0);
  std::vector<bool> inUse(num+1, false);
  uint32_t level=0;
  backtrack(perm, inUse, level, perms);
  for (const std::vector<uint32_t> &perm : perms) {
    for (uint32_t val : perm) {
      std::cout << val << " ";
    }
    std::cout << "\n";
  }
}

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
  genPerm(3);
  return 0;
  {
    const std::vector<bool> inUse = {false/*disc*/, false, true, false, true, false, false, true, false, false, true, false, false};
    print_next_nums(inUse);
  }

  {
    const std::vector<bool> inUse = {false/*disc*/, false, true, false};
    print_next_nums(inUse);
  }
}

#if 0
balajis-mbp:CPP Test9 balajicherukuri$ clang++ -g  -std=c++11 BtPerm.cc  && valgrind ./a.out
==60021== Memcheck, a memory error detector
==60021== Copyright (C) 2002-2015, and GNU GPL'd, by Julian Seward et al.
==60021== Using Valgrind-3.11.0 and LibVEX; rerun with -h for copyright info
==60021== Command: ./a.out
==60021==
0 1 2 3
0 1 3 2
0 2 1 3
0 2 3 1
0 3 1 2
0 3 2 1
==60021==
==60021== HEAP SUMMARY:
==60021==     in use at exit: 26,203 bytes in 192 blocks
==60021==   total heap usage: 275 allocs, 83 frees, 32,595 bytes allocated
==60021==
==60021== LEAK SUMMARY:
==60021==    definitely lost: 0 bytes in 0 blocks
==60021==    indirectly lost: 0 bytes in 0 blocks
==60021==      possibly lost: 0 bytes in 0 blocks
==60021==    still reachable: 4,096 bytes in 1 blocks
==60021==         suppressed: 22,107 bytes in 191 blocks
==60021== Rerun with --leak-check=full to see details of leaked memory
==60021==
==60021== For counts of detected and suppressed errors, rerun with: -v
==60021== ERROR SUMMARY: 0 errors from 0 contexts (suppressed: 0 from 0)
balajis-mbp:CPP Test9 balajicherukuri$
#endif
