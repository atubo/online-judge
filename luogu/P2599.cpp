// https://www.luogu.org/problemnew/show/P2599
// [ZJOI2009]取石子游戏

#include <bits/stdc++.h>
using namespace std;

const int MAXN = 1010;
int T, N;
int A[MAXN];
int lft[MAXN][MAXN], rgt[MAXN][MAXN];

void solve() {
    scanf("%d", &N);
    for (int i = 0; i < N; i++) {
        scanf("%d", &A[i]);
        lft[i][i] = rgt[i][i] = A[i];
    }
    for (int len = 2; len < N; len++) {
        for (int i = 1; i <= N-len; i++) {
            int j = i + len - 1;
            int x = A[j];
            int l = lft[i][j-1], r = rgt[i][j-1];
            if (r == x) lft[i][j] = 0;
            else if (x < l && x < r) lft[i][j] = x;
            else if (x < l && x > r) lft[i][j] = x-1;
            else if (x >= l && x < r) lft[i][j] = x+1;
            else {assert(x >= l && x > r); lft[i][j] = x;}
        }
        for (int i = 0; i < N-len; i++) {
            int x = A[i];
            int j = i + len - 1;
            int l = lft[i+1][j], r= rgt[i+1][j];
            if (l == x) rgt[i][j] = 0;
            else if (x < r && x < l) rgt[i][j] = x;
            else if (x < r && x > l) rgt[i][j] = x+1;
            else if (x >= r && x < l) rgt[i][j] = x-1;
            else {assert(x > l && x >= r); rgt[i][j] = x;}
        }
    }
    printf("%d\n", A[0] != lft[1][N-1]);
}

int main() {
    scanf("%d", &T);
    while (T--) {
        solve();
    }
    return 0;
}
