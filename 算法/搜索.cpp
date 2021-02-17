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

// 337.打家劫舍III
int rob(TreeNode* root) {
    pair<int, int> result = robTree(root);
    return max(result.first, result.second);
}

// first-rob
// second-not rob
pair<int, int> robTree(TreeNode* cur) {
    if (cur == NULL) return make_pair(0, 0);

    pair<int, int> left = robTree(cur->left);
    pair<int, int> right = robTree(cur->right);
    int rob_cur = cur->val + left.second + right.second;
    int not_rob_cur =
        max(left.first, left.second) + max(right.first, right.second);

    return make_pair(rob_cur, not_rob_cur);
}