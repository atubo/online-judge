// https://www.luogu.org/problemnew/show/CF17C
// Balance

#include <bits/stdc++.h>
using namespace std;

const int MOD = 51123987;
const int MAXN = 160;
int N;
char S[MAXN];
int last[MAXN];
int dp[MAXN][52][52][52];
int64_t ans;
int64_t B[52][52];

void build() {
    B[0][0] = 1;
    for (int i = 1; i <= 51; i++) {
        B[i][0] = 1;
        for (int j = 1; j <= i; j++) {
            B[i][j] = (B[i-1][j-1] + B[i-1][j]) % MOD;
        }
    }
}

int64_t binom(int m, int n) {
    if (m < n) return 0;
    return B[m][n];
}

int64_t calc(int m, int n) {
    if (n == 0) return (m == n);
    return binom(m-1, n-1);
}

int64_t mul3(int n1, int n2, int n3, int m1, int m2, int m3) {
    int64_t res = (calc(m1, n1) * calc(m2, n2)) % MOD;
    (res *= calc(m3, n3)) %= MOD;
    return res;
}

void tally(int n1, int n2, int n3, int f) {
    if (f == 0) return;
    const int m = N / 3;
    if (N % 3 == 0) {
        (ans += mul3(n1, n2, n3, m, m, m)*f) %= MOD;
    } else if (N % 3 == 1) {
        (ans += mul3(n1, n2, n3, m+1, m, m)*f) %= MOD;
        (ans += mul3(n1, n2, n3, m, m+1, m)*f) %= MOD;
        (ans += mul3(n1, n2, n3, m, m, m+1)*f) %= MOD;
    } else {
        (ans += mul3(n1, n2, n3, m, m+1, m+1)*f) %= MOD;
        (ans += mul3(n1, n2, n3, m+1, m, m+1)*f) %= MOD;
        (ans += mul3(n1, n2, n3, m+1, m+1, m)*f) %= MOD;
    }
}

int main() {
    build();
    scanf("%d", &N);
    scanf("%s", S+1);
    int pos[3] = {-1, -1, -1};
    for (int i = 1; i <= N; i++) {
        int x = S[i] - 'a';
        last[i] = pos[x];
        pos[x] = i;
    }

    dp[0][0][0][0] = 1;
    for (int i = 1; i <= N; i++) {
        int t = S[i] - 'a';
        for (int n1 = 0; n1 <= min(51, i); n1++) {
            for (int n2 = 0; n2 <= min(51, i-n1); n2++) {
                for (int n3 = 0; n3 <= min(51, i-n1-n2); n3++) {
                    int &res = dp[i][n1][n2][n3];
                    if (t == 0 && n1 > 0) {
                        for (int j = last[i]+1; j < i; j++) {
                            (res += dp[j][n1-1][n2][n3]) %= MOD;
                        }
                    } else if (t == 1 && n2 > 0) {
                        for (int j = last[i]+1; j < i; j++) {
                            (res += dp[j][n1][n2-1][n3]) %= MOD;
                        }
                    } else if (t == 2 && n3 > 0) {
                        for (int j = last[i]+1; j < i; j++) {
                            (res += dp[j][n1][n2][n3-1]) %= MOD;
                        }
                    }
                    tally(n1, n2, n3, res);
                }
            }
        }
    }

    cout << ans << endl;

    return 0;
}
