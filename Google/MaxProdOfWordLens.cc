/**
Given a string array words, find the maximum value of length(word[i]) *
length(word[j]) where the two words do not share common letters. You may assume
that each word will contain only lower case letters. If no such two words exist,
return 0.

Example 1:
Given ["abcw", "baz", "foo", "bar", "xtfn", "abcdef"]
Return 16
The two words can be "abcw", "xtfn".

Example 2:
Given ["a", "ab", "abc", "d", "cd", "bcd", "abcd"]
Return 4
The two words can be "ab", "cd".

Example 3:
Given ["a", "aa", "aaa", "aaaa"]
Return 0
No such pair of words
**/

class Solution {
public:
    int maxProduct(vector<string>& words) {
        std::unordered_map<int, int> wmLen;
        for (auto w : words) {
            uint32_t mask=0;
            for (auto c : w) {
                mask |= 1 << c-'a';
            }
            int len=w.length();
            if (wmLen.count(mask) > 0 && len < wmLen[mask]) {
                len=wmLen[mask];
            }
            wmLen[mask] = len;
        }
        
        int result = 0;
        for (auto a : wmLen) {
            for (auto b : wmLen) {
                if ((a.first & b.first) == 0) {
                    result = std::max(result, a.second*b.second);
                }
            }
        }
        return result;
    }
};
