/*
 * @lc app=leetcode id=212 lang=cpp
 *
 * [212] Word Search II
 *
 * https://leetcode.com/problems/word-search-ii/description/
 *
 * algorithms
 * Hard (31.69%)
 * Likes:    1740
 * Dislikes: 89
 * Total Accepted:    158.2K
 * Total Submissions: 498.7K
 * Testcase Example:
 '[["o","a","a","n"],["e","t","a","e"],["i","h","k","r"],["i","f","l","v"]]\n' +
  '["oath","pea","eat","rain"]'
 *
 * Given a 2D board and a list of words from the dictionary, find all words in
 * the board.
 *
 * Each word must be constructed from letters of sequentially adjacent cell,
 * where "adjacent" cells are those horizontally or vertically neighboring. The
 * same letter cell may not be used more than once in a word.
 *
 *
 *
 * Example:
 *
 *
 * Input:
 * board = [
 * ⁠ ['o','a','a','n'],
 * ⁠ ['e','t','a','e'],
 * ⁠ ['i','h','k','r'],
 * ⁠ ['i','f','l','v']
 * ]
 * words = ["oath","pea","eat","rain"]
 *
 * Output: ["eat","oath"]
 *
 *
 *
 *
 * Note:
 *
 *
 * All inputs are consist of lowercase letters a-z.
 * The values of words are distinct.
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
  Trie() : _root(new TrieNode()) {}
  Trie(const vector<string>& words) {
    _root = new TrieNode();
    add_list(words);
  }
  TrieNode* root() { return _root; }
  void add_list(const vector<string>& words) {
    for (const auto& word : words) {
      add(word);
    }
  }
  void add(const string& word) {
    auto p = _root;
    for (auto c : word) {
      if (p->get(c) == nullptr) {
        p->add(c);
      }
      p = p->get(c);
    }
    p->is_leaf = true;
  }
  bool search(const string& word) const {
    auto p = _root;
    for (auto c : word) {
      if (p == nullptr) {
        return false;
      }
      p = p->get(c);
    }
    return p && p->is_leaf;
  }

 private:
  TrieNode* _root = nullptr;
};
class Solution {
 public:
  vector<string> findWords(vector<vector<char>>& board, vector<string>& words) {
    auto trie = new Trie(words);
    auto root = trie->root();
    set<string> result_set;
    for (int i = 0; i < board.size(); ++i) {
      for (int j = 0; j < board[i].size(); ++j) {
        search(board, root, i, j, "", &result_set);
      }
    }
    vector<string> result;
    for (auto& item : result_set) {
      result.push_back(item);
    }
    return result;
  }

 private:
  void search(vector<vector<char>>& board, TrieNode* root, int x, int y,
              const string& word, set<string>* result) {
    if (x < 0 || x >= board.size() || board.empty() || y < 0 ||
        y >= board[0].size() || board[x][y] == ' ') {
      return;
    }
    auto cur = board[x][y];
    if (root->get(cur) != nullptr) {
      auto new_word = word + cur;
      root = root->get(cur);
      if (root->is_leaf) {
        result->insert(new_word);
      }
      board[x][y] = ' ';  // 剪枝 新方法？
      search(board, root, x + 1, y, new_word, result);
      search(board, root, x - 1, y, new_word, result);
      search(board, root, x, y + 1, new_word, result);
      search(board, root, x, y - 1, new_word, result);
      board[x][y] = cur;
    }
  }
};
// @lc code=end

TEST(findWords, findWords1) {
  auto trie(make_unique<Trie>());
  trie->add("apple");
  EXPECT_TRUE(trie->search("apple"));  // returns true
  EXPECT_FALSE(trie->search("app"));   // returns false
  trie->add("app");
  EXPECT_TRUE(trie->search("app"));  // returns true
}

TEST(findWords, findWords2) {
  vector<vector<char>> board{
      {'o', 'a', 'a', 'n'},
      {'e', 't', 'a', 'e'},
      {'i', 'h', 'k', 'r'},
      {'i', 'f', 'l', 'v'},
  };
  vector<string> words{
      "oath",
      "pea",
      "eat",
      "rain",
  };
  set<string> output{
      "eat",
      "oath",
  };
  Solution s;
  auto result = s.findWords(board, words);
  EXPECT_EQ(output.size(), result.size());
  for (auto& item : result) {
    EXPECT_TRUE(output.find(item) != output.end());
  }
}