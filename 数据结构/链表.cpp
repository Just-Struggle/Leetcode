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
        fast = fast->next->next;
        slow = slow->next;
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
/* 给定一个排序链表，删除所有重复的元素，使得每个元素只出现一次。 */
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

// 82.删除排序链表中的重复元素II
/* 给定一个排序链表，删除所有含有重复数字的节点，只保留原始链表中 没有重复出现
 * 的数字。 */
ListNode *deleteDuplicates(ListNode *head) {
    ListNode *dummy = new ListNode(0, head), *pre = dummy, *cur = head;
    while (cur && cur->next) {  //须要同时判断 cur 和 cur->next
        if (cur->next->val == cur->val) {
            int val = cur->val;  //暂存重复元素
            cur = cur->next->next;
            while (cur && cur->val == val)  //找第一个非空且不重复的元素
                cur = cur->next;
            pre->next = cur;
        } else {
            pre = cur;
            cur = cur->next;
        }
    }
    return dummy->next;
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
    ListNode *mid = middleNode1(head);
    ListNode *pb = mid->next;
    mid->next = nullptr;  // attention!
    ListNode *pa = sortList(head);
    pb = sortList(pb);
    //合
    return mergeTwoLists(pa, pb);  // call 21.
}

/* 给定一个头结点为 head 的非空单链表，返回链表的中间结点。
如果有两个中间结点，则返回第一个中间结点。 */
ListNode *middleNode1(ListNode *head) {  // 234.用到此方法
    ListNode *slow = head, *fast = head;
    while (fast->next &&
           fast->next->next) {  //循环结束时 slow 在中点（奇）或中点左侧（偶）
        fast = fast->next->next;
        slow = slow->next;
    }
    return slow;
}

// 876.链表的中间节点
/* 给定一个头结点为 head 的非空单链表，返回链表的中间结点。
如果有两个中间结点，则返回第二个中间结点。 */
ListNode *middleNode2(ListNode *head) {
    ListNode *slow = head, *fast = head;
    while (fast && fast->next) {
        fast = fast->next->next;
        slow = slow->next;
    }
    return slow;
}

// 147.对链表进行插入排序
ListNode *insertionSortList(ListNode *head) {
    if (head == nullptr || head->next == nullptr) return head;
    ListNode *dummy = new ListNode(0, head), *pre = head, *cur = head->next;
    while (cur != nullptr) {
        //对数组进行插入排序时，从当前索引开始向前找插入位置
        //考虑到单链表只能从头遍历的特点，从哨兵节点出发找插入位置
        ListNode *insert_pos = dummy;
        while (insert_pos->next->val < cur->val) {
            insert_pos = insert_pos->next;
        }

        if (insert_pos != pre) {  //插入位置不是原位置，需进行插入操作
            //暂存插入位置的后一个结点
            ListNode *insert_pos_next = insert_pos->next;
            insert_pos->next = cur;
            pre->next = cur->next;
            cur->next = insert_pos_next;
            cur = pre->next;
        } else {  //插入位置是原位置，无需进行插入操作
            pre = cur;
            cur = cur->next;
        }
    }
    return dummy->next;
}

// by LWK
ListNode *insertionSortList(ListNode *head) {
    //特殊情况，有一个一定是有序的
    if (head == nullptr || head->next == nullptr) return head;

    ListNode *tmp1 = head->next;  //迭代所有节点
    ListNode *tmp2 = nullptr;     //保留tmp1后一个节点
    ListNode *tmp3 = head;        //保留tmp1前一个节点

    while (tmp1 != nullptr) {
        //寻找tmp1该插入的位置
        ListNode *head1 = head;
        ListNode *pre = nullptr;
        while ((head1->val < tmp1->val) && head1 != tmp1) {
            pre = head1;
            head1 = head1->next;
        }

        //分三种情况
        if (pre == nullptr)  //如果比第一个还小,即它应该成为开始结点
        {
            tmp2 = tmp1->next;
            tmp1->next = head;
            tmp3->next = tmp2;
            head = tmp1;
        } else if (tmp1 == head1)  //此时大于前边所有数，在原位置保持不变
        {
            tmp2 = tmp1->next;
            tmp3 = tmp1;
        } else {  //在中间正常插入
            tmp2 = tmp1->next;
            tmp1->next = head1;
            pre->next = tmp1;
            tmp3->next = tmp2;
        }
        tmp1 = tmp2;
    }
    return head;
}

//剑指Offer18.删除链表的节点
/* 给定单向链表的头指针和一个要删除的节点的值，定义一个函数删除该节点。
返回删除后的链表的头节点。
题目保证链表中节点的值互不相同
不需要 free 或 delete 被删除的节点 */
ListNode *deleteNode(ListNode *head, int val) {
    ListNode *dummy = new ListNode(0, head), *cur = dummy;
    while (cur->next->val != val) {
        cur = cur->next;
    }
    cur->next = cur->next->next;
    return dummy->next;
}

// 237.删除链表中的节点
/* 删除单向链表中间的某个节点（即不是第一个或最后一个节点），假定你只能访问该节点*/
void deleteNode(ListNode *node) {
    node->val = node->next->val;
    node->next = node->next->next;
}

//面试题02.05.链表求和
ListNode *addTwoNumbers(ListNode *l1, ListNode *l2) {
    ListNode *dummy = new ListNode(), *cur = dummy;
    int carry = 0;
    while (l1 != nullptr || l2 != nullptr || carry > 0) {
        int num1 = l1 ? l1->val : 0, num2 = l2 ? l2->val : 0,
            sum = num1 + num2 + carry;
        carry = sum / 10;
        cur->next = new ListNode(sum % 10);
        cur = cur->next;
        if (l1) l1 = l1->next;
        if (l2) l2 = l2->next;
    }
    return dummy->next;
}