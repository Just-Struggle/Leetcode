#include <iostream>
using namespace std;

#include <algorithm>
#include <numeric>
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
    int pre = 1, cur = 1;  //空串解码方法为 1
    for (int i = 1; i < n; ++i) {
        int tmp = cur;  //暂存以 s[i - 1] 结尾的子串的解码方法数
        //以 s[i] 结尾的子串，s[i] 单独解码的方法数或者为 0，或者不变
        if (s[i] == '0') cur = 0;
        //判断 s[i-1] 与 s[i] 能否共同解码
        if (s[i - 1] == '1' || s[i - 1] == '2' && s[i] <= '6')
            cur += pre;  //以 s[i] 结尾的子串，s[i-1] 与 s[i] 共同解码的方法数 =
                         // s[i] 单独解码的方法数 + 以 s[i - 2]
                         //结尾的子串的解码方法数
        pre = tmp;  //以 s[i - 1] 结尾的子串的解码方法数
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
    //{1}如果只有一个元素，加上vector不包含end()所以截取之后没有元素
    vector<int> a = vector<int>(nums.begin(), nums.end() - 1);
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

// 53.最大子序和
int maxSubArray(vector<int>& nums) {
    int n = nums.size(), max_sum = nums[0], sum = nums[0];
    for (int i = 1; i < n; ++i) {
        sum = max(sum + nums[i], nums[i]);
        max_sum = max(max_sum, sum);
    }
    return max_sum;

    /* int n= nums.size(), max_sum = nums[0];
    vector<int> dp(n, nums[0]);
    for(int i = 1; i < n; ++i){
        dp[i] = max(dp[i - 1] + nums[i], nums[i]);
        max_sum = max(max_sum, dp[i]);
    }
    return max_sum; */
}

// 279.完全平方数
int numSquares(int n) {
    vector<int> dp(n + 1, INT_MAX);
    dp[0] = 0;
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j * j <= i; ++j) {
            dp[i] = min(dp[i], dp[i - j * j] + 1);
        }
    }
    return dp[n];
}

// 139.单词拆分
bool wordBreak(string s, vector<string>& wordDict) {
    int n = s.length();
    vector<bool> dp(n + 1, false);
    dp[0] = true;
    for (int i = 1; i <= n; ++i) {
        for (const auto& word : wordDict) {
            int len = word.length();
            /* if (i >= len && word == s.substr(i - len, len))
                dp[i] = dp[i] || dp[i - len]; */

            if (i >= len && word == s.substr(i - len, len)) {
                dp[i] = dp[i - len];
                if (dp[i]) break;
            }
        }
    }
    return dp[n];
}

// 343.整数拆分
int integerBreak(int n) {
    vector<int> dp(n + 1, 1);
    for (int i = 3; i <= n; ++i) {
        for (int j = 1; j * 2 <= i; ++j) {
            dp[i] = max(dp[i], max(dp[i - j] * j, (i - j) * j));
        }
    }
    return dp[n];
}

// 322.零钱兑换
int coinChange(vector<int>& coins, int amount) {
    vector<int> dp(amount + 1, INT_MAX - 1);
    dp[0] = 0;
    for (int i = 1; i <= amount; ++i) {
        for (const auto& coin : coins) {
            if (i >= coin) dp[i] = min(dp[i], dp[i - coin] + 1);
        }
    }
    return dp[amount] == INT_MAX - 1 ? -1 : dp[amount];
}

// 300.最长递增子序列
//动态规划
int lengthOfLIS(vector<int>& nums) {
    int n = nums.size();
    if (n <= 1) return n;
    vector<int> dp(n, 1);
    int max_size = 1;
    for (int i = 1; i < n; ++i) {
        for (int j = 0; j < i; ++j) {
            if (nums[j] < nums[i]) dp[i] = max(dp[i], dp[j] + 1);
        }
        max_size = max(max_size, dp[i]);
    }
    return max_size;
}

//动规 + 二分
int lengthOfLIS(vector<int>& nums) {
    int n = nums.size();
    if (n <= 1) return n;
    vector<int> dp;
    dp.push_back(nums[0]);
    for (int i = 1; i < n; ++i) {
        if (dp.back() < nums[i]) {
            //若 dp 数组最大值小于 nums[i]，增加子序列长度
            dp.push_back(nums[i]);
        } else {
            //找第一个 >= nums[i] 的元素，用 nums[i] 替换这个元素
            //以保证 dp[k-1] 是 min{ 长度为 k 的子序列的最后一个元素 }
            int l = 0, r = dp.size();
            while (l < r) {
                int mid = l + ((r - l) >> 1);
                if (dp[mid] < nums[i])
                    l = mid + 1;
                else
                    r = mid;
            }
            dp[l] = nums[i];
        }
    }
    return dp.size();
}

// 646.最长数对链
//可以类比为给定任务的起始时间和终止时间，如何尽可能多地完成任务
// 动规 + 二分
int findLongestChain(vector<vector<int>>& pairs) {  // 1<=n<=1000
    //注意要先对 pairs 排序，
    //这里采用第一个元素从小到大的排序方式，第一个元素相同时按照第二个元素从小到大排序
    sort(pairs.begin(), pairs.end(), [](const auto& a, const auto& b) {
        return a[0] < b[0] || a[0] == b[0] && a[1] < b[1];
    });
    vector<int> dp;  //只保存数对第二个元素
    dp.push_back(pairs[0][1]);
    for (int i = 1; i < pairs.size(); ++i) {
        int first = pairs[i][0], second = pairs[i][1];
        if (dp.back() < first)  //加入数对
            dp.push_back(second);
        else if (dp.back() > second) {
            // second < 当前数对链末尾元素，有可能替换原有数对
            int l = 0, r = dp.size();
            while (l < r) {
                int mid = l + ((r - l) >> 1);
                if (dp[mid] < first)
                    l = mid + 1;
                else
                    r = mid;
            }
            // l 左侧的值均小于 first，dp[l-1] < first <= dp[l]
            if (dp[l] > second) dp[l] = second;  //替换原有数对
        }
    }
    return dp.size();
}

//贪心
//按结束时间从早到晚排序，每次选最早结束的任务加入队列
int findLongestChain(vector<vector<int>>& pairs) {  // 1<=n<=1000
    //先对 pairs 排序，
    //这里采用第二个元素从小到大的排序方式，第二个元素相同时按照第一个元素从小到大排序
    sort(pairs.begin(), pairs.end(), [](const auto& a, const auto& b) {
        return a[1] < b[1] || a[1] == b[1] && a[0] < b[0];
    });
    int cnt = 0, end = pairs[0][1];
    for (int i = 1; i < pairs.size(); ++i) {
        if (end < pairs[i][0]) {
            end = pairs[i][1];
            ++cnt;
        }
    }
    return cnt;
}

// 1143.最长公共子序列
int longestCommonSubsequence(string text1, string text2) {
    int m = text1.length(), n = text2.length();
    vector<vector<int>> dp(m + 1, vector<int>(n + 1, 0));
    for (int i = 1; i <= m; ++i) {
        for (int j = 1; j <= n; ++j) {
            if (text1[i - 1] == text2[j - 1])
                dp[i][j] = dp[i - 1][j - 1] + 1;  // attention
            else
                dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]);
        }
    }
    return dp[m][n];
}

//与“最大正方形”相似
int longestCommonSubsequence(string text1, string text2) {
    int m = text1.length(), n = text2.length();
    vector<int> dp(n + 1, 0);
    for (int i = 1; i <= m; ++i) {
        int pre = 0;  //保存dp[i-1][j-1]
        for (int j = 1; j <= n; ++j) {
            int tmp = dp[j];  //保存dp[i-1][j]
            if (text1[i - 1] == text2[j - 1])
                dp[j] = pre + 1;
            else
                dp[j] = max(dp[j], dp[j - 1]);
            pre = tmp;  //下一个循环 pre 变成 dp[i-1][j-1]
        }
    }
    return dp[n];
}

// 583.两个字符串的删除操作
int minDistance(string word1, string word2) {
    int m = word1.length(), n = word2.length(),
        sub_len = longestCommonSubsequence(word1, word2);
    return m + n - 2 * sub_len;
}

// 376.摆动序列
//类似于最长递增子序列的 动规 + 二分 做法
// cnt 保存摆动序列的最大长度，last 保存摆动序列的最后一个元素
int wiggleMaxLength(vector<int>& nums) {
    int n = nums.size();
    if (n < 2) return n;
    int cnt = 1, last_diff = 0, last = nums[0];
    //找到第一对不相等的数，特例：[0,0,0,0]
    int i;
    for (i = 1; i < n; ++i) {
        last_diff = nums[i] - last;
        if (last_diff) {
            last = nums[i];
            ++cnt;
            break;
        }
    }
    //若所有元素均相等，返回 1
    if (last_diff == 0) return 1;

    for (; i < n; ++i) {
        int cur_diff = nums[i] - nums[i - 1];
        // 1.若数组中相邻的两个元素的差与摆动序列上一个差值的符号相反，满足条件，更新相关值
        // 2.若相邻的两个元素的差与摆动序列上一个差值的符号相同
        // 2.1.若摆动序列上一个差值 > 0，令序列最后一个元素尽可能大
        // 2.2.若摆动序列上一个差值 < 0，令序列最后一个元素尽可能小
        if (cur_diff > 0 && last_diff < 0 || cur_diff < 0 && last_diff > 0) {
            last_diff = cur_diff;
            last = nums[i];
            ++cnt;
        } else if (last_diff > 0 && nums[i] > last ||
                   last_diff < 0 && nums[i] < last)
            last = nums[i];
    }
    return cnt;
}
//上一种方法麻烦了
int wiggleMaxLength(vector<int>& nums) {
    int n = nums.size();
    if (n < 2) return n;
    int cnt = 1, last_diff = 0;
    //找到第一对不相等的数，特例：[0,0,0,0]
    int i;
    for (i = 1; i < n; ++i) {
        last_diff = nums[i] - nums[0];
        if (last_diff) {
            nums[0] = nums[i];
            ++cnt;
            break;
        }
    }
    //若所有元素均相等，返回 1
    if (last_diff == 0) return 1;

    for (; i < n; ++i) {
        int cur_diff = nums[i] - nums[i - 1];
        if (cur_diff > 0 && last_diff < 0 || cur_diff < 0 && last_diff > 0) {
            //加入摆动序列
            last_diff = cur_diff;
            ++cnt;
        }
    }
    return cnt;
}

// 416.分割等和子集
//相当于 0-1 背包问题，N = nums.size()，W = sum / 2;
bool canPartition(vector<int>& nums) {
    int n = nums.size();
    if (n < 2) return false;
    int sum = accumulate(nums.begin(), nums.end(), 0);
    if (sum % 2) return false;  //数组总和为奇数时，不可能分割出等和子集

    int W = sum / 2;
    vector<bool> dp(W + 1, false);
    dp[0] = true;
    for (int i = 1; i <= n; ++i) {
        int w = nums[i - 1];
        for (int j = W; j >= w; --j) {
            //注意这里是逆向，因为需要用到外层上一循环的两个结果
            // dp[i][j] = dp[i - 1][j] || dp[i - 1][j - w];
            dp[j] = dp[j] || dp[j - w];
        }
    }
    return dp[W];
}

// 474.一和零
int findMaxForm(vector<string>& strs, int m, int n) {
    vector<vector<int>> dp(m + 1, vector<int>(n + 1, 0));
    for (const auto& str : strs) {
        int cnt0 = 0, cnt1 = 0;
        for (int i = 0; i < str.length(); ++i) {
            if (str[i] == '0')
                ++cnt0;
            else
                ++cnt1;
        }
        for (int i = m; i >= cnt0; --i) {
            for (int j = n; j >= cnt1; --j) {
                dp[i][j] = max(dp[i][j], 1 + dp[i - cnt0][j - cnt1]);
            }
        }
    }
    return dp[m][n];
}

// 494.目标和
//总和 = sum，令加法部分总和 = x，则减法部分总和 = sum - x
// S = x - (sum - x) 即 2 * x = (S + sum)，x 必为偶数
//相当于 0-1 背包问题，目标 W = x
int findTargetSumWays(vector<int>& nums, int S) {
    int sum = accumulate(nums.begin(), nums.end(), 0);
    if (abs(S) > sum || (S + sum) % 2 == 1) return 0;

    int W = (S + sum) / 2;
    vector<int> dp(W + 1, 0);
    dp[0] = 1;
    for (int i = 0; i < nums.size(); ++i) {
        int w = nums[i];
        for (int j = W; j >= w; --j) {
            dp[j] = dp[j] + dp[j - w];
        }
    }
    return dp[W];
}

// 72.编辑距离
int minDistance(string word1, string word2) {
    int m = word1.length(), n = word2.length();
    if (m == 0 || n == 0) return max(m, n);
    vector<vector<int>> dp(m + 1, vector<int>(n + 1, 0));
    for (int i = 0; i <= m; ++i)
        dp[i][0] = i;  //一个字符串为空时，通过插入得到另一个字符串
    for (int i = 1; i <= n; ++i)
        dp[0][i] = i;  //一个字符串为空时，通过插入得到另一个字符串

    for (int i = 1; i <= m; ++i) {
        for (int j = 1; j <= n; ++j) {
            dp[i][j] =
                min(dp[i - 1][j - 1] + (word1[i - 1] == word2[j - 1] ? 0 : 1),
                    min(dp[i - 1][j] + 1, dp[i][j - 1] + 1));
        }
    }
    return dp[m][n];
}

// 650.只有两个键的键盘
/* 初始时有一个 A，可以进行 复制全部、粘贴上次复制结果 两种操作 */
int minSteps(int n) {
    if (n == 1) return 0;
    vector<int> dp(n + 1, n);
    dp[2] = 2;
    for (int i = 3; i <= n; ++i) {
        // 1. i 是素数，此时进行 1 次复制，i-1 次粘贴，共 i 次
        // 2. i 是合数，找 i 的最大因数和最小因数，
        //在已输入 max_factor 个 A 的情况下，把这些 A 看作一个整体，还需要
        // dp[min_factor] 次操作
        int max_factor = 1, min_factor = 2;
        while (min_factor <= sqrt(n)) {
            if (i % min_factor == 0) {
                max_factor = i / min_factor;
                break;
            }
            ++min_factor;
        }
        dp[i] = (max_factor == 1) ? i : dp[max_factor] + dp[min_factor];
    }
    return dp[n];
}

// 10.正则表达式匹配
bool isMatch(string s, string p) {
    int m = s.length(), n = p.length();
    vector<vector<int>> dp(m + 1, vector<int>(n + 1, false));
    dp[0][0] = true;
    for (int i = 0; i < n; ++i) {
        if (p[i] == '*') {
            dp[0][i] = dp[0][i - 2];
        }
    }
    for (int i = 1; i < m + 1; ++i) {
        for (int j = 1; j < n + 1; ++j) {
            if (p[j - 1] == '.')  //任意字符均匹配
                dp[i][j] = dp[i - 1][j - 1];
            else if (p[j - 1] != '*')  //是字母
                dp[i][j] = dp[i - 1][j - 1] && p[j - 1] == s[i - 1];
            else {  //是 '*'
                if (p[j - 2] != '.' &&
                    p[j - 2] != s[i - 1])  //与 * 前的字符不匹配
                    dp[i][j] = dp[i][j - 2];
                else  //与 * 前的字符匹配
                    dp[i][j] = dp[i - 1][j] || dp[i][j - 1] || dp[i][j - 2];
            }
        }
    }
    return dp[m][n];
}
bool isMatch(string s, string p) {
    int m = s.size(), n = p.size();
    vector<vector<bool>> dp(m + 1, vector<bool>(n + 1, false));
    dp[0][0] = true;
    for (int i = 1; i < n + 1; ++i) {
        if (p[i - 1] == ’*’) {
            dp[0][i] = dp[0][i - 2];
        }
    }
    for (int i = 1; i < m + 1; ++i) {
        for (int j = 1; j < n + 1; ++j) {
            if (p[j - 1] == ’.’) {
                dp[i][j] = dp[i - 1][j - 1];
            } else if (p[j - 1] != ’*’) {
                dp[i][j] = dp[i - 1][j - 1] && p[j - 1] == s[i - 1];
            } else if (p[j - 2] != s[i - 1] && p[j - 2] != ’.’) {
                dp[i][j] = dp[i][j - 2];
            } else {
                dp[i][j] = dp[i][j - 1] || dp[i - 1][j] || dp[i][j - 2];
            }
        }
    }
    return dp[m][n];
}
