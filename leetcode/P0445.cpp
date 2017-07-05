// https://leetcode.com/problems/add-two-numbers-ii/#/description
// 445. Add Two Numbers II

#include "BinaryTree.h"
#include "Graph.h"
#include "LinkedList.h"
#include "Util.h"
#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
        int len1 = length(l1), len2 = length(l2);
        if (len1 < len2) {
            swap(l1, l2);
            swap(len1, len2);
        }
        ListNode* l1p = forward(l1, len1-len2);

        ListNode *tail, *head;
        int carry = 0;
        tie(tail, carry) = add(l1p, l2, carry);
        tie(head, carry) = inc(l1, l1p, carry, tail);
        if (carry) {
            tie(head, ignore) = buildNode(0, 0, carry, head);
        }
        return head;
    }

    int length(ListNode* head) {
        int ret = 0;
        while (head) {
            head = head->next;
            ret++;
        }
        return ret;
    }

    ListNode* forward(ListNode* head, int d) {
        for (int i = 0; i < d; i++) {
            head = head->next;
        }
        return head;
    }

    pair<ListNode*, int> buildNode(int x, int y, int carry, ListNode* tail) {
        int v = (x + y + carry) % 10;
        int c = (x + y + carry) / 10;
        ListNode* node = new ListNode(v);
        node->next = tail;
        return make_pair(node, c);
    }

    pair<ListNode*, int> inc(ListNode* curr, ListNode* end, int carry,
                             ListNode* tail) {
        if (curr == end) return make_pair(tail, carry);
        tie(tail, carry) = inc(curr->next, end, carry, tail);
        return buildNode(curr->val, 0, carry, tail);
    }

    pair<ListNode*, int> add(ListNode* l1, ListNode* l2, int carry) {
        if (!l1) return make_pair((ListNode*)NULL, carry);
        ListNode* tail;
        tie(tail, carry) = add(l1->next, l2->next, carry);
        return buildNode(l1->val, l2->val, carry, tail);
    }
};

int main() {
    Solution solution;
    return 0;
}
