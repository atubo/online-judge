// https://leetcode.com/problems/ternary-expression-parser/#/description
// 439. Ternary Expression Parser

#include "BinaryTree.h"
#include "Graph.h"
#include "LinkedList.h"
#include "Util.h"
#include <bits/stdc++.h>
using namespace std;

class Solution {
    struct Expr {
        int type;

        char val;

        bool cond;
        Expr* left;
        Expr* right;
    };

    Expr* parseExpr(const string& expr, int& pos) {
        const int N = expr.length();
        Expr* node = new Expr();
        if (pos <= N-2 && expr[pos+1] == '?') {
            node->type = 1;
            node->cond = parseBool(expr, pos);
            take(expr, '?', pos);
            node->left = parseExpr(expr, pos);
            take(expr, ':', pos);
            node->right = parseExpr(expr, pos);
        } else {
            node->type = 0;
            node->val = parseTerm(expr, pos);
        }
        return node;
    }

    bool parseBool(const string& expr, int& pos) {
        return expr[pos++] == 'T';
    }

    void take(const string& expr, char expected, int& pos) {
        char c = expr[pos++];
        assert(c == expected);
    }

    char parseTerm(const string& expr, int& pos) {
        return expr[pos++];
    }

    char eval(Expr* root) {
        if (root->type == 0) return root->val;
        return root->cond ? eval(root->left) : eval(root->right);
    }

public:
    string parseTernary(string expression) {
        int pos = 0;
        Expr* root = parseExpr(expression, pos);
        assert(pos == (int)expression.length());
        string ret;
        ret.push_back(eval(root));
        return ret;
    }
};

int main() {
    string expr;
    cin >> expr;
    Solution solution;
    cout << solution.parseTernary(expr) << endl;
    return 0;
}
