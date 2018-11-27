// https://leetcode.com/problems/print-binary-tree/
// 655. Print Binary Tree

#include <bits/stdc++.h>
using namespace std;
#include "../utils/BinaryTree.h"
#include "../utils/Graph.h"
#include "../utils/LinkedList.h"
#include "../utils/Util.h"

void print(const vector<vector<string>> &subtree) {
    for (auto v: subtree) {
        for (auto s: v) {
            printf("\"%s\" ", s.c_str());
        }
        printf("\n");
    }
}


class Solution {
public:
    vector<vector<string>> printTree(TreeNode *root) {
        if (!root) return vector<vector<string>>();
        auto ret = build(root);
        return ret;
    }

private:
    vector<vector<string>> build(TreeNode *root) {
        if (!root) return {{""}};
        auto left = build(root->left);
        auto right = build(root->right);
        return merge(left, right, root);
    }

    vector<vector<string>> merge(vector<vector<string>> &left,
                                 vector<vector<string>> &right,
                                 TreeNode *root) {
        if (!root->left && !root->right) {
            return {{to_string(root->val)}};
        }
        int h1 = left.size();
        int h2 = right.size();
        if (h1 > h2) expand(right, h1);
        if (h2 > h1) expand(left, h2);
        int h = max(h1, h2) + 1;
        vector<vector<string>> ret(h);
        ret[0].assign((1<<h)-1, "");
        ret[0][((1<<h)-1)/2] = to_string(root->val);
        for (int i = 1; i < h; i++) {
            ret[i] = left[i-1];
            ret[i].push_back("");
            copy(right[i-1].begin(), right[i-1].end(),
                 back_inserter(ret[i]));
        }
        return ret;
    }
            
    void expand(vector<vector<string>> &subtree, int h) {
        vector<vector<string>> tmp(h);
        for (int i = 0; i < h; i++) {
            fill_n(back_inserter(tmp[i]), (1<<h)-1, "");
        }
        int h1 = subtree.size();
        for (int i = h1-1; i >= 0; i--) {
            int b1 = (1<<(h1-1-i)) - 1;
            int s1 = 1 << (h1-i);
            int b2 = (1<<(h-1-i)) - 1;
            int s2 = 1 << (h-i);
            for (int j = 0; j < (1<<i); j++) {
                tmp[i][b2+s2*j] = subtree[i][b1+s1*j];
            }
        }
        swap(tmp, subtree);
    }
};

int main() {
    Solution solution;
    TreeNode* root;
    cin >> root;
    //printf("%d\n", root->val);
    auto ret = solution.printTree(root);
    for (auto v: ret) {
        for (auto s: v) {
            printf("\"%s\" ", s.c_str());
        }
        printf("\n");
    }
    return 0;
}
