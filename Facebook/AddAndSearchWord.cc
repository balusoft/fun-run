/**
211. Add and Search Word - Data structure design   My Submissions
QuestionEditorial Solution
Total Accepted: 23425 Total Submissions: 115897 Difficulty: Medium
Design a data structure that supports the following two operations:

void addWord(word)
bool search(word)
search(word) can search a literal word or a regular expression string containing
only letters a-z or .. A . means it can represent any one letter.

For example:

addWord("bad")
addWord("dad")
addWord("mad")
search("pad") -> false
search("bad") -> true
search(".ad") -> true
search("b..") -> true
Note:
You may assume that all words are consist of lowercase letters a-z.
**/

class TrieNode;
//using TrieNodePtr = std::shared_ptr<TrieNode>;
using TrieNodePtr = TrieNode*;
struct TrieNode {
    TrieNode() : next(26, nullptr), isWord(false) {} 
    std::vector<TrieNodePtr> next;
    bool isWord;
};

class WordDictionary {
public:
    WordDictionary() : trie(/*std::make_shared<TrieNode>()*/new TrieNode()) {}
    // Adds a word into the data structure.
    void addWord(const string &s) {
        TrieNodePtr itr = trie;
        for (int i=0; i<s.length(); ++i) {
            if (!itr->next[s[i]-'a']) {
                std::cout << "adding node with:" << s[i] << "\n";
                //itr->next[s[i]-'a'] = std::make_shared<TrieNode>(s[i]);
                itr->next[s[i]-'a'] = new TrieNode();
            }
            itr=itr->next[s[i]-'a'];
        }
        std::cout << "itr->c:" << "\n";
        itr->isWord = true;
    }

    // Returns if the word is in the data structure. A word could
    // contain the dot character '.' to represent any one letter.
    bool search(const string &word) {
        return searchDfs(word, 0, trie);
    }
    bool searchDfs(const string &word, const int idx, TrieNodePtr itr) {
        if (!itr) {
            return false;
        }
        if (idx == word.length()) {
            return itr->isWord;
        }
        char c = word[idx]; 
        if ('.' == c) {
            for (auto n : itr->next) {
                if (searchDfs(word, idx+1, n)) {
                    return true;
                }
            }
        } else {
            return searchDfs(word, idx+1, itr->next[word[idx]-'a']);
        }
    }
private:
    TrieNodePtr trie;
};

// Your WordDictionary object will be instantiated and called as such:
// WordDictionary wordDictionary;
// wordDictionary.addWord("word");
// wordDictionary.search("pattern");
