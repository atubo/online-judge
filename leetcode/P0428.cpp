// https://leetcode.com/problems/serialize-and-deserialize-n-ary-tree/
// 428. Serialize and Deserialize N-ary Tree

#include <bits/stdc++.h>
using namespace std;

class Node {
public:
    int val = 0;
    vector<Node*> children;

    Node() {}
    Node(int _val, vector<Node*> _children) {
        val = _val;
        children = _children;
    }
};

class Codec {
public:
    string serialize(Node *root) {
        string ret;
        ret.push_back('[');
        build(root, ret);
        ret.push_back(']');
        return ret;
    }

    void build(Node *root, string &ret) {
        if (!root) return;
        ret.append(to_string(root->val));
        ret.push_back('(');
        ret.append(to_string(root->children.size()));
        ret.push_back(')');

        ret.append("[");
        for (Node *node: root->children) {
            build(node, ret);
        }
        ret.push_back(']');
    }

    Node* deserialize(string data) {
        int p = 0;
        accept(data, p, '[');
        if (peek(data, p) == ']') return NULL;
        Node *root = buildTree(data, p);
        accept(data, p, ']');
        return root;
    }

    void accept(const string &data, int &p, char c) {
        assert(data[p] == c);
        p++;
    }

    char peek(const string &data, int p) {
        return data[p];
    }

    Node* buildTree(const string &data, int &p) {
        int q = data.find('(', p);
        int x = stoi(data.substr(p, q-p));
        Node *node = new Node;
        node->val = x;
        p = q + 1;
        q = data.find(')', p);
        int sz = stoi(data.substr(p, q-p));
        node->children.resize(sz);
        p = q + 1;
        accept(data, p, '[');
        for (int i = 0; i < sz; i++) {
            node->children[i] = buildTree(data, p);
        }
        accept(data, p, ']');
        return node;
    }
};

int main() {
    return 0;
}
