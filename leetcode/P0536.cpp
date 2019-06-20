// https://leetcode.com/problems/construct-binary-tree-from-string/
// 536. Construct Binary Tree from String

#include <bits/stdc++.h>
using namespace std;
#include "../utils/BinaryTree.h"
#include "../utils/Graph.h"
#include "../utils/LinkedList.h"
#include "../utils/Util.h"

class Solution {
public:
    TreeNode *str2tree(string s) {
        return parse(s, 0, s.length());
    }

private:
    TreeNode* parse(const string &s, int p0, int q) {
        int p = p0;
        if (p == q) return NULL;
        int val = parseNumber(s, p);
        TreeNode *curr = new TreeNode(val);
        int r = INT_MAX;
        if (p < q) {
            r = findRight(s, p);
            curr->left = parse(s, p+1, r);
        }
        if (r < q-1) {
            int r2 = findRight(s, r+1);
            curr->right = parse(s, r+2, r2);
        }
        return curr;
    }

    int parseNumber(const string &s, int &p) {
        assert(s[p] == '-' || ('0' <= s[p] && s[p] <= '9'));
        int f = 1;
        if (s[p] == '-') {
            f = -1;
            p++;
        }
        int ret = 0;
        while ('0' <= s[p] && s[p] <= '9') {
            ret = ret*10 + s[p] - '0';
            p++;
        }
        return ret*f;
    }

    int findRight(const string  &s, int p) {
        assert(s[p] == '(');
        int cnt = 0;
        while (true) {
            if (s[p] == '(') cnt++;
            if (s[p] == ')') cnt--;
            if (cnt == 0) break;
            p++;
        }
        return p;
    }
};

int main() {
    string s;
    cin >> s;
    Solution solution;
    solution.str2tree(s);
    return 0;
}
