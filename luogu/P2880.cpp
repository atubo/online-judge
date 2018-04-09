// https://www.luogu.org/problemnew/show/P2880
// [USACO07JAN]平衡的阵容Balanced Lineup

#include <bits/stdc++.h>
using namespace std;

const int MAXN = 50010;
int N, Q;
int A[MAXN];
int stmax[MAXN][17], stmin[MAXN][17];

void setup() {
    for (int k = 1, len = 2; k < 17; k++, len *= 2) {
        for (int i = 0; i < N; i++) {
            if (i + len <= N) {
                stmax[i][k] = max(stmax[i][k-1], stmax[i+len/2][k-1]);
                stmin[i][k] = min(stmin[i][k-1], stmin[i+len/2][k-1]);
            }
        }
    }
}

void query(int a, int b) {
    for (int k = 16; k >= 0; k--) {
        int len = (1 << k);
        if (a + len <= b) {
            int c = b - len;
            int maxr = max(stmax[a][k], stmax[c][k]);
            int minr = min(stmin[a][k], stmin[c][k]);
            printf("%d\n", maxr - minr);
            break;
        }
    }
}

int main() {
    scanf("%d%d", &N, &Q);
    for (int i = 0; i < N; i++) {
        scanf("%d", &A[i]);
        stmax[i][0] = stmin[i][0] = A[i];
    }

    setup();
    for (int i = 0; i < Q; i++) {
        int a, b;
        scanf("%d%d", &a, &b);
        query(a-1, b);
    }
    return 0;
}
