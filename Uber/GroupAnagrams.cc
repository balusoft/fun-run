/*
   49. Group Anagrams My Submissions Question
   Total Accepted: 69354 Total Submissions: 257368 Difficulty: Medium
   Given an array of strings, group anagrams together.

   For example, given: ["eat", "tea", "tan", "ate", "nat", "bat"],
Return:

[
["ate", "eat","tea"],
["nat","tan"],
["bat"]
]
Note:
For the return value, each inner list's elements must follow the lexicographic
order.
All inputs will be in lower-case.
Subscribe to see which companies asked this question

Show Tags
Show Similar Problems
Have you met this question in a real interview? Yes  No
Discuss


*/

#include <unordered_map>
#include <vector>
#include <algorithm>
#include <iostream>
#include <set>

static std::string countSort(const std::string &str) {
  std::vector<int> alpha(26, 0);
  for (auto &c : str) {
    alpha[c-'a'] += 1;
  }

  std::string out;
  for (size_t idx=0; idx<alpha.size(); ++idx) {
    if (alpha[idx] > 0) {
      out += std::string(alpha[idx], 'a' + idx);
    }
  }
  return out;
}

class Solution {
public:
  std::vector<std::vector<std::string>>
  groupAnagrams(const std::vector<std::string> &strs) {
    std::vector<std::vector<std::string>> blah;
    if (strs.empty()) {
      return blah;
    }
    typedef std::unordered_map<std::string, std::multiset<std::string>> AngMapT;
    AngMapT map;
    for (auto &s : strs) {
      std::string tmp = countSort(s);
      //std::sort(tmp.begin(), tmp.end());
      map[tmp].insert(s);
    }

    for (auto &res : map) {
      std::vector<std::string> tmp(res.second.begin(), res.second.end());
      blah.push_back(tmp);
    }
    return blah;
  }
};

std::ostream& operator<<(std::ostream &ostr,
                        const std::vector<std::string> &given) {
  ostr << "{";
  for (auto &s : given) {
    ostr << s << ", ";
  }
  ostr << "}";
  return ostr;
}

std::ostream &operator<<(std::ostream &ostr,
                         const std::vector<std::vector<std::string>> &res) {
  ostr << "{\n";
  for (auto &vs : res) {
    ostr << vs << ", \n";
  }
  ostr << "}\n";
  return ostr;
}
void test(const std::vector<std::string>& vs) {
  Solution s;
  std::cout << "Given " << vs << ":::" << s.groupAnagrams(vs) << "\n";
}

int main() {
  std::vector<std::string> vs{"eat", "tea", "tan", "ate", "nat", "bat"};
  test(vs);
}
