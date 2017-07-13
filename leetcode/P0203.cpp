// https://leetcode.com/problems/remove-linked-list-elements/#/description
// 203. Remove Linked List Elements

#include "BinaryTree.h"
#include "Graph.h"
#include "LinkedList.h"
#include "Util.h"
#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    ListNode* removeElements(ListNode* head, int val) {
        ListNode** prev = &head;
        ListNode* curr = head;
        while (curr) {
            ListNode* next = curr->next;
            if (curr->val == val) {
                *prev = curr = next;
            } else {
                prev = &(curr->next);
                curr = curr->next;
            }
        }
        return head;
    }
};

int main() {
    int x;
    cin >> x;
    ListNode* head = readList();
    Solution solution;
    ListNode* ret = solution.removeElements(head, x);
    printList(ret);
    return 0;
}
