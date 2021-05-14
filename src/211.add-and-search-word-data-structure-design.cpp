/*
 * @lc app=leetcode id=211 lang=cpp
 *
 * [211] Add and Search Word - Data structure design
 *
 * https://leetcode.com/problems/add-and-search-word-data-structure-design/description/
 *
 * algorithms
 * Medium (33.60%)
 * Likes:    1241
 * Dislikes: 69
 * Total Accepted:    147.8K
 * Total Submissions: 439.4K
 * Testcase Example:
 '["WordDictionary","addWord","addWord","addWord","search","search","search","search"]\n'
 +
  '[[],["bad"],["dad"],["mad"],["pad"],["bad"],[".ad"],["b.."]]'
 *
 * Design a data structure that supports the following two operations:
 *
 *
 * void addWord(word)
 * bool search(word)
 *
 *
 * search(word) can search a literal word or a regular expression string
 * containing only letters a-z or .. A . means it can represent any one
 * letter.
 *
 * Example:
 *
 *
 * addWord("bad")
 * addWord("dad")
 * addWord("mad")
 * search("pad") -> false
 * search("bad") -> true
 * search(".ad") -> true
 * search("b..") -> true
 *
 *
 * Note:
 * You may assume that all words are consist of lowercase letters a-z.
 *
 */

#include "headers.h"

// @lc code=start
class TrieNode {
 public:
  bool is_leaf = false;
  TrieNode* next[26]{};
  void add(char c) { next[c - 'a'] = new TrieNode; }
  TrieNode* get(char c) const { return next[c - 'a']; }
};

class WordDictionary {
 public:
  /** Initialize your data structure here. */
  WordDictionary() : _root(new TrieNode) {}

  /** Adds a word into the data structure. */
  void addWord(const string& word) {
    auto p = _root;
    for (auto c : word) {
      if (p->get(c) == nullptr) {
        p->add(c);
      }
      p = p->get(c);
    }
    p->is_leaf = true;
  }

  /** Returns if the word is in the data structure. A word could contain the dot
   * character '.' to represent any one letter. */
  bool search(const string& word) { return search(word.c_str(), _root); }

 private:
  bool search(const char* word, TrieNode* root) {
    for (int i = 0; word[i] && root; ++i) {
      if (word[i] != '.') {
        root = root->get(word[i]);
      } else {
        auto tmp = root;
        for (int j = 0; j < 26; ++j) {
          root = tmp->next[j];
          if (search(word + i + 1, root)) {
            return true;
          }
        }
      }
    }
    return root && root->is_leaf;
  }

 private:
  TrieNode* _root = nullptr;
};

/**
 * Your WordDictionary object will be instantiated and called as such:
 * WordDictionary* obj = new WordDictionary();
 * obj->addWord(word);
 * bool param_2 = obj->search(word);
 */
// @lc code=end

TEST(WordDictionary, WordDictionary1) {
  vector<string> words{
      "bad",
      "dad",
      "mad",
  };
  auto obj(make_unique<WordDictionary>());
  for (const auto& word : words) {
    obj->addWord(word);
  }
  vector<string> tests{
      "pad",
      "bad",
      ".ad",
      "b..",
  };
  vector<bool> results{
      false,
      true,
      true,
      true,
  };
  EXPECT_EQ(tests.size(), results.size());
  for (int i = 0; i < tests.size(); ++i) {
    EXPECT_EQ(results[i], obj->search(tests[i]));
  }
}