/*
 * @lc app=leetcode id=208 lang=cpp
 *
 * [208] Implement Trie (Prefix Tree)
 *
 * https://leetcode.com/problems/implement-trie-prefix-tree/description/
 *
 * algorithms
 * Medium (43.20%)
 * Likes:    2272
 * Dislikes: 41
 * Total Accepted:    234K
 * Total Submissions: 541.1K
 * Testcase Example:
 '["Trie","insert","search","search","startsWith","insert","search"]\n' +
  '[[],["apple"],["apple"],["app"],["app"],["app"],["app"]]'
 *
 * Implement a trie with insert, search, and startsWith methods.
 *
 * Example:
 *
 *
 * Trie trie = new Trie();
 *
 * trie.insert("apple");
 * trie.search("apple");   // returns true
 * trie.search("app");     // returns false
 * trie.startsWith("app"); // returns true
 * trie.insert("app");
 * trie.search("app");     // returns true
 *
 *
 * Note:
 *
 *
 * You may assume that all inputs are consist of lowercase letters a-z.
 * All inputs are guaranteed to be non-empty strings.
 *
 *
 */

#include "headers.h"

// @lc code=start
class TrieNode {
 public:
  TrieNode* next[26]{};
  bool is_leaf = false;
  void add(char c) { next[c - 'a'] = new TrieNode(); }
  TrieNode* get(char c) { return next[c - 'a']; }
};

class Trie {
 public:
  /** Initialize your data structure here. */
  Trie() : _root(new TrieNode) {}

  /** Inserts a word into the trie. */
  void insert(const string& word) {
    auto p = _root;
    for (auto c : word) {
      if (p->get(c) == nullptr) {
        p->add(c);
      }
      p = p->get(c);
    }
    p->is_leaf = true;
  }

  /** Returns if the word is in the trie. */
  bool search(const string& word) {
    auto p = _root;
    for (auto c : word) {
      if (p == nullptr) {
        break;
      }
      p = p->get(c);
    }
    return p && p->is_leaf;
  }

  /** Returns if there is any word in the trie that starts with the given
   * prefix. */
  bool startsWith(const string& prefix) {
    auto p = _root;
    for (auto c : prefix) {
      if (p == nullptr) {
        break;
      }
      p = p->get(c);
    }
    return p;
  }

 private:
  TrieNode* _root;
};

/**
 * Your Trie object will be instantiated and called as such:
 * Trie* obj = new Trie();
 * obj->insert(word);
 * bool param_2 = obj->search(word);
 * bool param_3 = obj->startsWith(prefix);
 */
// @lc code=end

TEST(Trie, Trie1) {
  auto trie(make_unique<Trie>());
  trie->insert("apple");
  EXPECT_TRUE(trie->search("apple"));     // returns true
  EXPECT_FALSE(trie->search("app"));      // returns false
  EXPECT_TRUE(trie->startsWith("app"));   // returns true
  EXPECT_FALSE(trie->startsWith("bpp"));  // returns false
  trie->insert("app");
  EXPECT_TRUE(trie->search("app"));  // returns true
}
