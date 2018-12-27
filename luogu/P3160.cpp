// https://www.luogu.org/problemnew/show/P3160
// [CQOI2012]局部极小值

#include <bits/stdc++.h>
using namespace std;

const int MOD = 12345678;
const int DX[8] = {0, 1, 1, 1, 0, -1, -1, -1};
const int DY[8] = {1, 1, 0, -1, -1, -1, 0, 1};
int N, M;
int dp[32][1<<8];
int num[1<<8];
int A[4][7];
int ans;

bool inRange(int x, int y) {
    return 0 <= x && x < N && 0 <= y && y < M;
}

void init() {
    memset(dp, -1, sizeof(dp));
    dp[0][0] = 1;
    for (int i = 1; i < (1<<8); i++) {
        dp[0][i] = 0;
    }

    vector<pair<int, int>> p;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            if (A[i][j] == 1) p.push_back({i, j});
        }
    }

    memset(num, 0, sizeof(num));
    int a[4][7];
    int sz = p.size();
    for (int s = 0; s < (1<<sz); s++) {
        memset(a, 0, sizeof(a));
        for (int j = 0; j < sz; j++) {
            int x = p[j].first;
            int y = p[j].second;
            a[x][y] = 1;
            if ((s >> j & 1) == 0) {
                for (int d = 0; d < 8; d++) {
                    int x2 = x + DX[d];
                    int y2 = y + DY[d];
                    if (inRange(x2, y2)) a[x2][y2] = 1;
                }
            }

        }
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < M; j++) {
                num[s] += (a[i][j] == 0);
            }
        }
    }
}

int solve(int i, int s) {
    if (dp[i][s] != -1) return dp[i][s];
    int &ret = dp[i][s] = 0;
    for (int k = 0; k < 8; k++) {
        if (s >> k & 1) (ret += solve(i-1, s-(1<<k))) %= MOD;
    }
    ret += 1LL*(num[s]-(i-1-__builtin_popcount(s))) * solve(i-1, s) % MOD;
    ret %= MOD;
    return ret;
}

void dfs(int x, int y, int sign) {
    if (y == M) {
        dfs(x+1, 0, sign);
        return;
    }
    if (x == N) {
        int cnt = 0;
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < M; j++) {
                cnt += A[i][j];
            }
        }
        init();
        (ans += solve(N*M, (1<<cnt)-1) * sign) %= MOD;
        return;
    }

    dfs(x, y+1, sign);
    if (A[x][y] == 1) return;
    for (int d = 0; d < 8; d++) {
        int x2 = x + DX[d];
        int y2 = y + DY[d];
        if (!inRange(x2, y2)) continue;
        if (A[x2][y2] == 1) {
            return;
        }
    }

    A[x][y] = 1;
    dfs(x, y+1, -sign);
    A[x][y] = 0;
}

int main() {
    scanf("%d%d", &N, &M);
    int cnt = 0;
    for (int i = 0; i < N; i++) {
        char line[10];
        scanf("%s", line);
        for (int j = 0; j < M; j++) {
            A[i][j] = (line[j] == 'X');
            cnt += A[i][j];
        }
    }

    dfs(0, 0, 1);
    printf("%d\n", (ans+MOD) % MOD);

    return 0;
}
