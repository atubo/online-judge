// https://www.lintcode.com/problem/binary-search-tree-iterator/description
// 86. Binary Search Tree Iterator

#include <bits/stdc++.h>
using namespace std;
#include "../utils/BinaryTree.h"
#include "../utils/Graph.h"
#include "../utils/LinkedList.h"
#include "../utils/Util.h"

class BSTIterator {
public:
    BSTIterator(TreeNode *root) {
        if (root) traverse(root);
    }

    bool hasNext() {
        return !st_.empty();
    }

    TreeNode* next() {
        auto ret = st_.top();
        auto curr = ret;
        if (curr->right) {
            traverse(curr->right);
        } else {
            st_.pop();
            while (!st_.empty() && st_.top()->right == curr) {
                curr = st_.top();
                st_.pop();
            }
        }

        return ret;
    }

private:
    stack<TreeNode*> st_;

    void traverse(TreeNode *start) {
        auto curr = start;
        while (curr->left) {
            st_.push(curr);
            curr = curr->left;
        }
        st_.push(curr);
    }
};

int main() {
    TreeNode *root;
    cin >> root;
    BSTIterator it(root);
    while (it.hasNext()) {
        printf("%d ", it.next()->val);
    }
    printf("\n");
    printTree(root);
    return 0;
}
