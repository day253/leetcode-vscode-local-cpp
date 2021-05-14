/*
 * @lc app=leetcode id=210 lang=cpp
 *
 * [210] Course Schedule II
 *
 * https://leetcode.com/problems/course-schedule-ii/description/
 *
 * algorithms
 * Medium (37.71%)
 * Likes:    1509
 * Dislikes: 101
 * Total Accepted:    205.5K
 * Total Submissions: 543.9K
 * Testcase Example:  '2\n[[1,0]]'
 *
 * There are a total of n courses you have to take, labeled from 0 to n-1.
 *
 * Some courses may have prerequisites, for example to take course 0 you have
 * to first take course 1, which is expressed as a pair: [0,1]
 *
 * Given the total number of courses and a list of prerequisite pairs, return
 * the ordering of courses you should take to finish all courses.
 *
 * There may be multiple correct orders, you just need to return one of them.
 * If it is impossible to finish all courses, return an empty array.
 *
 * Example 1:
 *
 *
 * Input: 2, [[1,0]]
 * Output: [0,1]
 * Explanation: There are a total of 2 courses to take. To take course 1 you
 * should have finished
 * course 0. So the correct course order is [0,1] .
 *
 * Example 2:
 *
 *
 * Input: 4, [[1,0],[2,0],[3,1],[3,2]]
 * Output: [0,1,2,3] or [0,2,1,3]
 * Explanation: There are a total of 4 courses to take. To take course 3 you
 * should have finished both
 * ⁠            courses 1 and 2. Both courses 1 and 2 should be taken after
 * you finished course 0. So one correct course order is [0,1,2,3]. Another
 * correct ordering is [0,2,1,3] .
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
  vector<int> findOrder(int numCourses, vector<vector<int>>& prerequisites) {
    vector<vector<int>> adj(numCourses, vector<int>{});
    vector<int> indegree(numCourses, 0);
    for (const auto& item : prerequisites) {
      adj[item[1]].push_back(item[0]);
      ++indegree[item[0]];
    }
    queue<int> q;
    vector<int> result;
    for (int i = 0; i < numCourses; ++i) {
      if (indegree[i] == 0) {
        q.push(i);
      }
    }
    while (!q.empty()) {
      int cur = q.front();
      q.pop();
      result.push_back(cur);
      --numCourses;
      for (auto item : adj[cur]) {
        if (--indegree[item] == 0) {
          q.push(item);
        }
      }
    }
    return numCourses == 0 ? result : vector<int>{};
  }
};
// @lc code=end

bool isSameVector(const vector<int>& v1, const vector<int>& v2) {
  if (v1.size() != v2.size()) {
    return false;
  }
  for (int i = 0; i < v1.size(); ++i) {
    if (v1[i] != v2[i]) {
      return false;
    }
  }
  return true;
}

bool isOneOfVector(const vector<vector<int>>& results,
                   const vector<int>& input) {
  for (const auto& item : results) {
    if (isSameVector(item, input)) {
      return true;
    }
  }
  return false;
}

TEST(findOrder, findOrder1) {
  Solution s;
  int numCourses = 2;
  vector<vector<int>> prerequisites = {
      {1, 0},
  };
  vector<vector<int>> results = {
      {0, 1},
  };
  EXPECT_TRUE(isOneOfVector(results, s.findOrder(numCourses, prerequisites)));
}

TEST(findOrder, findOrder2) {
  Solution s;
  int numCourses = 4;
  vector<vector<int>> prerequisites = {
      {1, 0},
      {2, 0},
      {3, 1},
      {3, 2},
  };
  vector<vector<int>> results = {
      {0, 1, 2, 3},
      {0, 2, 1, 3},
  };
  EXPECT_TRUE(isOneOfVector(results, s.findOrder(numCourses, prerequisites)));
}

TEST(findOrder, findOrder3) {
  Solution s;
  int numCourses = 3;
  vector<vector<int>> prerequisites = {
      {1, 0},
      {1, 2},
      {0, 1},
  };
  vector<vector<int>> results = {
      {},
  };
  EXPECT_TRUE(isOneOfVector(results, s.findOrder(numCourses, prerequisites)));
}