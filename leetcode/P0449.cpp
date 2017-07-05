// https://leetcode.com/problems/serialize-and-deserialize-bst/#/description
// 449. Serialize and Deserialize BST

#include "BinaryTree.h"
#include "Graph.h"
#include "LinkedList.h"
#include "Util.h"
#include <bits/stdc++.h>
using namespace std;

class Codec {
public:
    string serialize(TreeNode* root) {
        vector<string> items;
        buildItems(root, items);
        return build(items);
    }

    void buildItems(TreeNode* root, vector<string>& items) {
        if (!root) return;
        queue<TreeNode*> q;
        q.push(root);
        while (!q.empty()) {
            TreeNode* node = q.front();
            q.pop();
            items.push_back(node ? to_string(node->val) : "null");
            if (node) {
                q.push(node->left);
                q.push(node->right);
            }
        }
    }

    string build(vector<string>& items) {
        while (!items.empty() && items.back() == "null") items.pop_back();
        const int N = items.size();
        string ret = "[";
        for (int i = 0; i < N; i++) {
            ret += items[i];
            if (i != N-1) ret += ",";
        }
        ret += "]";
        return ret;
    }

    TreeNode* deserialize(string data) {
        int N = data.size();
        data = data.substr(1, N-2);
        if (data.empty()) return NULL;
        vector<string> items;
        int p = 0, q = data.find(',', p);
        while (q != (int)string::npos) {
            items.push_back(data.substr(p, q-p));
            p = q + 1;
            q = data.find(',', p);
        }
        items.push_back(data.substr(p));

        TreeNode* root;
        buildTree(&root, items);
        return root;
    }

    void buildTree(TreeNode** root, const vector<string>& items) {
        queue<TreeNode**> q;
        q.push(root);
        int idx = 0;
        while (!q.empty()) {
            TreeNode** node = q.front();
            q.pop();
            if (idx >= (int)items.size() || items[idx] == "null") {
                *node = NULL;
            } else {
                *node = new TreeNode(stoi(items[idx]));
                q.push(&(*node)->left);
                q.push(&(*node)->right);
            }
            idx++;
        }
    }
};


int main() {
    string s;
    cin >> s;
    Codec c;
    TreeNode* root = c.deserialize(s);
    cout << c.serialize(root) << endl;
    return 0;
}
