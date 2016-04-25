/**
166. Fraction to Recurring Decimal   My Submissions QuestionEditorial Solution
Total Accepted: 29736 Total Submissions: 197126 Difficulty: Medium
Given two integers representing the numerator and denominator of a fraction, return the fraction in string format.

If the fractional part is repeating, enclose the repeating part in parentheses.

For example,

Given numerator = 1, denominator = 2, return "0.5".
Given numerator = 2, denominator = 1, return "2".
Given numerator = 2, denominator = 3, return "0.(6)".
Show Hint 
Credits:
Special thanks to @Shangrila for adding this problem and creating all test cases.

Subscribe to see which companies asked this question
**/

class Solution {
public:
    string fractionToDecimal(int64_t n, int64_t d) {
        /*
        1) Get integral division value
        2) Get remindar
        3) If remindar is zero return to_string(res)
        4) rem *= 10;
        5) take map
           res2;
        6) repeat until rem is zero
        7)   res = rem/d;
        8)   rem = rem%d;
        9)   if map.count(rem) > 0 .. return 
        10)  res2 += to_string(res);
        11)  rem *= 10;
        */
        if (n == 0) {
            return "0";
        }
        assert(0 != d);
        bool isNeg = ((n < 0) ^ (d<0));
        n = abs(n);
        d = abs(d);
        std::string res;
        if (isNeg) { res += "-"; 
            std::cout << "negative" << "\n";
        }
        res += to_string(n/d);
        if (n%d == 0) return res;
        res += ".";
        std::unordered_map<int, int> map;
        for (int64_t r = n%d; r; r %= d) {
            if (map.count(r) > 0) {
                res.insert(map[r], 1, '(');
                res += ')';
                break;
            }
            map[r]=res.size();
            r *= 10;
            res += to_string(r/d);
            //std::cout << "rem: "  << rem << "\n";
        }
        return res;
    }
};
