//
//  trie.h
//  CPP Test9
//
//  Created by Balaji Cherukuri on 8/24/15.
//  Copyright (c) 2015 FooBar. All rights reserved.
//

#ifndef __CPP_Test9__trie__
#define __CPP_Test9__trie__

#include <vector>
#include <string>
#include <iostream>
#include <list>
#include <cctype>
#include <cassert>

namespace trie {
    int ABC = 'z' - 'a' + 1;
    int c2i(char c) { return c - 'a'; }
    int i2c(int idx) { return idx + 'a'; }
    bool islower1(char c) { return c >= 'a' && c <= 'z'; }
    class TrieNode {
    public:
        char val;
        bool word;
        std::vector<TrieNode *> next;

        // Initialize your data structure here.
        TrieNode()
            : val('\0'), word(false), next(ABC, nullptr) {}
        TrieNode(char c)
            : val(c), word(false), next(ABC, nullptr) {}
        
    };
    
    struct WordsFound
    {
        TrieNode* node;
        std::string  word;
        bool valid;
        
        WordsFound(TrieNode *n, const std::string &str)
            : node(n), word(str), valid(true) {}
    };
    
    void printWords(const std::list<WordsFound*> &words)
    {
        return;
        for (auto i : words ) {
            if (i) {
                std::cout << std::boolalpha << "word: " << i->word << " fullword: " << i->node->word << " valid: " << i->valid << " \n";
            }
        }
        std::cout << "\n\n";
    }
    
    class Trie {
    public:
        Trie() {
            root = new TrieNode();
        }
        
        // Inserts a word into the trie.
        void insert(std::string word) {
            
            if (word == "") return;
            
            TrieNode* t = root;
            for (int i = 0; i < word.length(); ++i ) {
                if (!t->next[c2i(word[i])]) {
                    t->next[c2i(word[i])] = new TrieNode(word[i]);
                }
                
                t = t->next[c2i(word[i])];
            }
            
            t->word = true;
        }
        
        // Returns if the word is in the trie.
        bool search(std::string word) {
            if (word == "") return false;
            auto wf = pRegSearch(word);
            
            auto itr = wf.begin();
            while (itr != wf.end()) {
                if (!(*itr)->node->word) {
                    itr = wf.erase(itr);
                } else {
                    ++itr;
                }
            }
            
            printWords(wf);

            return !wf.empty();
        }
        
        // Returns if there is any word in the trie
        // that starts with the given prefix.
        bool startsWith(std::string prefix) {
            if (prefix == "") return false;
            auto words = pRegSearch(prefix);
            printWords(words);
            return !words.empty();
        }
    private:
        TrieNode* psearch(const std::string& word) {
            TrieNode *t = root;
            
            for (int i = 0; i < word.length(); ++i) {
                if (!t->next[c2i(word[i])]) {
                    return nullptr;
                }
                t = t->next[c2i(word[i])];
            }
            return t;
            
        }
        
        std::list<WordsFound*> pRegSearch(const std::string& word) {
            std::list<WordsFound*> wf;
            WordsFound *r = new WordsFound(root, "");
            wf.push_front(r);
            
            for (int i = 0; i < word.length(); ++i) {
                //Handle special cases
                std::list<WordsFound*> nl1;
                
                if (word[i] == '.')
                {
                    for (auto itr = wf.begin(); itr != wf.end(); ++itr)
                    {
                        if (!(*itr)->valid) {
                            continue;
                        }
                        
                        // Iterate from 'b' to 'z'
                        for (int j = 1; j < ABC; ++j) {
                            // Handle current list elements by assuming 'a'
                            if ((*itr)->node->next[j]) {
                                std::string w((*itr)->word);
                                w += i2c(j);
                                nl1.push_back(new WordsFound((*itr)->node->next[j], w));
                            }
                        }
                        
                        // Handle current list elements by assuming 'a'
                        if ((*itr)->node->next[0]) {
                            if ((*itr)->node->word) {
                                std::string st((*itr)->word);
                                st += i2c(0);
                                nl1.push_back(new WordsFound((*itr)->node->next[0], st));
                            } else {
                                (*itr)->node = (*itr)->node->next[0];
                                (*itr)->word += i2c(0);
                            }
                        } else {
                            (*itr)->valid = false;
                        }
                    }
                } else if (islower(word[i])) {
                    for (auto itr = wf.begin(); itr != wf.end(); ++itr) {
                        if (!(*itr)->valid) {
                            continue;
                        }
                        
                        if ((*itr)->node->next[c2i(word[i])]) {
                            if ((*itr)->node->word) {
                                std::string st((*itr)->word);
                                st += word[i];
                                nl1.push_back(new WordsFound((*itr)->node->next[c2i(word[i])], st));
                            } else {
                                (*itr)->node = (*itr)->node->next[c2i(word[i])];
                                (*itr)->word += word[i];
                            }
                        } else {
                            (*itr)->valid = false;
                        }

                    }
                } else {
                    assert(0 == "Unexpected character");
                }
                
                // merge wf and nl1
                wf.insert(wf.end(), nl1.begin(), nl1.end());
                
            }
            
            auto itr = wf.begin();
            while (itr != wf.end()) {
                if (!(*itr)->valid) {
                    itr = wf.erase(itr);
                } else {
                    ++itr;
                }
            }
            
            return wf;
        }
        
    private:
        TrieNode* root;
    };
    
    void unitTest()
    {
        {
            // Your Trie object will be instantiated and called as such:
            Trie trie;
            trie.insert("somestring");
            trie.insert("abc");
            trie.insert("act");
            trie.insert("ace");
            trie.insert("");
            trie.insert("z");
            
            std::cout << std::boolalpha << "sw: a.. >> " << trie.startsWith("...") << " \n";

            std::cout << std::boolalpha << "sw: a.. >> " << trie.search("...") << " \n";
            
            std::cout << std::boolalpha << "sw: a.. >> " << trie.search(".") << " \n";

//            std::cout << std::boolalpha << "Search: key >> " << trie.search("key") << " \n";
//            std::cout << std::boolalpha << "Search: a >> " << trie.search("a") << " \n";
//            std::cout << std::boolalpha << "Search: ab >> " << trie.search("ab") << " \n";
//            std::cout << std::boolalpha << "sw: ab >> " << trie.startsWith("ab") << " \n";
//            std::cout << std::boolalpha << "sw: ac >> " << trie.startsWith("ac") << " \n";
//            std::cout << std::boolalpha << "sw: .cc >> " << trie.startsWith(".cc") << " \n";
//            std::cout << std::boolalpha << "sw: .ct >> " << trie.startsWith(".ct") << " \n";
//
//            std::cout << std::boolalpha << "Search: abc >> " << trie.search("abc") << " \n";
//            std::cout << std::boolalpha << "Search: act >> " << trie.search("act") << " \n";
//            std::cout << std::boolalpha << "Search:  >> " << trie.search("") << " \n";

            

        }
    }
}
#endif /* defined(__CPP_Test9__trie__) */
