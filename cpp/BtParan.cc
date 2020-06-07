/**
Given n pairs of parentheses, write a function to generate all combinations of
well-formed parentheses.

For example, given n = 3, a solution set is:

"((()))", "(()())", "(())()", "()(())", "()()()"

*/

#include <vector>
#include <iostream>

struct BtContext {
  BtContext(uint32_t num)
   : n(num), curParen(2*n, ' '),level(-1),allParens(),cntr(2, 0),val{'(', ')'} {
   }
  uint32_t n;
  std::string curParen;
  uint32_t level;
  std::vector<std::string> allParens;
  std::vector<uint32_t> cntr;
  std::vector<char> val;
};

struct ParenItr {
  ParenItr(const BtContext& cx)
    : ctx(cx), avail(2, false),idx(-1) {
    if (ctx.cntr[0] == ctx.cntr[1]) {
      avail[0] = true;
    } else if (ctx.cntr[0] > ctx.cntr[1]) {
      if (ctx.cntr[0] < ctx.n) {
        avail[0] = true;
      }
      avail[1] = true;
    }
  }
  bool next() {
    uint32_t tmp = idx + 1;
    while (tmp < 2 && !avail[tmp]) {
      ++tmp;
    }
    if (2 == tmp) {
      return false;
    }
    idx=tmp;
    return true;
  }
  uint32_t operator*() const {
    return idx;
  }
  const BtContext &ctx;
  std::vector<bool> avail;
  uint32_t idx; /* ( ) */
};

/*backtrack*/
void backtrack(BtContext& ctx) {
  if (ctx.n < 1) return;
  if (ctx.level == ctx.n*2) {
    ctx.allParens.push_back(ctx.curParen);
  } else {
    ++ctx.level;
    ParenItr itr(ctx);
    while (itr.next()) {
      ++ctx.cntr[*itr];
      ctx.curParen[ctx.level] = ctx.val[*itr];
      //std::cout << "cp: " << ctx.curParen << "\n";
      backtrack(ctx);
      --ctx.cntr[*itr];
    }
    --ctx.level;
  }
}
/* API */
std::vector<std::string> generateParenthesis(uint32_t n) {
  BtContext ctx(n);
  backtrack(ctx);
  return ctx.allParens;
}

class Solution {
public:
  std::vector<std::string> generateParenthesis(int n) {
    BtContext ctx(n);
    backtrack(ctx);
    return ctx.allParens;
    //return generateParenthesis(n);
  }
};

int main() {
  for (uint32_t idx=1; idx <= 1; ++idx) {
    Solution s;
    std::vector<std::string> sol = s.generateParenthesis(idx);
    for (const auto& val : sol) {
      std::cout << val << "\n";
    }
    //std::cout <<"\n\n" ;
  }
}
