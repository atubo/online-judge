// https://www.lintcode.com/problem/sparse-matrix-multiplication/description
// 654. Sparse Matrix Multiplication

#include <bits/stdc++.h>
using namespace std;

#include "../utils/Util.h"

class Solution {
public:
    vector<vector<int>> multiply(vector<vector<int>> &A,
                                 vector<vector<int>> &B) {
        int r1 = A.size();
        int c1 = A[0].size();
        int c2 = B[0].size();
        vector<vector<int>> cols(c1);
        for (int i = 0; i < c1; i++) {
            for (int j = 0; j < c2; j++) {
                if (B[i][j] != 0) {
                    cols[i].push_back(j);
                }
            }
        }

        vector<vector<int>> ret(r1);
        for (int i = 0; i < r1; i++) ret[i].resize(c2);
        for (int i = 0; i < r1; i++) {
            for (int k = 0; k < c1; k++) {
                if (A[i][k] != 0) {
                    for (int j: cols[k]) {
                        ret[i][j] += A[i][k] * B[k][j];
                    }
                }
            }
        }
        return ret;
    }
};

int main() {
    auto A = getMatrix();
    auto B = getMatrix();
    Solution solution;
    auto C = solution.multiply(A, B);
    printMatrix(C);
    return 0;
}
