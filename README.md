# LeetCode C++ 本地调试环境

[![Build Status](https://travis-ci.com/day253/LeetCode.svg?branch=master)](https://travis-ci.com/day253/LeetCode)

详细用法参见[使用VSCode进行LeetCode C++本地调试](https://zhuanlan.zhihu.com/p/80062085)

## 持续集成

在fork的仓库中可以直接启用TravisCI功能，最后修改下Travis的图标的地址就能变成自己的仓库啦。

## 依赖

- cmake
- googletest

### Googletest安装

```shell
git clone https://github.com/google/googletest.git
mkdir build && cd build
cmake ..
make
make install
```

## 生成模板并调试运行

首先生成题目模板，拷贝`src`目录中的`0.template.cc`，并重命名为`{PROBLEM_NAME}_{PROBLEM_ID}.cc`的格式，修改函数名称，输入输出或者使用项目根目录中的模板生成脚本，不是很难。

修改测试用例，根据需求修改函数名、测试用例输入输出等等，下面为例程

```cpp
// 包含"include/headers.h"文件，引入常用头文件
// 如不包含，于"include/headers.h"文件中添加
#include "headers.h"

// @lc code=start
class Solution
// 题解类
{
public:
    int coinChange_322(vector<int> &coins, int amount)
    // 题解函数，这里写答案
    {
        vector<int> dp(amount + 1, amount + 1);
        dp[0] = 0;
        for (int i = 1; i <= amount; i++)
        {
            for (auto coin : coins)
            {
                if (coin <= i)
                    dp[i] = min(dp[i], dp[i - coin] + 1);
            }
        }
        return dp[amount] > amount ? -1 : dp[amount];
    }
};
// @lc code=end

// 测试用例，每个测试用例一个函数段，直接复制修改
// 测试用例1
TEST(coinChange_322, coinChange_322_1)
{
    Solution s;
    vector<int> in = {1, 2, 5};
    int amount = 11;
    int ans = 3;
    // 希望返回值相同
    EXPECT_EQ(s.coinChange_322(in, amount), ans);
}
// 测试用例2
TEST(coinChange_322, coinChange_322_2)
{
    Solution s;
    vector<int> in = {2};
    int amount = 3;
    int ans = -1;
    EXPECT_EQ(s.coinChange_322(in, amount), ans);
}
```

点击`Run CTest tests`测试答案代码。
