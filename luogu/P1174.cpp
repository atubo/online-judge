// https://www.luogu.org/problem/show?pid=1174
// 打砖块

#include <bits/stdc++.h>
using namespace std;

const int MAXN = 210;
int N, M, K;
int A[MAXN][MAXN], B[MAXN][MAXN];
int dp_x[MAXN][MAXN], dp_y[MAXN][MAXN];
int dx[MAXN][MAXN], dy[MAXN][MAXN];

int main() {
    scanf("%d %d %d", &N, &M, &K);
    for (int i = N; i >= 1; i--) {
        for (int j = 1; j <= M; j++) {
            char c;
            scanf("%d %c", &A[j][i], &c);
            B[j][i] = (c == 'Y');
        }
    }
    swap(N, M);

    for (int i = 1; i <= N; i++) {
        int k = 1;
        while (k <= M && B[i][k]) {
            dy[i][0] += A[i][k];
            k++;
        }

        for (int j = 1; j <= M && k <= M; j++) {
            dx[i][j] = dy[i][j-1] + A[i][k];
            dy[i][j] = dx[i][j];
            k++;
            while (k <= M && B[i][k]) {
                dy[i][j] += A[i][k];
                k++;
            }
        }
    }

    for (int i = 1; i <= N; i++) {
        for (int k = 0; k <= K; k++) {
            for (int x = 0; x <= k; x++) {
                dp_y[i][k] = max(dp_y[i][k], dp_y[i-1][k-x] + dy[i][x]);
                if (x < k) dp_x[i][k] = max(dp_x[i][k], dp_x[i-1][k-x] + dy[i][x]);
                if (x > 0) dp_x[i][k] = max(dp_x[i][k], dp_y[i-1][k-x] + dx[i][x]);
            }
        }
    }

    printf("%d\n", dp_x[N][K]);

    return 0;
}
