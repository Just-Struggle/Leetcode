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