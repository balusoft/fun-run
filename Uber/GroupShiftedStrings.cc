/*
Group Shifted Strings
Given a string, we can "shift" each of its letter to its successive letter, for
example: "abc" -> "bcd". We can keep "shifting" which forms the sequence:

"abc" -> "bcd" -> ... -> "xyz"
Given a list of strings which contains only lowercase alphabets, group all
strings that belong to the same shifting sequence.

For example, given: ["abc", "bcd", "acef", "xyz", "az", "ba", "a", "z"],
Return:

[
  ["abc","bcd","xyz"],
  ["az","ba"],
  ["acef"],
  ["a","z"]
]
Note: For the return value, each inner list's elements must follow the
lexicographic order.

Show Company Tags
Show Tags
Show Similar Problems
Have you met this question in a real interview? Yes  No
Discuss

*/

#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <unordered_map>
#include <algorithm>

std::ostream &operator<<(std::ostream &ostr,
                         const std::vector<std::string> &vs) {
  ostr << "{ ";
  for (auto& s : vs) {
    ostr << s << ", ";
  }
  ostr << "}";
  return ostr;
}
std::ostream &operator<<(std::ostream &ostr,
                         const std::vector<std::vector<std::string>> &vvs) {
  ostr << "{ ";
  for (auto& vs : vvs) {
    ostr << vs << ", \n";
  }
  ostr << "}";
  return ostr;
}
static std::string get_string_key(const std::string& st) {
  std::ostringstream ostr;
  if (st.length() <= 1) {
    return ostr.str();
  }
  for (size_t idx=1; idx<st.length(); ++idx) {
    ostr << st[idx-1] - st[idx] << ":";
  }
  return ostr.str();
}
class Solution {
public:
  std::vector<std::vector<std::string>>
  groupStrings(const std::vector<std::string> &strings) {
    typedef std::unordered_map<std::string, std::vector<std::string>>
        resMapType;
    resMapType resMap;
    for (auto& st : strings) {
      std::string key=get_string_key(st);
      if (resMap.find(key) == resMap.end()) {
        resMap[key] = { st };
      } else {
        resMap[key].push_back(st);
      }
    }
    //return resMap.values();
    std::vector<std::vector<std::string>> res;
    res.reserve(resMap.size());
    std::transform(resMap.begin(), resMap.end(), std::back_inserter(res),
              [](resMapType::value_type &val) {return val.second;});
    //for (auto &kv : resMap) {
    //  res.push_back(kv.second);
    //}
    return res;
  }
};
void test(const std::vector<std::string> &vs) {
  std::cout << "Input: " << vs << "\n";
  Solution s;
  std::cout << "Output: " << s.groupStrings(vs) << "\n";
}
int main() {
  std::vector<std::string> vs{"abc", "bcd", "acef", "xyz",
                              "az",  "ba",  "a",    "z"};
  test(vs);
  return 0;
}
