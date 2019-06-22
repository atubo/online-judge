// https://leetcode.com/problems/strobogrammatic-number-ii/
// 247. Strobogrammatic Number II

#include <bits/stdc++.h>
using namespace std;
#include "../utils/BinaryTree.h"
#include "../utils/Graph.h"
#include "../utils/LinkedList.h"
#include "../utils/Util.h"

class Solution {
public:
    vector<string> findStrobogrammatic(int n) {
        vector<string> ret;
        string s(n, '\0');
        dfs(0, n-1, s, ret);
        return ret;
    }

    void dfs(int l, int r, string &s, vector<string> &ret) {
        static const int S1[3] = {0, 1, 8};
        static vector<pair<int, int>> S2 = {
            {0, 0},{1, 1}, {6, 9}, {8, 8}, {9, 6}
        };
        if (l == r) {
            for (int i = 0; i < 3; i++) {
                s[l] = S1[i] + '0';
                ret.push_back(s);
            }
            return;
        }
        if (l > r) {
            ret.push_back(s);
            return;
        }

        for (int i = (l == 0); i < (int)S2.size(); i++) {
            s[l] = S2[i].first + '0';
            s[r] = S2[i].second + '0';
            dfs(l+1, r-1, s, ret);
        }
    }
};

int main() {
    Solution solution;
    return 0;
}
