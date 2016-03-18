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
class TrieNode {
public:
  // Initialize your data structure here.
  TrieNode() {}
};

class Trie {
public:
  Trie() { root = new TrieNode(); }

  // Inserts a word into the trie.
  void insert(string word) {}

  // Returns if the word is in the trie.
  bool search(string word) {}

  // Returns if there is any word in the trie
  // that starts with the given prefix.
  bool startsWith(string prefix) {}

private:
  TrieNode *root;
};

// Your Trie object will be instantiated and called as such:
// Trie trie;
// trie.insert("somestring");
// trie.search("key");
