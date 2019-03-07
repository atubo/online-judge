// https://www.luogu.org/problemnew/show/P2943
// [USACO09MAR]清理Cleaning Up

#include <bits/stdc++.h>
using namespace std;

const int MAXN = 40010;
int N, M;
int P[MAXN];
int dp[MAXN];
int E[2][210], L[2][210];

void solve(int i) {
    int curr = i & 1;
    int prev = curr ^ 1;
    int l = 0;
    E[prev][0] = P[i];
    for (int x = 1; x <= 200; x++) {
        if (P[i] == E[prev][l+1]) {
            E[curr][x] = E[prev][l];
            L[curr][x] = L[prev][l+1] + 1;
            l += 2;
        } else {
            E[curr][x] = E[prev][l];
            if (L[prev][l] >= 0) {
                L[curr][x] = L[prev][l] + 1;
            } else {
                L[curr][x] = -1;
            }
            l++;
        }
    }

    dp[i] = i;
    for (int x = 1; x <= 200; x++) {
        if (E[curr][x] == -1) break;
        int d = L[curr][x];
        dp[i] = min(dp[i], dp[i-d] + x*x);
    }
}


int main() {
    memset(E, -1, sizeof(E));
    memset(L, -1, sizeof(L));
    L[0][0] = L[1][0] = 0;
    scanf("%d%d", &N, &M);
    for (int i = 1; i <= N; i++) {
        scanf("%d", &P[i]);
    }
    for (int i = 1; i <= N; i++) {
        solve(i);
    }
    printf("%d", dp[N]);
    return 0;
}
