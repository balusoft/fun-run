/**
Given two strings S and T, determine if they are both one edit distance apart.

**/

class Solution {
public:
  bool isOneEditDistance(string s, string t) {
    /**
     * ab
     * abc
     *
     *  bc
     * abc
     *
     * xyz
     * ayz
     *
     * abcdabcde
     * abcdxabcde
     * s(i), t(i+1)
     *
     * s: abcdabcd
     * t: abddbcd
     *  s(i+1), t(i) ==
     *
     * abcdabcd
     * abcdxbcd
     *
     * s(i+1), t(i+1)
     *
     * abcxb
     * abcyb
     *
     * ""
     * "a"
     */
    int slen = s.length();
    int tlen = t.length();
    if (s.empty() && t.empty()) {
      return false;
    }
    if (abs(slen - tlen) > 1) {
      return false;
    }
    // Now strings should be having only one mismatch otherwise throw false.
    // First move till the first difference
    int i = 0;
    for (; i < slen && i < tlen && s[i] == t[i]; ++i) {
    }
    // Now we have only one difference
    if (i == slen || i == tlen) {
      return slen != tlen;
    }
    if (slen > tlen) {
      return (s.substr(i + 1) == t.substr(i));
    } else if (slen < tlen) {
      return (s.substr(i) == t.substr(i + 1));
    } else {
      return s.substr(i + 1) == t.substr(i + 1);
    }
  }
};
