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

// 206.反转链表
ListNode *reverseList(ListNode *head) {
    ListNode *prev = head, *new_head = nullptr;
    while (prev) {
        ListNode *tmp = prev->next;
        prev->next = new_head;
        new_head = prev;
        prev = tmp;
    }
    return new_head;
}

// 21.合并两个有序链表
ListNode *mergeTwoLists(ListNode *l1, ListNode *l2) {
    ListNode *dummy = new ListNode(), *cur = dummy;
    while (l1 && l2) {
        if (l1->val <= l2->val) {
            cur->next = l1;
            l1 = l1->next;
        } else {
            cur->next = l2;
            l2 = l2->next;
        }
        cur = cur->next;
    }
    if (l1)
        cur->next = l1;
    else
        cur->next = l2;
    return dummy->next;
}

// 24.两两交换链表中的节点
ListNode *swapPairs(ListNode *head) {
    ListNode *dummy = new ListNode(0, head), *cur = dummy;
    while (cur->next && cur->next->next) {
        ListNode *tmp = cur->next;
        cur->next = tmp->next;
        cur = cur->next;
        tmp->next = cur->next;
        cur->next = tmp;
        cur = tmp;
    }
    return dummy->next;
}

// 160.相交链表
ListNode *getIntersectionNode(ListNode *headA, ListNode *headB) {
    ListNode *pa = headA, *pb = headB;
    while (pa != pb) {
        pa = pa ? pa->next : headB;
        pb = pb ? pb->next : headA;
    }
    return pa;
}

// 234.回文链表
bool isPalindrome(ListNode *head) {
    if (!head || !head->next) return true;
    ListNode *slow = head, *fast = head;
    while (fast->next && fast->next->next) {
        slow = slow->next;
        fast = fast->next->next;
    }
    slow->next = reverseList(slow->next);  // 206.
    slow = slow->next;
    fast = head;
    while (slow) {
        if (fast->val == slow->val) {
            fast = fast->next;
            slow = slow->next;
        } else
            return false;
    }
    return true;
}