// https://www.luogu.org/problemnew/show/P3126
// [USACO15OPEN]回文的路径Palindromic Paths

#include <bits/stdc++.h>
using namespace std;

const int MAXN = 514;
int N;
int A[MAXN][MAXN];
const int MOD = 1e9+7;
const int DX[2] = {0, 1};
const int DY[2] = {1, 0};

bool inRange(int x, int y) {
    return (0 <= x && x < N && 0 <= y && y < N);
}

int dp1[MAXN*MAXN], dp2[MAXN*MAXN];

int encode(int t1, int t2) {
    return (t1 << 9) | t2;
}

int solve() {
    int *p1 = dp1, *p2 = dp2;
    for (int t = 0; t < N; t++) {
        int x = N-1-t, y = t;
        for (int d1 = 0; d1 < 2; d1++) {
            for (int d2 = 0; d2 < 2; d2++) {
                int x1 = x - DX[d1], y1 = y - DY[d1];
                int x2 = x + DX[d2], y2 = y + DY[d2];
                int t1 = y1, t2 = y2 - 1;
                if (inRange(x1, y1) && inRange(x2, y2) &&
                    A[x1][y1] == A[x2][y2]) {
                    p1[encode(t1, t2)]++;
                }
            }
        }
    }

    for (int k = 1; k < N-1; k++) {
        for (int t1 = 0; t1 <= N-1-k; t1++) {
            for (int t2 = max(0, t1-k); t2 <= min(t1+k, N-1-k); t2++) {
                int key = encode(t1, t2);
                if (p1[key] > 0) {
                    int x1 = N-1-k-t1, y1 = t1;
                    int x2 = N-1-t2, y2 = k+t2;
                    for (int d1 = 0; d1 < 2; d1++) {
                        for (int d2 = 0; d2 < 2; d2++) {
                            int x1n = x1 - DX[d1], y1n = y1 - DY[d1];
                            int x2n = x2 + DX[d2], y2n = y2 + DY[d2];
                            if (x1n < 0 || y1n < 0 || x2n >= N || y2n >= N) {
                                continue;
                            }
                            if (A[x1n][y1n] == A[x2n][y2n]) {
                                int t1n = y1n, t2n = y2n-(k+1);
                                (p2[encode(t1n, t2n)] += p1[key]) %= MOD;
                            }
                        }
                    }
                    p1[key] = 0;
                }
            }
        }
        swap(p1, p2);
    }

    return p1[0];
}

int main() {
    scanf("%d", &N);
    char line[MAXN];
    for (int i = 0; i < N; i++) {
        scanf("%s", line);
        for (int j = 0; j < N; j++) {
            A[i][j] = line[j] - 'A';
        }
    }

    int ans = solve();

    printf("%d\n", ans);

    return 0;
}
