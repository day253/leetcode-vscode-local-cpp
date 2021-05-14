/*
 * @lc app=leetcode.cn id=703 lang=cpp
 *
 * [703] 数据流中的第K大元素
 *
 * https://leetcode-cn.com/problems/kth-largest-element-in-a-stream/description/
 *
 * algorithms
 * Easy (42.27%)
 * Likes:    106
 * Dislikes: 0
 * Total Accepted:    13.8K
 * Total Submissions: 32.6K
 * Testcase Example:
 * '["KthLargest","add","add","add","add","add"]\n[[3,[4,5,8,2]],[3],[5],[10],[9],[4]]'
 *
 * 设计一个找到数据流中第K大元素的类（class）。注意是排序后的第K大元素，不是第K个不同的元素。
 *
 * 你的 KthLargest 类需要一个同时接收整数 k
 * 和整数数组nums 的构造器，它包含数据流中的初始元素。每次调用
 * KthLargest.add，返回当前数据流中第K大的元素。
 *
 * 示例:
 *
 *
 * int k = 3;
 * int[] arr = [4,5,8,2];
 * KthLargest kthLargest = new KthLargest(3, arr);
 * kthLargest.add(3);   // returns 4
 * kthLargest.add(5);   // returns 5
 * kthLargest.add(10);  // returns 5
 * kthLargest.add(9);   // returns 8
 * kthLargest.add(4);   // returns 8
 *
 *
 * 说明:
 * 你可以假设 nums 的长度≥ k-1 且k ≥ 1。
 *
 */

#include "headers.h"

// @lc code=start
class KthLargest {
 public:
  KthLargest(int k, vector<int>& nums) : _k(k) {
    for (int i = 0; i < k && i < nums.size(); ++i) {
      _min_heap.push_back(nums[i]);
    }
    build_min_heap();
  }

  int add(int val) {
    if (_min_heap.size() < _k) {
      _min_heap.push_back(val);
      build_min_heap();
    } else {
      if (_min_heap[0] < val) {
        _min_heap[0] = val;
        build_min_heap();
      }
    }
    return _min_heap[0];
  }

  void build_min_heap() {
    for (int i = _min_heap.size() / 2 - 1; i >= 0; --i) {
      min_heap(_min_heap, i, _min_heap.size() - 1);
    }
  }

  void build_max_heap() {
    for (int i = _min_heap.size() / 2 - 1; i >= 0; --i) {
      max_heap(_min_heap, i, _min_heap.size() - 1);
    }
  }

  void static max_heap_sort(vector<int>& nums) {
    for (int i = nums.size() / 2 - 1; i >= 0; --i) {
      max_heap(nums, i, nums.size() - 1);
    }
    for (int i = nums.size() - 1; i > 0; --i) {
      swap(nums[0], nums[i]);
      max_heap(nums, 0, i - 1);
    }
  }
  void static min_heap_sort(vector<int>& nums) {
    for (int i = nums.size() / 2 - 1; i >= 0; --i) {
      min_heap(nums, i, nums.size() - 1);
    }
    for (int i = nums.size() - 1; i > 0; --i) {
      swap(nums[0], nums[i]);
      min_heap(nums, 0, i - 1);
    }
  }
  // 大顶堆
  void static max_heap(vector<int>& nums, int root, int end) {
    int dad = root;
    int son = dad * 2 + 1;
    while (son <= end) {
      if (son + 1 <= end && nums[son] < nums[son + 1]) {
        son += 1;
      }
      if (nums[dad] > nums[son]) {
        return;
      } else {
        swap(nums[dad], nums[son]);
        dad = son;
        son = dad * 2 + 1;
      }
    }
  }
  // 小顶堆
  void static min_heap(vector<int>& nums, int root, int end) {
    int dad = root;
    int son = dad * 2 + 1;
    while (son <= end) {
      if (son + 1 <= end && nums[son] > nums[son + 1]) {
        son += 1;
      }
      if (nums[dad] < nums[son]) {
        return;
      } else {
        swap(nums[dad], nums[son]);
        dad = son;
        son = dad * 2 + 1;
      }
    }
  }

 private:
  vector<int> _min_heap;
  int _k = 0;
};

/**
 * Your KthLargest object will be instantiated and called as such:
 * KthLargest* obj = new KthLargest(k, nums);
 * int param_1 = obj->add(val);
 */
// @lc code=end

TEST(KthLargest, KthLargest1) {
  vector<int> nums = {
      4,
      5,
      8,
      2,
  };
  KthLargest obj(3, nums);
  EXPECT_EQ(4, obj.add(3));
  EXPECT_EQ(5, obj.add(5));
  EXPECT_EQ(5, obj.add(10));
  EXPECT_EQ(8, obj.add(9));
  EXPECT_EQ(8, obj.add(4));
}

TEST(KthLargest, KthLargest2) {
  vector<int> nums = {
      4,
      5,
      8,
      2,
  };
  KthLargest::max_heap_sort(nums);
  EXPECT_EQ(2, nums[0]);
  EXPECT_EQ(4, nums[1]);
  EXPECT_EQ(5, nums[2]);
  EXPECT_EQ(8, nums[3]);
}

TEST(KthLargest, KthLargest3) {
  vector<int> nums = {
      4,
      5,
      8,
      2,
  };
  KthLargest::min_heap_sort(nums);
  EXPECT_EQ(8, nums[0]);
  EXPECT_EQ(5, nums[1]);
  EXPECT_EQ(4, nums[2]);
  EXPECT_EQ(2, nums[3]);
}

TEST(KthLargest, KthLargest4) {
  vector<int> nums = {};
  KthLargest obj(1, nums);
  EXPECT_EQ(-3, obj.add(-3));
  EXPECT_EQ(-2, obj.add(-2));
  EXPECT_EQ(-2, obj.add(-4));
  EXPECT_EQ(0, obj.add(0));
  EXPECT_EQ(4, obj.add(4));
}

TEST(KthLargest, KthLargest5) {
  vector<int> nums = {
      0,
  };
  KthLargest obj(2, nums);
  EXPECT_EQ(-1, obj.add(-1));
  EXPECT_EQ(0, obj.add(1));
  EXPECT_EQ(0, obj.add(-2));
  EXPECT_EQ(0, obj.add(-4));
  EXPECT_EQ(1, obj.add(3));
}

TEST(KthLargest, KthLargest6) {
  vector<int> nums = {
      -10, 1, 3, 1, 4, 10, 3, 9, 4, 5, 1,
  };
  KthLargest obj(7, nums);
  vector<int> inputs = {
      3, 2, 3, 1,  2,  4, 5, 5, 6, 7, 7, 8, 2, 3,
      1, 1, 1, 10, 11, 5, 6, 2, 4, 7, 8, 5, 6,
  };
  vector<int> results = {
      3, 3, 3, 3, 3, 3, 4, 4, 4, 5, 5, 5, 5, 5,
      5, 5, 5, 6, 7, 7, 7, 7, 7, 7, 7, 7, 7,
  };
  EXPECT_EQ(inputs.size(), results.size());
  for (int i = 0; i < inputs.size(); ++i) {
    EXPECT_EQ(results[i], inputs[i]);
  }
}