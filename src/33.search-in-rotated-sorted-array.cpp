/*
 * @lc app=leetcode id=33 lang=cpp
 *
 * [33] Search in Rotated Sorted Array
 *
 * https://leetcode.com/problems/search-in-rotated-sorted-array/description/
 *
 * algorithms
 * Medium (33.59%)
 * Likes:    3644
 * Dislikes: 396
 * Total Accepted:    562.8K
 * Total Submissions: 1.7M
 * Testcase Example:  '[4,5,6,7,0,1,2]\n0'
 *
 * Suppose an array sorted in ascending order is rotated at some pivot unknown
 * to you beforehand.
 *
 * (i.e., [0,1,2,4,5,6,7] might become [4,5,6,7,0,1,2]).
 *
 * You are given a target value to search. If found in the array return its
 * index, otherwise return -1.
 *
 * You may assume no duplicate exists in the array.
 *
 * Your algorithm's runtime complexity must be in the order of O(log n).
 *
 * Example 1:
 *
 *
 * Input: nums = [4,5,6,7,0,1,2], target = 0
 * Output: 4
 *
 *
 * Example 2:
 *
 *
 * Input: nums = [4,5,6,7,0,1,2], target = 3
 * Output: -1
 *
 */

#include "headers.h"

// @lc code=start
class Solution {
 public:
  // 异或解法
  // https://leetcode-cn.com/problems/search-in-rotated-sorted-array/solution/ji-jian-solution-by-lukelee/
  int search(vector<int>& nums, int target) {
    int left = 0;
    int right = nums.size() - 1;

    while (left <= right) {
      int mid = left + (right - left) / 2;
      if (nums[mid] == target) {
        return mid;
      } else if ((nums[mid] < nums[0]) ^ (target < nums[0]) ^
                 (nums[mid] < target)) {
        left = mid + 1;
      } else {
        right = mid - 1;
      }
    }
    return -1;
  }
};
// @lc code=end

TEST(search, search1) {
  Solution s;
  vector<int> nums = {4, 5, 6, 7, 0, 1, 2};
  int target = 0;
  int result = 4;
  EXPECT_EQ(result, s.search(nums, target));
}

TEST(search, search2) {
  Solution s;
  vector<int> nums = {4, 5, 6, 7, 0, 1, 2};
  int target = 3;
  int result = -1;
  EXPECT_EQ(result, s.search(nums, target));
}