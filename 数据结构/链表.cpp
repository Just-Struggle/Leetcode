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
    ListNode *prev = nullptr, *next;
    while (head) {
        next = head->next;
        head->next = prev;
        prev = head;
        head = next;
    }
    return prev;
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
    cur->next = l1 ? l1 : l2;
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
// 求两个无环单链表相交的第一个节点，若不相交返回空指针
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
    while (fast->next &&
           fast->next->next) {  //循环结束时 slow 在中点（奇）或中点左侧（偶）
        slow = slow->next;
        fast = fast->next->next;
    }
    slow->next = reverseList(slow->next);  // 翻转后半段链表，call 206.
    ListNode *mid = slow;  //保存分界点，便于后面恢复数据
    slow = slow->next;
    fast = head;
    while (slow) {
        if (fast->val == slow->val) {
            fast = fast->next;
            slow = slow->next;
        } else
            return false;
    }
    mid->next = reverseList(fast->next);  //恢复数据
    return true;
}

// 83.删除排序链表中的重复元素
ListNode *deleteDuplicates(ListNode *head) {
    if (head == nullptr) return nullptr;
    ListNode *cur = head;
    while (cur->next) {
        if (cur->val == cur->next->val)
            cur->next =
                cur->next
                    ->next;  //更新了cur->next，这个值还未与cur比较，故不需要更新cur
        else
            cur = cur->next;
    }
    return head;
}

// 328.奇偶链表
ListNode *oddEvenList(ListNode *head) {
    if (head == nullptr || head->next == nullptr || head->next->next == nullptr)
        return head;  //节点数小于等于2
    ListNode *odd = head, *even = head->next, *even_head = even,
             *cur = even->next;
    while (cur) {  //判断是否还有未处理的节点
        //处理奇数节点
        odd->next = cur;
        odd = odd->next;
        cur = cur->next;
        //处理偶数节点
        if (cur) {
            even->next = cur;
            even = even->next;
            cur = cur->next;
        }
    }
    odd->next = even_head;
    even->next = nullptr;  // attention!
    return head;
}

// 148.排序链表
ListNode *sortList(ListNode *head) {
    if (head == nullptr || head->next == nullptr) return head;
    //分
    ListNode *mid = findMid(head);
    ListNode *pb = mid->next;
    mid->next = nullptr;  // attention!
    ListNode *pa = sortList(head);
    pb = sortList(pb);
    //合
    return mergeTwoLists(pa, pb);  // call 21.
}

ListNode *findMid(ListNode *head) {  // 234.用到此方法
    ListNode *slow = head, *fast = head;
    while (fast->next &&
           fast->next->next) {  //循环结束时 slow 在中点（奇）或中点左侧（偶）
        slow = slow->next;
        fast = fast->next->next;
    }
    return slow;
}

// 147.对链表进行插入排序
ListNode *insertionSortList(ListNode *head) {}