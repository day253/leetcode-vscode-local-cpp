#include "headers.h"

// @lc code=start
class Solution
{
public:
    int isValid(vector<int> &nums)
    {
        return 1;
    }
};
// @lc code=end

TEST(isValid, isValid_1)
{
    Solution s;
    vector<int> in = {1, 2, 3};
    int ans = 1;
    EXPECT_EQ(s.isValid(in), ans);
}
