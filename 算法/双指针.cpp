#include <iostream>
using namespace std;

#include <algorithm>
#include <string>
#include <vector>

struct ListNode {
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};

//剑指 Offer 22.链表中倒数第 k 个节点
ListNode *getKthFromEnd(ListNode *head, int k) {
    ListNode *fast = head;
    while (k--) {
        if (fast == nullptr)
            return nullptr;
        else
            fast = fast->next;
    }
    ListNode *slow = head;
    while (fast) {
        fast = fast->next;
        slow = slow->next;
    }
    return slow;
}

// 19.删除链表的倒数第 N 个节点
/* 与「剑指 Offer 22.链表中倒数第 k 个节点」不同
本题要找到「倒数第 N + 1 个节点」以实现删除功能，故增设哨兵节点 */
ListNode *removeNthFromEnd(ListNode *head, int n) {
    ListNode *dummy = new ListNode(0, head), *slow = dummy, *fast = head;
    while (n--) {
        fast = fast->next;
    }
    while (fast) {
        fast = fast->next;
        slow = slow->next;
    }
    slow->next = slow->next->next;
    return dummy->next;
}

// 75.颜色分类
void sortColors(vector<int> &nums) {
    int left = 0, right = nums.size() - 1;  // n>=1
    for (int i = 0; i <= right; ++i) {
        if (nums[i] == 0) {
            swap(nums[i], nums[left]);
            ++left;
        } else if (nums[i] == 2) {
            swap(nums[i], nums[right]);
            --right;
            if (nums[i] != 1) --i;  //从右侧交换过来的数!=1时需要重新判断
        }
    }
}

// 167.两数之和 II - 输入有序数组
vector<int> twoSum(vector<int> &numbers, int target) {
    int left = 0, right = numbers.size() - 1;
    while (left < right) {
        int sum = numbers[left] + numbers[right];
        if (sum == target)
            break;
        else if (sum < target)
            ++left;
        else  // sum > target
            --right;
    }
    return vector<int>{left + 1, right + 1};
}

// 88.合并两个有序数组
void merge(vector<int> &nums1, int m, vector<int> &nums2, int n) {
    int i = m + n - 1;
    --m;
    --n;
    while (m >= 0 && n >= 0) {
        if (nums1[m] > nums2[n])
            nums1[i--] = nums1[m--];
        else
            nums1[i--] = nums2[n--];
    }
    while (n >= 0) {
        nums1[i--] = nums2[n--];
    }
}

// 142.环形链表Ⅱ
ListNode *detectCycle(ListNode *head) {
    //特殊情况在 if 里可以处理
    ListNode *slow = head, *fast = head;
    do {
        if (fast == nullptr || fast->next == nullptr) return nullptr;
        slow = slow->next;
        fast = fast->next->next;
    } while (slow != fast);
    fast = head;
    while (slow != fast) {
        slow = slow->next;
        fast = fast->next;
    }
    return slow;
}

// 142.环形链表
bool hasCycle(ListNode *head) {
    //特殊情况在 if 里可以处理
    ListNode *slow = head, *fast = head;
    do {
        if (fast == nullptr || fast->next == nullptr) return false;
        slow = slow->next;
        fast = fast->next->next;
    } while (slow != fast);
    return true;
}

// 633.平方数之和
bool judgeSquareSum(int c) {
    long long i = 0, j = sqrt(c);
    while (i <= j) {
        if (i * i + j * j == c)
            return true;
        else if (i * i + j * j < c)
            ++i;
        else
            --j;
    }
    return false;
}

// 524.通过删除字母匹配到字典里最长单词
string findLongestWord(string s, vector<string> &d) {
    string result = "";
    int s_len = s.length(), n = d.size(), result_len = 0;
    for (const auto &word : d) {
        int word_len = word.length();
        // 两种情况下，有可能更新 result
        // 1. result_len < 当前单词的长度 < s_len
        // 2. result_len = 当前单词的长度 且 当前单词的字典序更小
        if ((result_len < word_len && word_len <= s_len) ||
            (word_len == result_len && word < result)) {
            //判断能否通过删除字母得到当前单词
            // p1 遍历 s，p2 遍历当前单词
            int p1 = 0, p2 = 0;
            while (p1 < s_len && p2 < word_len) {
                if (s[p1] == word[p2]) p2++;
                p1++;
            }
            // p2 走到结尾，说明可以通过删除字母得到当前单词，更新相关值
            if (p2 == word_len) {
                result_len = word_len;
                result = word;
            }
        }
    }
    return result;
}