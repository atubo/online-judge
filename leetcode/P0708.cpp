// https://leetcode.com/problems/insert-into-a-cyclic-sorted-list/
// 708. Insert into a Cyclic Sorted List

#include <bits/stdc++.h>
using namespace std;
#include "../utils/BinaryTree.h"
#include "../utils/Graph.h"
#include "../utils/LinkedList.h"
#include "../utils/Util.h"

class Node {
public:
    int val;
    Node* next;

    Node() {}
    Node(int _val, Node* _next) {
        val = _val;
        next = _next;
    }
};

class Solution {
public:
    Node* insert(Node* head, int insertVal) {
        if (!head) {
            auto ret = new Node(insertVal, NULL);
            ret->next = ret;
            return ret;
        }
        Node *p = head, *q = head->next;
        while (true) {
            if (check(p, q, insertVal)) {
                Node *node = new Node(insertVal, q);
                p->next = node;
                return head;
            }
            p = q;
            q = q->next;
            if (p == head) break;
        }
        Node *node = new Node(insertVal, head->next);
        head->next = node;
        return head;
    }

    bool check(Node *p, Node *q, int x) {
        int x1 = p->val, x2 = q->val;
        if (x1 <= x2) return x1 <= x && x <= x2;
        else return x >= x1 || x <= x2;
    }
};

int main() {
    Solution solution;
    return 0;
}
