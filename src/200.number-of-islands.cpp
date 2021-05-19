/*
 * @lc app=leetcode.cn id=200 lang=cpp
 *
 * [200] 岛屿数量
 *
 * https://leetcode-cn.com/problems/number-of-islands/description/
 *
 * algorithms
 * Medium (46.99%)
 * Likes:    399
 * Dislikes: 0
 * Total Accepted:    61.3K
 * Total Submissions: 129.7K
 * Testcase Example:
 * '[["1","1","1","1","0"],["1","1","0","1","0"],["1","1","0","0","0"],["0","0","0","0","0"]]'
 *
 * 给定一个由 '1'（陆地）和
 * '0'（水）组成的的二维网格，计算岛屿的数量。一个岛被水包围，并且它是通过水平方向或垂直方向上相邻的陆地连接而成的。你可以假设网格的四个边均被水包围。
 *
 * 示例 1:
 *
 * 输入:
 * 11110
 * 11010
 * 11000
 * 00000
 *
 * 输出: 1
 *
 *
 * 示例 2:
 *
 * 输入:
 * 11000
 * 11000
 * 00100
 * 00011
 *
 * 输出: 3
 *
 *
 */

#include "headers.h"

// @lc code=start
class Solution {
 public:
  void bfs(vector<vector<char>>& grid, int i, int j) {
    if (i < 0 || i >= grid.size() || j < 0 || j >= grid[i].size() ||
        grid[i][j] != '1') {
      return;
    }
    grid[i][j] = '2';
    bfs(grid, i + 1, j);
    bfs(grid, i - 1, j);
    bfs(grid, i, j + 1);
    bfs(grid, i, j - 1);
  }
  int numIslands(vector<vector<char>>& grid) {
    int res = 0;
    for (int i = 0; i < grid.size(); ++i) {
      for (int j = 0; j < grid[i].size(); ++j) {
        if (grid[i][j] == '1') {
          bfs(grid, i, j);
          ++res;
        }
      }
    }
    return res;
  }
};
// @lc code=end

TEST(numIslands, numIslands) {
  Solution s;
  vector<vector<char>> grid = {
      {'1', '1', '1', '1', '0'},
      {'1', '1', '0', '1', '0'},
      {'1', '1', '0', '0', '0'},
      {'0', '0', '0', '0', '0'},
  };
  EXPECT_EQ(1, s.numIslands(grid));
}
