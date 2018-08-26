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
        if (root) traverse(root, NULL);
    }

    bool hasNext() {
        return curr_;
    }

    TreeNode* next() {
        auto ret = curr_;
        if (curr_->right) {
            auto tmp = curr_->right;
            curr_->right = curr_->left;
            curr_->left = fa_;
            traverse(tmp, curr_);
        } else {
            while (fa_ && fa_->val < curr_->val) {
                auto tmp = fa_->left;
                fa_->left = fa_->right;
                fa_->right = curr_;
                curr_ = fa_;
                fa_ = tmp;
            }
            if (fa_) {
                auto tmp = fa_->left;
                fa_->left = curr_;
                curr_ = fa_;
                fa_ = tmp;
            } else {
                curr_ = fa_;
            }
        }
        return ret;
    }

private:
    TreeNode *curr_ = NULL, *fa_ = NULL;

    void traverse(TreeNode *start, TreeNode *f) {
        curr_ = start;
        fa_ = f;
        while (curr_->left) {
            auto tmp = curr_->left;
            curr_->left = fa_;
            fa_ = curr_;
            curr_ = tmp;
        }
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
