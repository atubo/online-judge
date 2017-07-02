// https://leetcode.com/problems/smallest-range/#/description
// 632. Smallest Range

#include "BinaryTree.h"
#include "Graph.h"
#include "LinkedList.h"
#include "Util.h"
#include <bits/stdc++.h>
using namespace std;

class Solution {
    using PII = pair<int, int>;
public:
    vector<int> smallestRange(vector<vector<int>>& A) {
        const int N = A.size();
        vector<PII> B;
        for (int i = 0; i < N; i++) {
            for (int x: A[i]) {
                B.push_back(make_pair(x, i));
            }
        }
        const int M = B.size();
        sort(B.begin(), B.end());
        vector<int> freq(N, 0);
        int cnt = 0;
        int p = 0, q = 0;
        vector<int> ret = {0, INT_MAX};
        while (true) {
            while (q < M && cnt < N) {
                int x, c;
                tie(x, c) = B[q++];
                mark(c, freq, cnt);
            }
            if (cnt < N) break;
            update(ret, B, p, q-1);
            while (cnt == N) {
                update(ret, B, p, q-1);
                int x, c;
                tie(x, c) = B[p++];
                unmark(c, freq, cnt);
            }
        }

        return ret;
    }

    void mark(int c, vector<int>& freq, int& cnt) {
        if (freq[c] == 0) cnt++;
        freq[c]++;
    }

    void unmark(int c, vector<int>& freq, int& cnt) {
        if (freq[c] == 1) cnt--;
        freq[c]--;
    }

    void update(vector<int>& ret, const vector<PII>& B, int p, int q) {
        int x2 = B[q].first, x1 = B[p].first;
        if (ret[1] - ret[0] > x2 - x1) {
            ret[1] = x2;
            ret[0] = x1;
        }
    }
};

int main() {
    Solution solution;
    vector<vector<int>> A = {{10},{11}};
    auto ret = solution.smallestRange(A);
    printVector(ret);
    return 0;
}
