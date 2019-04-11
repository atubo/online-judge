// https://www.luogu.org/problemnew/show/P2514
// [HAOI2010]工厂选址

#include <bits/stdc++.h>
using namespace std;

const int MAXM = 50010, MAXN = 52;
int M, B, N;
int A[MAXM];
int H[MAXN];
int C[MAXM][MAXN];
struct Data {
    int d, i;
    bool operator < (const Data &other) const {
        return d < other.d;
    }
} D[MAXM];

int solve(int idx) {
    for (int i = 0; i < M; i++) {
        D[i] = {C[i][0] - C[i][idx], i};
    }
    sort(D, D+M);
    int c = 0;
    int cost = H[0] + H[idx];
    for (int i = 0; i < M; i++) {
        int k = D[i].i;
        if (A[k] <= B-c) {
            c += A[k];
            cost += C[k][0]*A[k];
        } else {
            int c0 = max(B-c, 0);
            int c1 = A[k] - c0;
            cost += (C[k][0]*c0 + C[k][idx]*c1);
            c += A[k];
        }
    }
    return cost;
}
        
int main() {
    scanf("%d%d%d%d", &M, &B, &H[0], &N);
    for (int i = 0; i < M; i++) {
        scanf("%d", &A[i]);
    }
    for (int i = 1; i <= N; i++) {
        scanf("%d", &H[i]);
    }
    for (int j = 0; j <= N; j++) {
        for (int i = 0; i < M; i++) {
            scanf("%d", &C[i][j]);
        }
    }
    int mx = INT_MAX, mi = -1;
    for (int i = 1; i <= N; i++) {
        int cost = solve(i);
        if (cost < mx) {
            mx = cost;
            mi = i;
        }
    }
    printf("%d\n%d\n", mi, mx);
    return 0;
}
