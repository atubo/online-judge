// https://www.luogu.org/problem/show?pid=2704
// 炮兵阵地

#include <bits/stdc++.h>
using namespace std;

int N, M;
int grid[110];
int dp[2][1024][1024];

bool isFeasible(int r, int k) {
    return ((~r & k) == 0) && ((k & (k << 1)) == 0) && ((k & (k << 2)) == 0);
}


int main() {
    scanf("%d%d", &N, &M);
    char s[20];
    for (int i = 1; i <= N; i++) {
        scanf("%s", s);
        for (int j = 0; j < M; j++) {
            if (s[j] == 'P') {
                grid[i] |= (1 << (M-1-j));
            }
        }
    }
    vector<vector<int>> feasible(N+1);
    feasible[0].push_back(0);
    for (int i = 1; i <= N; i++) {
        for (int k = 0; k < (1 << M); k++) {
            if (isFeasible(grid[i], k)) feasible[i].push_back(k);
        }
    }

    int cur = 0;
    for (int x: feasible[1]) {
        dp[0][0][x] = __builtin_popcount(x);
    }
    for (int i = 2; i <= N; i++) {
        cur ^= 1;
        memset(dp[cur], 0, sizeof(dp[cur]));
        for (int x: feasible[i]) {
            for (int y: feasible[i-1]) {
                if (x & y) continue;
                for (int z: feasible[i-2]) {
                    if ((x & z) == 0) dp[cur][y][x] = max(dp[cur][y][x],
                                                          dp[cur^1][z][y]);
                }
                dp[cur][y][x] += __builtin_popcount(x);
            }
        }
    }

    int ret = 0;
    for (int y: feasible[N-1]) {
        for (int x: feasible[N]) {
            ret = max(ret, dp[cur][y][x]);
        }
    }
    printf("%d\n", ret);
    return 0;
}
