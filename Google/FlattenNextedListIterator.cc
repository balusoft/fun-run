/*
341. Flatten Nested List Iterator   My Submissions QuestionEditorial Solution
Total Accepted: 2715 Total Submissions: 13073 Difficulty: Medium
Given a nested list of integers, implement an iterator to flatten it.

Each element is either an integer, or a list -- whose elements may also be integers or other lists.

Example 1:
Given the list [[1,1],2,[1,1]],

By calling next repeatedly until hasNext returns false, the order of elements returned by next should be: [1,1,2,1,1].

Example 2:
Given the list [1,[4,[6]]],

By calling next repeatedly until hasNext returns false, the order of elements returned by next should be: [1,4,6].


*/


/**
 * // This is the interface that allows for creating nested lists.
 * // You should not implement it, or speculate about its implementation
 * class NestedInteger {
 *   public:
 *     // Return true if this NestedInteger holds a single integer, rather than a nested list.
 *     bool isInteger() const;
 *
 *     // Return the single integer that this NestedInteger holds, if it holds a single integer
 *     // The result is undefined if this NestedInteger holds a nested list
 *     int getInteger() const;
 *
 *     // Return the nested list that this NestedInteger holds, if it holds a nested list
 *     // The result is undefined if this NestedInteger holds a single integer
 *     const vector<NestedInteger> &getList() const;
 * };
 */
using NItr = vector<NestedInteger>::const_iterator;
using Nstk = std::stack<std::tuple<NItr, NItr>>;

class NestedIterator {
public:
    NestedIterator(const vector<NestedInteger> &nestedList)
        : nl_(nestedList) {
        st_.push(std::make_tuple(nl_.begin(), nl_.end()));
    }

    int next() {
        /*
        call hasNext();
        take a result from top.
        Increment the top, begin iterator.
        */
        hasNext();
        int res = std::get<0>(st_.top())->getInteger();
        ++std::get<0>(st_.top());
        return res;
    }

    bool hasNext() {
        /*
        while (top b == e || t is list) {
        while top of begin equal to end
          if stack empty, return false
          pop stack.
          increment begin pointer to refer next.
        while top of begin is list
          st.push(st.list.b, st.list.e);
        }
          
        */
        NItr begin, end;
        std::tie(begin, end) = st_.top();
        while (begin == end || !begin->isInteger()) {
            if (begin == end && st_.empty()) {
                break;
            }
            while (begin == end && !st_.empty()) {
                st_.pop();
                if (st_.empty()) {
                    break;
                }
                ++std::get<0>(st_.top());
                std::tie(begin, end) = st_.top();
            }
            while (begin != end && !begin->isInteger()) {
                st_.push(std::make_tuple(begin->getList().begin(), begin->getList().end()));
                std::tie(begin, end) = st_.top();
            }
        }
        return begin != end;
        
    }
private:
    Nstk st_;
    const vector<NestedInteger> nl_;
};

/**
 * Your NestedIterator object will be instantiated and called as such:
 * NestedIterator i(nestedList);
 * while (i.hasNext()) cout << i.next();
 */
