// https://leetcode.com/problems/reverse-linked-list/#/description
// 206. Reverse Linked List

#include "BinaryTree.h"
#include "Graph.h"
#include "LinkedList.h"
#include "Util.h"
#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    ListNode* reverseList(ListNode* head) {
        if (!head) return head;
        ListNode* curr = head;
        ListNode* next = curr->next;
        curr->next = NULL;
        while (next) {
            ListNode* tmp = next->next;
            next->next = curr;
            curr = next;
            next = tmp;
        }
        return curr;
    }
};

int main() {
    Solution solution;
    ListNode* head = readList();
    ListNode* ret = solution.reverseList(head);
    printList(ret);
    return 0;
}
