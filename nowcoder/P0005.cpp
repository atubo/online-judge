//  从尾到头打印链表
#include "LinkedList.h"
#include "Util.h"
#include <bits/stdc++.h>
using namespace std;

class Solution {
    using Node = ListNode;
    void add(Node* head, vector<int>& v) {
        if (!head) return;
        add(head->next, v);
        v.push_back(head->val);
    }
public:
    vector<int> printListFromTailToHead(ListNode* head) {
        vector<int> ret;
        add(head, ret);
        return ret;
    }
};

int main() {
    auto l = readList();
    Solution solution;
    auto v = solution.printListFromTailToHead(l);
    printVector(v);
    return 0;
}
