// https://www.luogu.org/problem/P4253
// [SCOI2015]小凸玩密室

#include <bits/stdc++.h>
using namespace std;

const int MAXN = 200010;
int N;
int64_t A[MAXN], B[MAXN], D[MAXN], L[MAXN];
int64_t F[MAXN][19], G[MAXN][19];

void dp() {
    for (int x = N; x > 0; x--) {
        for (int i = L[x]-1; i >= 0; i--) {
            int lc = x << 1;
            int rc = lc + 1;
            int target = (x >> (L[x]-i-1)) ^ 1;
            if (lc > N) {
                F[x][i] = A[target] * (D[x] + D[target] - D[target/2]*2);
            } else if (rc > N) {
                F[x][i] = A[lc] * B[lc] + F[lc][i];
            } else {
                F[x][i] = min(A[lc]*B[lc] + F[lc][L[x]] + F[rc][i],
                              A[rc]*B[rc] + F[rc][L[x]] + F[lc][i]);
            }
        }
    }

    for (int x = N; x > 0; x--) {
        for (int i = L[x]-1; i >= 0; i--) {
            int lc = x << 1;
            int rc = lc + 1;
            int target = x >> (L[x]-i);
            if (lc > N) {
                G[x][i] = A[target] * (D[x] - D[target]);
            } else if (rc > N) {
                G[x][i] = A[lc] * B[lc] + G[lc][i];
            } else {
                G[x][i] = min(A[lc]*B[lc] + F[lc][L[x]] + G[rc][i],
                              A[rc]*B[rc] + F[rc][L[x]] + G[lc][i]);
            }
        }
    }
}

int64_t calc(int x) {
    int64_t ret = G[x][L[x]-1];
    for (; x != 1; x >>= 1) {
        int br = x ^ 1, fa = x >> 1;
        if (br > N) {
            ret += A[fa>>1] * B[fa];
        } else {
            ret += A[br] * B[br] + G[br][L[fa]-1];
        }
    }
    return ret;
}

int64_t solve() {
    int64_t ret = G[1][0];
    for (int i = 2; i <= N; i++) {
        ret = min(ret, calc(i));
    }
    return ret;
}

int main() {
    scanf("%d", &N);
    for (int i = 1; i <= N; i++) {
        scanf("%ld", &A[i]);
    }

    for (int i = 2; i <= N; i++) {
        scanf("%ld", &B[i]);
    }
    
    L[1] = 1, D[1] = 0;
    for (int i = 2; i <= N; i++) {
        L[i] = L[i>>1] + 1;
        D[i] = D[i>>1] + B[i];
    }

    dp();
    printf("%ld\n", solve());
    return 0;
}
