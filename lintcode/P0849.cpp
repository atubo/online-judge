// https://www.lintcode.com/problem/basic-calculator-iii/description
// 849. Basic Calculator III

#include <bits/stdc++.h>
using namespace std;
#include "../utils/BinaryTree.h"
#include "../utils/Graph.h"
#include "../utils/LinkedList.h"
#include "../utils/Util.h"

class Solution {
    struct Expr {
        int type;
        int64_t val;
        Expr *left, *right;
        Expr(int t): type(t), val(0), left(NULL), right(NULL) {}
    };

public:
    int calculate(string &s0) {
        string s;
        for (char c: s0) {
            if (c != ' ' && c != '\t') {
                s.push_back(c);
            }
        }
        const int n = s.length();
        Expr *root = parse(s, 0, n-1);
        return eval(root);
    }

    Expr* parse(const string &s, int left, int right) {
        if (right < left) return NULL;
        int p = -1, q = -1, cnt = 0;
        for (int i = right; i >= left; i--) {
            if (s[i] == ')') cnt++;
            if (s[i] == '(') cnt--;
            if (cnt == 0) {
                if ((s[i] == '+' || s[i] == '-') && p == -1) p = i;
                if ((s[i] == '*' || s[i] == '/') && q == -1) q = i;
            }
        }
        Expr *node;
        if (p != -1) {
            int t = (s[p] == '+' ? 0 : 1);
            node = new Expr(t);
            node->left = parse(s, left, p-1);
            node->right = parse(s, p+1, right);
        } else if (q != -1) {
            int t = (s[q] == '*' ? 2: 3);
            node = new Expr(t);
            node->left = parse(s, left, q-1);
            node->right = parse(s, q+1, right);
        } else if (s[right] == ')') {
            node = parse(s, left+1, right-1);
        } else {
            node = new Expr(4);
            node->val = stol(s.substr(left, right-left+1));
        }
        return node;
    }

    int eval(Expr *node) {
        int ret;
        switch (node->type) {
            case 0:
                ret = eval(node->left) + eval(node->right);
                break;
            case 1:
                ret = eval(node->left) - eval(node->right);
                break;
            case 2:
                ret = eval(node->left) * eval(node->right);
                break;
            case 3:
                ret = eval(node->left) / eval(node->right);
                break;
            case 4:
                ret = node->val;
                break;
            default:
                break;
        }
        return ret;
    }
};

int main() {
    Solution solution;
    string s;
    getline(cin, s);
    cout << solution.calculate(s) << endl;
    return 0;
}
