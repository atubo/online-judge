// https://leetcode.com/problems/serialize-and-deserialize-binary-tree/
// 297. Serialize and Deserialize Binary Tree

#include <bits/stdc++.h>
using namespace std;
#include "../utils/BinaryTree.h"
#include "../utils/Graph.h"
#include "../utils/LinkedList.h"
#include "../utils/Util.h"

class Codec {
public:
    string serialize(TreeNode* root) {
        if (!root) return "";
        string ret = to_string(root->val);
        ret += "(" + serialize(root->left) + ")";
        ret += "(" + serialize(root->right) + ")";
        return ret;
    }

    TreeNode* deserialize(string data) {
        return deserialize(data, 0, data.length());
    }

    TreeNode* deserialize(const string &data, int l, int r) {
        if (l == r) return NULL;
        int val = readInt(data, l);
        int e = findMatch(data, l);
        TreeNode *node = new TreeNode(val);
        node->left = deserialize(data, l+1, e);
        node->right = deserialize(data, e+2, r-1);
        return node;
    }

    int readInt(const string &data, int &l) {
        int f = 1;
        if (data[l] == '-') {
            f = -1;
            l++;
        }
        int ret = 0;
        while (isdigit(data[l])) {
            ret = ret*10 + data[l] - '0';
            l++;
        }
        return ret*f;
    }

    int findMatch(const string &data, int l) {
        assert(data[l] == '(');
        int p = l+1;
        int lp = 1;
        while (true) {
            if (data[p] == '(') lp++;
            if (data[p] == ')') lp--;
            if (lp == 0) break;
            p++;
        }
        return p;
    }
};

int main() {
    return 0;
}
