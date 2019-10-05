// https://www.luogu.org/problem/P4590
// [TJOI2018]游园会

#include <bits/stdc++.h>
using namespace std;

const int MOD = 1000000007;
const int T[3][3] = {{1, 0, 0}, {1, 2, 0}, {1, 0, 3}};
int N, K;
int B[16];
int dp[2][3][1<<15];

void solve() {
    dp[0][0][0] = 1;
    for (int i = 1; i <= N; i++) {
        memset(dp[i&1], 0, sizeof(dp[i&1]));
        for (int x = 0; x < 3; x++) {
            for (int c = 0; c < 3; c++) {
                int x2 = T[x][c];
                if (x2 == 3) continue;
                for (int s = 0; s < (1<<K); s++) {
                    if (dp[(i-1)&1][x][s] == 0) continue;
                    int t1 = 0, t2 = 0, s2 = 0;
                    for (int j = 1; j <= K; j++) {
                        int t3 = max(t2,
                                     t1 + max(int(B[j] == c), (s >> (j-1)) & 1));
                        int d = (t3 - t2);
                        assert(0 <= d && d <= 1);
                        s2 |= (d << (j-1));
                        t2 = t3;
                        t1 += (s >> (j-1)) & 1;
                    }
                    (dp[i&1][x2][s2] += dp[(i-1)&1][x][s]) %= MOD;
                }
            }
        }
    }

    int ans[16] = {0};
    for (int s = 0; s < (1<<K); s++) {
        int d = __builtin_popcount(s);
        for (int x = 0; x < 3; x++) {
            (ans[d] += dp[N&1][x][s]) %= MOD;
        }
    }

    for (int i = 0; i <= K; i++) {
        printf("%d\n", ans[i]);
    }
}

int main() {
    scanf("%d%d", &N, &K);
    string s;
    cin >> s;
    for (int i = 1; i <= K; i++) {
        char c = s[i-1];
        if (c == 'N') B[i] = 0;
        else if (c == 'O') B[i] = 1;
        else B[i] = 2;
    }
    solve();
    return 0;
}
