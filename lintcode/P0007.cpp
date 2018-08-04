
#include "../utils/BinaryTree.h"
#include "../utils/Graph.h"
#include "../utils/LinkedList.h"
#include "../utils/Util.h"
#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    string serialize(TreeNode *root) {
        if (!root) return "#";
        string ret = to_string(root->val) + "#";
        return ret + serialize(root->left) + serialize(root->right);
    }

    TreeNode *deserialize(string &data) {
        int p = 0;
        return deserialize(data, p);
    }

    TreeNode *deserialize(const string &data, int &p) {
        int q = p;
        while (data[q] != '#') q++;
        if (p == q) {
            p++;
            return NULL;
        }
        string vs = data.substr(p, q-p);
        TreeNode *node = new TreeNode(stoi(vs));
        p = q + 1;
        node->left = deserialize(data, p);
        node->right = deserialize(data, p);
        return node;
    }
};

int main() {
    Solution solution;
    auto pre = getVector();
    auto in = getVector();
    TreeNode *root = buildTree(pre, in);
    string s = solution.serialize(root);
    cout << s << endl;
    TreeNode *root2 = solution.deserialize(s);
    printTree(root2);

    return 0;
}
