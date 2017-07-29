// https://leetcode.com/problems/sparse-matrix-multiplication/description/
// 311. Sparse Matrix Multiplication

#include "BinaryTree.h"
#include "Graph.h"
#include "LinkedList.h"
#include "Util.h"
#include <bits/stdc++.h>
using namespace std;

class Solution {
    using PII = pair<int, int>;
public:
    vector<vector<int>> multiply(vector<vector<int>>& A, vector<vector<int>>& B) {
        const int M = A.size();
        const int R = A[0].size();
        const int N = B[0].size();
        vector<vector<PII>> ma(M);
        for (int i = 0; i < M; i++) {
            for (int j = 0; j < R; j++) {
                if (A[i][j] != 0) {
                    ma[i].push_back(make_pair(j, A[i][j]));
                }
            }
        }

        vector<vector<PII>> mb(R);
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < R; j++) {
                if (B[j][i] != 0) {
                    mb[i].push_back(make_pair(j, B[j][i]));
                }
            }
        }

        vector<vector<int>> ret(M, vector<int>(N));
        for (int i = 0; i < M; i++) {
            for (int j = 0; j < N; j++) {
                ret[i][j] = inner(ma[i], mb[j]);
            }
        }
        return ret;
    }

    int inner(const vector<PII>& a, const vector<PII>& b) {
        int ret = 0;
        int p = 0, q = 0;
        const int M = a.size(), N = b.size();
        while (p < M && q < N) {
            if (a[p].first == b[q].first) {
                ret += a[p++].second * b[q++].second;
            } else if (a[p].first < b[q].first) {
                p++;
            } else {
                q++;
            }
        }
        return ret;
    }
};

int main() {
    Solution solution;
    return 0;
}
