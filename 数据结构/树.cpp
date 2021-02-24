#include <iostream>
using namespace std;

#include <algorithm>
#include <numeric>
#include <queue>
#include <stack>
#include <string>
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

// 144.二叉树的前序遍历
//迭代 1 模板化
vector<int> preorderTraversal(TreeNode* root) {
    vector<int> ans;
    if (root == nullptr) return ans;
    stack<TreeNode*> s;
    TreeNode* cur = root;
    while (cur != nullptr || !s.empty()) {
        while (cur != nullptr) {
            ans.push_back(cur->val);
            s.push(cur);
            cur = cur->left;
        }
        if (!s.empty()) {
            cur = s.top();
            s.pop();
            cur = cur->right;
        }
    }
    return ans;
}
//迭代 2
vector<int> preorderTraversal(TreeNode* root) {
    vector<int> ans;
    if (root == nullptr) return ans;
    stack<TreeNode*> s;
    s.push(root);
    while (!s.empty()) {
        TreeNode* cur = s.top();
        s.pop();
        ans.push_back(cur->val);
        if (cur->right) s.push(cur->right);
        if (cur->left) s.push(cur->left);
    }
    return ans;
}
//递归
vector<int> preorderTraversal(TreeNode* root) {
    vector<int> ans;
    preorder(root, ans);
    return ans;
}
void preorder(TreeNode* root, vector<int>& ans) {
    if (root == nullptr) {
        return;
    }
    ans.push_back(root->val);
    preorder(root->left, ans);
    preorder(root->right, ans);
}

// 94.二叉树的中序遍历
//迭代 1 模板化
vector<int> inorderTraversal(TreeNode* root) {
    vector<int> ans;
    if (root == nullptr) return ans;
    stack<TreeNode*> s;
    TreeNode* cur = root;
    while (cur != nullptr || !s.empty()) {
        while (cur != nullptr) {
            s.push(cur);
            cur = cur->left;
        }
        if (!s.empty()) {
            cur = s.top();
            s.pop();
            ans.push_back(cur->val);
            cur = cur->right;
        }
    }
    return ans;
}
//递归
vector<int> inorderTraversal(TreeNode* root) {
    vector<int> ans;
    inorder(root, ans);
    return ans;
}
void inorder(TreeNode* root, vector<int>& ans) {
    if (root == nullptr) {
        return;
    }
    inorder(root->left, ans);
    ans.push_back(root->val);
    inorder(root->right, ans);
}

// 145.二叉树的后序遍历
//迭代 1-1 反转向量
vector<int> preorderTraversal(TreeNode* root) {
    vector<int> ans;
    if (root == nullptr) return ans;
    stack<TreeNode*> s;
    s.push(root);
    while (!s.empty()) {
        TreeNode* cur = s.top();
        s.pop();
        ans.push_back(cur->val);
        if (cur->left) s.push(cur->left);
        if (cur->right) s.push(cur->right);
    }
    reverse(ans.begin(), ans.end());
    return ans;
}
//迭代 1-2 用栈逆序输出
vector<int> preorderTraversal(TreeNode* root) {
    vector<int> ans;
    if (root == nullptr) return ans;
    stack<TreeNode*> s, t;
    s.push(root);
    while (!s.empty()) {
        TreeNode* cur = s.top();
        s.pop();
        t.push(cur);
        if (cur->left) s.push(cur->left);
        if (cur->right) s.push(cur->right);
    }
    while (!t.empty()) {
        ans.push_back(t.top()->val);
        t.pop();
    }
    return ans;
}
//递归
vector<int> postorderTraversal(TreeNode* root) {
    vector<int> ans;
    postorder(root, ans);
    return ans;
}
void postorder(TreeNode* root, vector<int>& ans) {
    if (root == nullptr) {
        return;
    }
    postorder(root->left, ans);
    postorder(root->right, ans);
    ans.push_back(root->val);
}

// 104.二叉树的最大深度
int maxDepth(TreeNode* root) {
    if (root == nullptr) return 0;
    return 1 + max(maxDepth(root->left), maxDepth(root->right));
}

// 110.平衡二叉树
bool isBalanced(TreeNode* root) { return helper(root) != -1; }
//是平衡树，返回最大深度
//不是平衡树，返回 -1
int helper(TreeNode* root) {
    if (root == nullptr) return 0;
    int left = helper(root->left), right = helper(root->right);
    //左右子树有一个不平衡，或当前树不平衡
    if (left == -1 || right == -1 || abs(left - right) > 1) return -1;
    return 1 + max(left, right);
}

// 543.二叉树的直径
int diameterOfBinaryTree(TreeNode* root) {
    int diameter = 0;
    helper(root, diameter);
    return diameter;
}
int helper(TreeNode* root, int& diameter) {
    if (root == nullptr) return 0;
    int left = helper(root->left, diameter),
        right = helper(root->right, diameter);
    diameter = max(diameter, left + right);
    return 1 + max(left, right);
}

// 437.路径总和II
int pathSum(TreeNode* root, int sum) {
    if (root == nullptr) return 0;
    return pathSumStartWithRoot(root, sum) + pathSum(root->left, sum) +
           pathSum(root->right, sum);
}
int pathSumStartWithRoot(TreeNode* root, int sum) {
    if (root == nullptr) return 0;
    int cnt = 0;
    if (root->val == sum) cnt = 1;
    cnt += pathSumStartWithRoot(root->left, sum - root->val);
    cnt += pathSumStartWithRoot(root->right, sum - root->val);
    return cnt;
}

// 101.对称二叉树
//递归
bool isSymmetric(TreeNode* root) {
    if (root == nullptr) return true;
    return isSymmetric(root->left, root->right);
}
bool isSymmetric(TreeNode* left, TreeNode* right) {
    if (left == nullptr && right == nullptr) return true;
    if (left == nullptr || right == nullptr) return false;
    if (left->val != right->val) return false;
    return isSymmetric(left->left, right->right) &&
           isSymmetric(left->right, right->left);
}
//迭代 队列
bool isSymmetric(TreeNode* root) {
    if (root == nullptr || root->left == nullptr && root->right == nullptr)
        return true;
    queue<TreeNode*> q;
    q.push(root->left);
    q.push(root->right);
    while (!q.empty()) {
        TreeNode* left = q.front();
        q.pop();
        TreeNode* right = q.front();
        q.pop();
        if (left == nullptr && right == nullptr) continue;
        if (left == nullptr || right == nullptr) return false;
        if (left->val != right->val) return false;
        q.push(left->left);
        q.push(right->right);
        q.push(left->right);
        q.push(right->left);
    }
    return true;
}

// 1110.删点成林
vector<TreeNode*> delNodes(TreeNode* root, vector<int>& to_delete) {
    vector<TreeNode*> forest;
    unordered_set<int> dict(to_delete.begin(), to_delete.end());
    root = helper(root, dict, forest);
    if (root) forest.push_back(root);
    return forest;
}
TreeNode* helper(TreeNode* root, unordered_set<int>& dict,
                 vector<TreeNode*>& forest) {
    if (root == nullptr) return root;
    root->left = helper(root->left, dict, forest);
    root->right = helper(root->right, dict, forest);
    if (dict.count(root->val)) {
        if (root->left) forest.push_back(root->left);
        if (root->right) forest.push_back(root->right);
        root = nullptr;
    }
    return root;
}

// 637.二叉树的层平均值
vector<double> averageOfLevels(TreeNode* root) {
    vector<double> ans;
    if (root == nullptr) return ans;
    queue<TreeNode*> q;
    q.push(root);
    while (!q.empty()) {
        int cnt = q.size();
        double sum = 0;
        for (int i = 0; i < cnt; ++i) {
            TreeNode* cur = q.front();
            q.pop();
            sum += cur->val;
            if (cur->left) q.push(cur->left);
            if (cur->right) q.push(cur->right);
        }
        ans.push_back(sum / cnt);
    }
    return ans;
}