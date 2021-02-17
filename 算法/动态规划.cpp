#include <iostream>
using namespace std;

#include <algorithm>
#include <string>
#include <vector>

struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

/*
1. 特殊情况
2. 状态初始化
3. 状态转移
 */

// 70.爬楼梯
int climbStairs(int n) {
    if (n <= 2) return n;
    int pre = 1, cur = 2;
    for (int i = 3; i <= n; ++i) {
        int tmp = cur;
        cur += pre;
        pre = tmp;
    }
    return cur;
}

// 91.解码方法
int numDecodings(string s) {
    if (s[0] == '0') return 0;
    int n = s.length();
    int pre = 1, cur = 1;
    for (int i = 1; i < n; ++i) {
        int tmp = cur;
        if (s[i] == '0') cur = 0;
        if (s[i - 1] == '1' || s[i - 1] == '2' && s[i] <= '6') cur += pre;

        pre = tmp;
    }
    return cur;
}

// 198.打家劫舍
int rob(vector<int>& nums) {
    int n = nums.size();
    if (n == 0) return 0;

    int pre = 0, cur = nums[0];
    for (int i = 1; i < n; ++i) {
        int tmp = cur;
        cur = max(cur, pre + nums[i]);
        pre = tmp;
    }
    return cur;
}

// 213.打家劫舍II
int rob(vector<int>& nums) {
    int n = nums.size();
    if (n == 0)
        return 0;
    else if (n == 1)
        return nums[0];

    int without_tail = rob(nums, 0, n - 1);
    int without_head = rob(nums, 1, n);

    return max(without_tail, without_head);
}

int rob(vector<int>& nums, int start, int end) {
    if (start == end) return 0;

    int pre = 0, cur = nums[start];
    for (int i = start + 1; i < end; ++i) {
        int tmp = cur;
        cur = max(cur, pre + nums[i]);
        pre = tmp;
    }

    return cur;
}

// 198.by LWK
int rob1(vector<int>& nums) {
    int n = nums.size();
    //特殊情况
    if (n == 0) return 0;
    if (n == 1) return nums[0];
    if (n == 2) return max(nums[0], nums[1]);
    //状态初始化
    int pre = nums[0], res = max(nums[0], nums[1]), tmp;
    //状态转移
    for (int i = 2; i < n; i++) {
        tmp = res;
        res = max(res, pre + nums[i]);
        pre = tmp;
    }
    return res;
}

// 213.by LWK
//注意如何截取vector
int rob(vector<int>& nums) {
    if (nums.size() == 0) return 0;
    if (nums.size() == 1) return nums[0];
    vector<int> a = vector<int>(
        nums.begin(),
        nums.end() -
            1);  //{1}如果只有一个元素，加上vector不包含end()所以截取之后没有元素
    vector<int> b = vector<int>(nums.begin() + 1, nums.end());
    return max(rob1(a), rob1(b));
}

// 413.等差数列划分
int numberOfArithmeticSlices(vector<int>& A) {
    int n = A.size();
    if (n < 3) return 0;
    int cur = 0, sum = 0;
    for (int i = 2; i < n; ++i) {
        if (A[i] + A[i - 2] == A[i - 1] * 2) {
            cur += 1;
            sum += cur;
        } else
            cur = 0;
    }
    return sum;
}

// 62.不同路径
int uniquePaths(int m, int n) {
    vector<int> dp_col(n, 1);
    for (int i = 1; i < m; ++i)
        for (int j = 1; j < n; ++j) dp_col[j] += dp_col[j - 1];
    return dp_col[n - 1];
}

// 64.最小路径和
int minPathSum(vector<vector<int>>& grid) {
    int m = grid.size(), n = grid[0].size();
    vector<int> dp_col(n, INT_MAX);
    dp_col[0] = 0;
    for (int i = 0; i < m; ++i) {
        dp_col[0] += grid[i][0];
        for (int j = 1; j < n; ++j) {
            dp_col[j] = min(dp_col[j], dp_col[j - 1]) + grid[i][j];
        }
    }
    return dp_col[n - 1];
}

// 542.01矩阵
vector<vector<int>> updateMatrix(vector<vector<int>>& matrix) {
    int m = matrix.size(), n = matrix[0].size();
    vector<vector<int>> dp(m, vector<int>(n, INT_MAX - 1));  //防止溢出

    for (int i = 0; i < m; ++i) {
        for (int j = 0; j < n; ++j) {
            if (matrix[i][j] == 0)
                dp[i][j] = 0;
            else {
                if (i > 0) dp[i][j] = dp[i - 1][j] + 1;
                // dp[i][j] = min(dp[i][j], dp[i - 1][j] + 1);
                if (j > 0) dp[i][j] = min(dp[i][j], dp[i][j - 1] + 1);
            }
        }
    }

    for (int i = m - 1; i >= 0; --i) {
        for (int j = n - 1; j >= 0; --j) {
            if (matrix[i][j] != 0) {
                if (i < m - 1) dp[i][j] = min(dp[i][j], dp[i + 1][j] + 1);
                if (j < n - 1) dp[i][j] = min(dp[i][j], dp[i][j + 1] + 1);
            }
        }
    }

    return dp;
}

// 221.最大正方形
int maximalSquare(vector<vector<char>>& matrix) {
    int m = matrix.size(), n = matrix[0].size();
    vector<int> dp_col(n + 1, 0);
    int max_edge = 0;

    for (int i = 1; i <= m; ++i) {
        int pre = 0;

        for (int j = 1; j <= n; ++j) {
            int tmp = dp_col[j];

            if (matrix[i - 1][j - 1] == '0') {
                dp_col[j] = 0;
            } else {
                dp_col[j] = min(pre, min(dp_col[j - 1], tmp)) + 1;
                max_edge = max(max_edge, dp_col[j]);
            }

            pre = tmp;
        }
    }

    return max_edge * max_edge;
}