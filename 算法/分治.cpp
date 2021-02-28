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

// 241.为运算表达式设计优先级
unordered_map<string, vector<int>> map;
vector<int> diffWaysToCompute(string input) {
    if (map.count(input)) return map[input];
    vector<int> ways;
    for (int i = 0; i < input.length(); ++i) {
        char c = input[i];
        if (c == '+' || c == '-' || c == '*') {
            vector<int> left = diffWaysToCompute(input.substr(0, i));
            vector<int> right = diffWaysToCompute(input.substr(i + 1));
            for (const int& l : left) {
                for (const int& r : right) {
                    switch (c) {
                        case '+':
                            ways.push_back(l + r);
                            break;
                        case '-':
                            ways.push_back(l - r);
                            break;
                        case '*':
                            ways.push_back(l * r);
                            break;
                    }
                }
            }
        }
    }
    if (ways.empty()) ways.push_back(stoi(input));
    map[input] = ways;
    return ways;
}