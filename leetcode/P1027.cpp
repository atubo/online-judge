// https://leetcode.com/problems/longest-arithmetic-sequence/
// 1027. Longest Arithmetic Sequence

#include <bits/stdc++.h>
using namespace std;
#include "../utils/BinaryTree.h"
#include "../utils/Graph.h"
#include "../utils/LinkedList.h"
#include "../utils/Util.h"

class Solution {
public:
    int longestArithSeqLength(vector<int> &A) {
        const int n = A.size();
        vector<unordered_map<int, int>> mp(n);
        int ret = 1;
        for (int i = 1; i < n; i++) {
            for (int j = i-1; j >= 0; j--) {
                int d = A[i] - A[j];
                if (mp[i].find(d) != mp[i].end()) continue;
                if (mp[j].find(d) == mp[j].end()) {
                    mp[i][d] = 2;
                } else {
                    mp[i][d] = 1 + mp[j][d];
                }
                ret = max(ret, mp[i][d]);
            }
        }
        return ret;
    }
};

int main() {
    Solution solution;
    return 0;
}
