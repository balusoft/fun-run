/*
208. Implement Trie (Prefix Tree) My Submissions Question
Total Accepted: 31711 Total Submissions: 125552 Difficulty: Medium
Implement a trie with insert, search, and startsWith methods.

Note:
You may assume that all inputs are consist of lowercase letters a-z.

Subscribe to see which companies asked this question

Show Tags
Show Similar Problems
Have you met this question in a real interview? Yes  No
Discuss

*/

#include <vector>
#include <string>
#include <memory>

#include <cxxtest/TestSuite.h>

class TrieNode;
typedef std::shared_ptr<TrieNode> TrieNodePtr;
class TrieNode {
public:
  // Initialize your data structure here.
  TrieNode() : next(26), isWord(false) {}
  std::vector<TrieNodePtr> next; // assume a-z or simply map
  bool isWord;
};

class Trie {
public:
  Trie() : root(new TrieNode()) {}

  // Inserts a word into the trie.
  void insert(const std::string& word) {
    TrieNodePtr itr = root;
    for (auto &c : word) {
      if (!itr->next[c-'a']) {
        TrieNodePtr node(new TrieNode());
        itr->next[c-'a'] = node;
      }
      itr = itr->next[c-'a'];
    }
    itr->isWord = true;
  }

  // Returns if the word is in the trie.
  bool search(const std::string& word) {
    if (word.empty()) {
      return false;
    }
    TrieNodePtr itr = getTrieNode(word);
    return (itr) && itr->isWord;
  }

  // Returns if there is any word in the trie
  // that starts with the given prefix.
  bool startsWith(const std::string& prefix) {
    if (prefix.empty()) {
      return true;
    }
    TrieNodePtr itr = getTrieNode(prefix);
    return !!itr;
  }
private:
  TrieNodePtr getTrieNode(const std::string& word) {
    TrieNodePtr itr = root;
    for (auto &c : word) {
      if (!itr->next[c-'a']) {
        return TrieNodePtr();
      }
      itr = itr->next[c-'a'];
    }
    return itr;
  }
  TrieNodePtr root;
};

// Your Trie object will be instantiated and called as such:
// Trie trie;
// trie.insert("somestring");
// trie.search("key");

class TestSolution : public CxxTest::TestSuite {
public:
  void test_all() {
    Trie trie;
    trie.insert("some");
    trie.insert("same");
    trie.insert("something");
    trie.insert("sameperson");
    TS_ASSERT_EQUALS(trie.search(""), false);
    TS_ASSERT_EQUALS(trie.startsWith(""), true);
    TS_ASSERT_EQUALS(trie.search("somet"), false);
    TS_ASSERT_EQUALS(trie.startsWith("somet"), true);
    TS_ASSERT_EQUALS(trie.search("sam"), false);
    TS_ASSERT_EQUALS(trie.search("foobar"), false);
    TS_ASSERT_EQUALS(trie.search("sameperson"), true);
    TS_ASSERT_EQUALS(trie.startsWith("sameper"), true);
  }
};
