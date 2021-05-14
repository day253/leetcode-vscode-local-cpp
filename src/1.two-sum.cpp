/*
 * @lc app=leetcode id=1 lang=cpp
 *
 * [1] Two Sum
 *
 * https://leetcode.com/problems/two-sum/description/
 *
 * algorithms
 * Easy (45.00%)
 * Likes:    13230
 * Dislikes: 477
 * Total Accepted:    2.5M
 * Total Submissions: 5.5M
 * Testcase Example:  '[2,7,11,15]\n9'
 *
 * Given an array of integers, return indices of the two numbers such that they
 * add up to a specific target.
 *
 * You may assume that each input would have exactly one solution, and you may
 * not use the same element twice.
 *
 * Example:
 *
 *
 * Given nums = [2, 7, 11, 15], target = 9,
 *
 * Because nums[0] + nums[1] = 2 + 7 = 9,
 * return [0, 1].
 *
 *
 */

#include "headers.h"

// @lc code=start
class Solution
{
public:
    vector<int> twoSum(vector<int> &nums, int target)
    {
        map<int, int> index;
        for (int i = 0; i < nums.size(); i++)
        {
            auto it = index.find(target - nums[i]);
            if (it != index.end())
            {
                return vector<int>{it->second, i};
            }
            index.emplace(nums[i], i);
        }
        return vector<int>{};
    }
};
// @lc code=end

bool vectorEqual(const vector<int> &num1, const vector<int> &num2)
{
    if (num1.size() != num2.size())
    {
        return false;
    }
    for (int i = 0; i < num1.size(); ++i)
    {
        if (num1[i] != num2[i])
        {
            return false;
        }
    }
    return true;
}

TEST(twoSum, twoSum_1)
{
    Solution s;
    vector<int> nums = {2, 7, 11, 15};
    int targe = 9;
    vector<int> result = {0, 1};
    EXPECT_TRUE(vectorEqual(result, s.twoSum(nums, targe)));
}

TEST(twoSum, twoSum_2)
{
    Solution s;
    vector<int> nums = {3, 2, 4};
    int targe = 6;
    vector<int> result = {1, 2};
    EXPECT_TRUE(vectorEqual(result, s.twoSum(nums, targe)));
}