# C++ 本地调试环境

[![Build Status](https://travis-ci.com/day253/codemaster-cpp.svg?branch=master)](https://travis-ci.com/day253/codemaster-cpp)

## 依赖

- ubuntu
- cmake
- googletest
- visual studio code

### 安装依赖

```shell
# codespace已经自带
sudo apt-get install cmake g++ gdb nodejs npm
# codespace额外安装
sudo apt-get install libgtest-dev
```

## 使用步骤

### 1.配置插件

```bash
# 安装leetcode插件
code --install-extension LeetCode.vscode-leetcode
# 安装CMake 工具插件
code --install-extension ms-vscode.cmake-tools
# 安装Microsoft C/C++ 插件
code --install-extension ms-vscode.cpptools
# 安装CMake 语言插件
code --install-extension twxs.cmake
```

配置插件，这样在sidebar点击题目会自动下载src目录

```
"leetcode.workspaceFolder": "/workspaces/codemaster-cpp/src",
"leetcode.defaultLanguage": "cpp"
```

添加题目后需要`>cmake: Configure`生成编译命令

### 2.本地调试

添加`#include "headers.h"`，修改测试用例，根据需求修改函数名、测试用例输入输出等等，例子如下

```cpp
// 包含"include/headers.h"文件，引入常用头文件
// 如不包含，在"include/headers.h"文件中添加
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

// 测试用例，每个测试用例一个函数段，直接复制修改
TEST(isValid, isValid_1)
{
    Solution s;
    vector<int> in = {1, 2, 3};
    int ans = 1;
    EXPECT_EQ(s.isValid(in), ans);
}
```

执行`>Cmake: Run Tests`测试答案代码。

### 3.提交到测试更多case

`>LeetCode: Submit to LeetCode`提交答案到，如果不通过，添加到本地case直到测试通过再次提交。

### 4.Segmentation fault (core dumped)

```
ulimit -c unlimited

sudo sysctl -w kernel.core_pattern=core.%e.%p
```
