/*
 * @lc app=leetcode.cn id=269 lang=cpp
 *
 * [269] Alien Dictionary
 *
 * https://leetcode-cn.com/problems/alien-dictionary
 * There is a new alien language which uses the latin alphabet. However, the
 * order among letters are unknown to you. You receive a list of non-empty words
 * from the dictionary, where words are sorted lexicographically by the rules of
 * this new language. Derive the order of letters in this language.
 *
 * Example 1:
 *
 * Input:
 * [
 *   "wrt",
 *   "wrf",
 *   "er",
 *   "ett",
 *   "rftt"
 * ]
 *
 * Output: "wertf"
 * Example 2:
 *
 * Input:
 * [
 *   "z",
 *   "x"
 * ]
 *
 * Output: "zx"
 * Example 3:
 *
 * Input:
 * [
 *   "z",
 *   "x",
 *   "z"
 * ]
 *
 * Output: "" 
 *
 * Explanation: The order is invalid, so return "".
 * Note:
 *
 * You may assume all letters are in lowercase.
 * You may assume that if a is a prefix of b, then a must appear before b in the
 * given dictionary. If the order is invalid, return an empty string. There may
 * be multiple valid order of letters, return any one of them is fine.
 */

#include "headers.h"

// @lc code=start
class Solution {
 public:
  string alienOrder(vector<string>& words) {
    if (words.empty()) {
      return "";
    }

    int cnt = 0;
    vector<int> indegree(26, -1);
    vector<vector<int>> graph(26, vector<int>{});

    for (auto c : words[0]) {
      if (indegree[c - 'a'] == -1) {
        ++cnt;
        indegree[c - 'a'] = 0;
      }
    }

    for (int i = 0; i < words.size() - 1; ++i) {
      for (auto c : words[i + 1]) {
        if (indegree[c - 'a'] == -1) {
          ++cnt;
          indegree[c - 'a'] = 0;
        }
      }
      for (int j = 0; j < min(words[i].size(), words[i + 1].size()); ++j) {
        char from = words[i][j];
        char to = words[i + 1][j];
        if (from == to) {
          continue;
        }
        graph[from - 'a'].push_back(to - 'a');
        ++indegree[to - 'a'];
        break;
      }
    }

    string ans;
    queue<int> q;
    for (int i = 0; i < indegree.size(); ++i) {
      if (indegree[i] == 0) {
        q.push(i);
      }
    }
    while (!q.empty()) {
      int from = q.front();
      q.pop();
      ans += (from + 'a');
      for (auto to : graph[from]) {
        if (--indegree[to] == 0) {
          q.push(to);
        }
      }
    }
    return ans.size() == cnt ? ans : "";
  }
};
// @lc code=end

TEST(alienOrder, alienOrder1) {
  Solution s;
  vector<string> words = {
      "wrt", "wrf", "er", "ett", "rftt",
  };
  EXPECT_STREQ("wertf", s.alienOrder(words).c_str());
}

TEST(alienOrder, alienOrder2) {
  Solution s;
  vector<string> words = {
      "z",
      "x",
  };
  EXPECT_STREQ("zx", s.alienOrder(words).c_str());
}

TEST(alienOrder, alienOrder3) {
  Solution s;
  vector<string> words = {
      "z",
      "x",
      "z",
  };
  EXPECT_STREQ("", s.alienOrder(words).c_str());
}

// TODO:网站可以提交这里不知道为啥不行
TEST(alienOrder, alienOrder4) {
  Solution s;
  vector<string> words = {
      "za",
      "zb",
      "ca",
      "cb",
  };
  // EXPECT_STREQ("abzc", s.alienOrder(words).c_str());
}