// https://leetcode.com/problems/construct-quad-tree/
// 427. Construct Quad Tree

#include <bits/stdc++.h>
using namespace std;

class Node {
public:
    bool val;
    bool isLeaf;
    Node* topLeft;
    Node* topRight;
    Node* bottomLeft;
    Node* bottomRight;

    Node() {}

    Node(bool _val, bool _isLeaf, Node* _topLeft, Node* _topRight,
         Node* _bottomLeft, Node* _bottomRight) {
        val = _val;
        isLeaf = _isLeaf;
        topLeft = _topLeft;
        topRight = _topRight;
        bottomLeft = _bottomLeft;
        bottomRight = _bottomRight;
    }
};

class Solution {
public:
    Node* construct(vector<vector<int>> &grid) {
        const int n = grid.size();
        vector<vector<int>> ps(n);
        for (int i = 0; i < n; i++) ps[i].resize(n);
        ps[0][0] = grid[0][0];
        for (int i = 1; i < n; i++) {
            ps[0][i] = ps[0][i-1] + grid[0][i];
            ps[i][0] = ps[i-1][0] + grid[i][0];
        }
        for (int i = 1; i < n; i++) {
            for (int j = 1; j < n; j++) {
                ps[i][j] = ps[i-1][j] + ps[i][j-1] + grid[i][j] -
                    ps[i-1][j-1];
            }
        }

        Node* root = build(ps, 0, 0, n, n);
        return root;
    }

    int calcPs(const vector<vector<int>> &ps,
               int x, int y) {
        if (x < 0 || y < 0) return 0;
        return ps[x][y];
    }

    int calcTotal(const vector<vector<int>> &ps,
                  int x1, int y1, int x2, int y2) {
        return calcPs(ps, x2-1, y2-1) - calcPs(ps, x1-1, y2-1)
            - calcPs(ps, x2-1, y1-1) + calcPs(ps, x1-1, y1-1);
    }

    Node* build(const vector<vector<int>> &ps,
                int x1, int y1, int x2, int y2) {
        int tot = calcTotal(ps, x1, y1, x2, y2);
        Node* ret = new Node;
        ret->topLeft = ret->topRight = ret->bottomLeft = ret->bottomRight
            = NULL;
        if (tot == 0) {
            ret->isLeaf = true;
            ret->val = false;
            return ret;
        }
        if (tot == (x2-x1)*(y2-y1)) {
            ret->isLeaf = true;
            ret->val = true;
            return ret;
        }
        ret->isLeaf = false;
        ret->val = true;
        int xmid = (x1 + x2) / 2;
        int ymid = (y1 + y2) / 2;
        ret->topLeft = build(ps, x1, y1, xmid, ymid);
        ret->topRight = build(ps, x1, ymid, xmid, y2);
        ret->bottomLeft = build(ps, xmid, y1, x2, ymid);
        ret->bottomRight = build(ps, xmid, ymid, x2, y2);
        return ret;
    }
};

int main() {
    int n = 4;
    vector<vector<int>> grid(n, vector<int>(n));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            grid[i][j] = 1;
        }
    }


    Solution solution;
    auto root = solution.construct(grid);
    return 0;
}
