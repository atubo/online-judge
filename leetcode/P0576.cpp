// https://leetcode.com/problems/out-of-boundary-paths/#/description
// 576. Out of Boundary Paths
#include "BinaryTree.h"
#include "Graph.h"
#include "LinkedList.h"
#include "Util.h"
#include <bits/stdc++.h>
using namespace std;

const int DX[4] = {1, 0, -1, 0};
const int DY[4] = {0, 1, 0, -1};

class Solution {
public:
    int64_t add(int64_t a, int64_t b) {
        return (a + b) % 1000000007;
    }

    bool inRange(int x, int y, int M, int N) {
        return (1 <= x && x <= M && 1 <= y && y <= N);
    }

    bool onBoundary(int x, int y, int M, int N) {
        return (x == 0 || x == M+1 || y == 0 || y == N+1);
    }

    int findPaths(int M, int N, int K, int i0, int j0) {
        i0++; j0++;
        int dp[M+2][N+2][K+1];
        memset(dp, 0, sizeof(dp));
        dp[i0][j0][0] = 1;
        int ret = 0;
        for (int k = 1; k <= K; k++) {
            for (int i = 0; i < M+2; i++) {
                for (int j = 0; j < N+2; j++) {
                    for (int d = 0; d < 4; d++) {
                        int x = i + DX[d];
                        int y = j + DY[d];
                        if (inRange(x, y, M, N)) {
                            dp[i][j][k] = add(dp[i][j][k], dp[x][y][k-1]);
                        }
                    }
                    if (onBoundary(i, j, M, N)) {
                        ret = add(ret, dp[i][j][k]);
                    }
                }
            }
        }
        return ret;
    }
};

int main() {
    Solution solution;
    int M, N, K, i, j;
    cin >> M >> N >> K >> i >> j;
    cout << solution.findPaths(M, N, K, i, j) << endl;
    return 0;
}
