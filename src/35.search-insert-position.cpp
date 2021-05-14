/*
 * @lc app=leetcode id=35 lang=cpp
 *
 * [35] Search Insert Position
 *
 * https://leetcode.com/problems/search-insert-position/description/
 *
 * algorithms
 * Easy (41.41%)
 * Likes:    1780
 * Dislikes: 214
 * Total Accepted:    512K
 * Total Submissions: 1.2M
 * Testcase Example:  '[1,3,5,6]\n5'
 *
 * Given a sorted array and a target value, return the index if the target is
 * found. If not, return the index where it would be if it were inserted in
 * order.
 *
 * You may assume no duplicates in the array.
 *
 * Example 1:
 *
 *
 * Input: [1,3,5,6], 5
 * Output: 2
 *
 *
 * Example 2:
 *
 *
 * Input: [1,3,5,6], 2
 * Output: 1
 *
 *
 * Example 3:
 *
 *
 * Input: [1,3,5,6], 7
 * Output: 4
 *
 *
 * Example 4:
 *
 *
 * Input: [1,3,5,6], 0
 * Output: 0
 *
 *
 */

#include "headers.h"

// @lc code=start
class Solution {
 public:
  int searchInsert(vector<int>& nums, int target) {
    int left = 0;
    int right = nums.size();
    while (left < right) {
      int mid = left + (right - left) /2;
      if (nums[mid] == target) {
        return mid;
      } else if (nums[mid] < target) {
        left = mid + 1;
      } else {
        right = mid;
      }
    }
    return left;
}
};
// @lc code=end

TEST(searchInsert, searchInsert1) {
  Solution s;
  vector<int> nums = {1, 3, 5, 6};
  int target = 5;
  int result = 2;
  EXPECT_EQ(result, s.searchInsert(nums, target));
}

TEST(searchInsert, searchInsert2) {
  Solution s;
  vector<int> nums = {1, 3, 5, 6};
  int target = 2;
  int result = 1;
  EXPECT_EQ(result, s.searchInsert(nums, target));
}

TEST(searchInsert, searchInsert3) {
  Solution s;
  vector<int> nums = {1, 3, 5, 6};
  int target = 7;
  int result = 4;
  EXPECT_EQ(result, s.searchInsert(nums, target));
}

TEST(searchInsert, searchInsert4) {
  Solution s;
  vector<int> nums = {1, 3, 5, 6};
  int target = 0;
  int result = 0;
  EXPECT_EQ(result, s.searchInsert(nums, target));
}