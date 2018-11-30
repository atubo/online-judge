// https://leetcode.com/problems/basic-calculator-iii/
// 772. Basic Calculator III

#include <bits/stdc++.h>
using namespace std;

struct Node {
    Node(int _op, int64_t _val = 0) {
        op = _op;
        val = _val;
        left = right = NULL;
    }
    int op;
    int64_t val;
    Node *left, *right;
    void print() {
        printf("%d %ld (", op, val);
        if (op != 4) {
            left->print();
            right->print();
        }
        printf(") ");
    }
};

class Solution {
public:
    int calculate(string s) {
        s = trim(s);
        size_t p = 0;
        auto *root = parseExpr(s, p);
        return eval(root);
    }
private:
    string trim(const string &s) {
        string ret;
        for (char c: s) {
            if (c != ' ') ret.push_back(c);
        }
        return ret;
    }

    Node* parseExpr(const string &s, size_t &p) {
        if (p == s.length()) return NULL;
        Node *term = parseTerm(s, p);
        Node *exprp = parseExprp(s, p);
        if (exprp) {
            Node *curr = exprp;
            while (curr->left) curr = curr->left;
            curr->left = term;
        }
        return exprp ? exprp : term;
    }

    Node* parseExprp(const string &s, size_t &p) {
        if (p == s.length()) return NULL;
        if (s[p] != '+' && s[p] != '-') return NULL;
        int op = (s[p] == '+' ? 0 : 1);
        p++;
        Node *node = new Node(op);
        node->right = parseTerm(s, p);
        Node *exprp = parseExprp(s, p);
        if (exprp) {
            Node *curr = exprp;
            while (curr->left) curr = curr->left;
            curr->left = node;
        }
        return exprp ? exprp : node;
    }

    Node* parseTerm(const string &s, size_t &p) {
        if (p == s.length()) return NULL;
        Node *fact = parseFactor(s, p);
        Node *termp = parseTermp(s, p);
        if (termp) {
            Node *curr = termp;
            while (curr->left) curr = curr->left;
            curr->left = fact;
        }
        return termp ? termp: fact;
    }

    Node* parseTermp(const string &s, size_t &p) {
        if (p == s.length()) return NULL;
        if (s[p] != '*' && s[p] != '/') return NULL;
        int op = (s[p] == '*' ? 2 : 3);
        p++;
        Node *node = new Node(op);
        node->right = parseFactor(s, p);
        Node *termp = parseTermp(s, p);
        if (termp) {
            Node *curr = termp;
            while (curr->left) curr = curr->left;
            curr->left = node;
        }
        return termp ? termp : node;
    }

    Node* parseFactor(const string &s, size_t &p) {
        Node *node = NULL;
        if (s[p] == '(') {
            p++;
            node = parseExpr(s, p);
            accept(s, p, ')');
        } else {
            assert('0' <= s[p] && s[p] <= '9');
            string vs;
            while ('0' <= s[p] && s[p] <= '9') {
                vs.push_back(s[p++]);
            }
            node = new Node(4, stol(vs));
        }
        return node;
    }

    void accept(const string &s, size_t &p, char c) {
        assert(s[p] == c);
        p++;
    }

    int eval(Node *root) {
        if (root->op == 4) return root->val;
        eval(root->left);
        eval(root->right);
        switch (root->op) {
            case 0:
                root->val = root->left->val + root->right->val;
                break;
            case 1:
                root->val = root->left->val - root->right->val;
                break;
            case 2:
                root->val = root->left->val * root->right->val;
                break;
            case 3:
                root->val = root->left->val / root->right->val;
                break;
            default:
                assert(0);
                break;
        }
        return root->val;
    }
};

int main() {
    string s;
    getline(cin, s);
    Solution solution;
    cout << solution.calculate(s) << endl;
    return 0;
}
