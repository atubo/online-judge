// https://leetcode.com/problems/binary-tree-longest-consecutive-sequence/description/
// 298. Binary Tree Longest Consecutive Sequence

#include "BinaryTree.h"
#include "Graph.h"
#include "LinkedList.h"
#include "Util.h"
#include <bits/stdc++.h>
using namespace std;

class Solution {
    using Node = TreeNode;
    using PII = pair<int, int>;
public:
    int longestConsecutive(Node* root) {
        if (!root) return 0;
        PII ret = traverse(root);
        return ret.second;
    }

    PII traverse(Node* node) {
        PII ret = make_pair(1, 1);
        if (node->left) {
            PII left = traverse(node->left);
            if (node->left->val == node->val + 1) {
                ret.first += left.first;
            }
            ret.second = max(ret.second, left.second);
        }
        if (node->right) {
            PII right = traverse(node->right);
            if (node->right->val == node->val + 1) {
                ret.first = max(ret.first, 1 + right.first);
            }
            ret.second = max(ret.second, right.second);
        }
        ret.second = max(ret.first, ret.second);
        return ret;
    }
};

int main() {
    Solution solution;
    return 0;
}
