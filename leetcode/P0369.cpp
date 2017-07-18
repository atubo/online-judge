// https://leetcode.com/problems/plus-one-linked-list/#/description
// 369. Plus One Linked List

#include "BinaryTree.h"
#include "Graph.h"
#include "LinkedList.h"
#include "Util.h"
#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    ListNode* plusOne(ListNode* head) {
        int carry = addOne(head);
        if (carry) {
            ListNode* nh = new ListNode(1);
            nh->next = head;
            head = nh;
        }
        return head;
    }

    int addOne(ListNode* node) {
        if (!node) return 1;
        int carry = addOne(node->next);
        int s = node->val + carry;
        node->val = s % 10;
        return s >= 10;
    }
};

int main() {
    ListNode* head = readList();
    Solution solution;
    ListNode* ret = solution.plusOne(head);
    printList(ret);
    return 0;
}
