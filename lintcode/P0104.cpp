// https://www.lintcode.com/problem/merge-k-sorted-lists/description
// 104. Merge K Sorted Lists

#include <bits/stdc++.h>
using namespace std;
#include "../utils/BinaryTree.h"
#include "../utils/Graph.h"
#include "../utils/LinkedList.h"
#include "../utils/Util.h"

class Solution {
    struct Cmp {
        bool operator () (const ListNode *a, const ListNode *b) {
            return a->val > b->val;
        }
    };
public:
    ListNode *mergeKLists(vector<ListNode*> &lists) {
        ListNode *head = NULL, *tail = NULL;
        priority_queue<ListNode*, vector<ListNode*>, Cmp> q;
        for (const auto &l: lists) {
            if (l) q.push(l);
        }
        while (!q.empty()) {
            auto pn = q.top();
            q.pop();
            if (head == NULL) {
                head = tail = pn;
            } else {
                tail->next = pn;
                tail = pn;
            }
            pn = pn->next;
            if (pn) q.push(pn);
        }
        return head;
    }
};

int main() {
    Solution solution;
    int n;
    cin >> n;
    vector<ListNode*> lists(n);
    for (int i = 0; i < n; i++) {
        lists[i] = readList();
    }
    auto ret = solution.mergeKLists(lists);
    printList(ret);
    return 0;
}
