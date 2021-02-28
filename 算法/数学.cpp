#include <iostream>
using namespace std;

#include <algorithm>
#include <numeric>
#include <queue>
#include <stack>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode* left, TreeNode* right)
        : val(x), left(left), right(right) {}
};

// 204.计数质数
//统计所有小于非负整数 n 的质数的数量
int countPrimes(int n) {
    if (n <= 2) return 0;  // 1
    vector<bool> prime(n, true);
    int cnt = n - 2;  //去掉 1
    for (int i = 2; i < n; ++i) {
        if (prime[i]) {  //减少重复计算
            for (int j = 2 * i; j < n; j += i) {
                if (prime[j]) {
                    prime[j] = false;
                    --cnt;
                }
            }
        }
    }
    return cnt;
}

// 504.七进制数
string convertToBase7(int num) {
    if (num == 0) return "0";
    bool is_positive = num > 0;
    if (!is_positive) num = -num;
    string s;
    while (num) {
        s = to_string(num % 7) + s;
        num = num / 7;
    }
    return (is_positive ? "" : "-") + s;
}

// 172.阶乘后的零
int trailingZeroes(int n) { return n < 5 ? 0 : n / 5 + trailingZeroes(n / 5); }

// 415.字符串相加
string addStrings(string num1, string num2) {
    string s;
    int carry = 0;
    int i = num1.length() - 1, j = num2.length() - 1;
    while (i >= 0 || j >= 0 || carry != 0) {
        int tmp = carry;
        if (i >= 0) tmp += num1[i--] - '0';
        if (j >= 0) tmp += num2[j--] - '0';
        carry = tmp / 10;
        s = (char)(tmp % 10 + '0') + s;
    }
    return s;
}