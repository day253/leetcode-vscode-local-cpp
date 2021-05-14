/*
 * @lc app=leetcode id=207 lang=cpp
 *
 * [207] Course Schedule
 *
 * https://leetcode.com/problems/course-schedule/description/
 *
 * algorithms
 * Medium (40.54%)
 * Likes:    2740
 * Dislikes: 141
 * Total Accepted:    312.8K
 * Total Submissions: 770.1K
 * Testcase Example:  '2\n[[1,0]]'
 *
 * There are a total of n courses you have to take, labeled from 0 to n-1.
 *
 * Some courses may have prerequisites, for example to take course 0 you have
 * to first take course 1, which is expressed as a pair: [0,1]
 *
 * Given the total number of courses and a list of prerequisite pairs, is it
 * possible for you to finish all courses?
 *
 * Example 1:
 *
 *
 * Input: 2, [[1,0]]
 * Output: true
 * Explanation: There are a total of 2 courses to take.
 * To take course 1 you should have finished course 0. So it is possible.
 *
 * Example 2:
 *
 *
 * Input: 2, [[1,0],[0,1]]
 * Output: false
 * Explanation: There are a total of 2 courses to take.
 * To take course 1 you should have finished course 0, and to take course 0 you
 * should
 * also have finished course 1. So it is impossible.
 *
 *
 * Note:
 *
 *
 * The input prerequisites is a graph represented by a list of edges, not
 * adjacency matrices. Read more about how a graph is represented.
 * You may assume that there are no duplicate edges in the input
 * prerequisites.
 *
 *
 */

#include "headers.h"

// @lc code=start
class Solution {
 public:
  bool canFinish(int numCourses, vector<vector<int>>& prerequisites) {
    // 1.格式转换
    // 初始化临接矩阵
    // 初始化出度数组
    vector<vector<int>> adj(numCourses, vector<int>{});
    vector<int> indegree(numCourses, 0);
    for (auto& item : prerequisites) {
      if (item.size() != 2) {
        continue;
      }
      adj[item[1]].push_back(item[0]);
      ++indegree[item[0]];
    }
    queue<int> q;
    // 2.初始化队列
    for (int i = 0; i < numCourses; ++i) {
      if (indegree[i] == 0) {
        q.push(i);
      }
    }
    // 3.拓扑排序
    while (!q.empty()) {
      // 去除队列元素
      int cur = q.front();
      q.pop();
      // 终止标记
      --numCourses;
      // 入度减一
      for (auto item : adj[cur]) {
        if (--indegree[item] == 0) {
          q.push(item);
        }
      }
    }
    return numCourses == 0;
  }
};
// @lc code=end

TEST(canFinish, canFinish1) {
  Solution s;
  int numCourses = 2;
  vector<vector<int>> prerequisites = {
      {1, 0},
  };
  EXPECT_TRUE(s.canFinish(numCourses, prerequisites));
}

TEST(canFinish, canFinish2) {
  Solution s;
  int numCourses = 2;
  vector<vector<int>> prerequisites = {
      {1, 0},
      {0, 1},
  };
  EXPECT_FALSE(s.canFinish(numCourses, prerequisites));
}

TEST(canFinish, canFinish3) {
  Solution s;
  int numCourses = 2;
  vector<vector<int>> prerequisites = {};
  EXPECT_TRUE(s.canFinish(numCourses, prerequisites));
}

TEST(canFinish, canFinish4) {
  Solution s;
  int numCourses = 3;
  vector<vector<int>> prerequisites = {
      {1, 0},
  };
  EXPECT_TRUE(s.canFinish(numCourses, prerequisites));
}