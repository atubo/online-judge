// https://www.luogu.org/problem/show?pid=2716
// 和谐的雪花

#include <bits/stdc++.h>
using namespace std;

const int MAXN = 510;
int minst[MAXN][MAXN][10];
int maxst[MAXN][MAXN][10];
int N, M, K;
int A[MAXN][MAXN];

int min4(int x1, int x2, int x3, int x4) {
    return min(min(x1, x2), min(x3, x4));
}

int max4(int x1, int x2, int x3, int x4) {
    return max(max(x1, x2), max(x3, x4));
}

bool feasible(int x) {
    int k = 1;
    int d = 0;
    while (2*k < x) {
        k *= 2;
        d++;
    }

    int ret = 0;
    for (int i = 0; i <= N - x; i++) {
        for (int j = 0; j <= M - x; j++) {
            int minval = min4(minst[i][j][d],
                              minst[i+x-k][j][d],
                              minst[i][j+x-k][d],
                              minst[i+x-k][j+x-k][d]);
            int maxval = max4(maxst[i][j][d],
                              maxst[i+x-k][j][d],
                              maxst[i][j+x-k][d],
                              maxst[i+x-k][j+x-k][d]);
            ret = max(ret, maxval - minval);
        }
    }
    return ret >= K;
}


int main() {
    scanf("%d%d%d", &N, &M, &K);
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            scanf("%d", &A[i][j]);
            minst[i][j][0] = maxst[i][j][0] = A[i][j];
        }
    }
    if (K == 0) {
        printf("1\n");
        return 0;
    }

    for (int d = 1; d <= 9; d++) {
        int k = (1 << d);
        for (int i = 0; i <= N - k; i++) {
            for (int j = 0; j <= M - k; j++) {
                minst[i][j][d] = min4(minst[i][j][d-1],
                                      minst[i+k/2][j][d-1],
                                      minst[i][j+k/2][d-1],
                                      minst[i+k/2][j+k/2][d-1]);
                maxst[i][j][d] = max4(maxst[i][j][d-1],
                                      maxst[i+k/2][j][d-1],
                                      maxst[i][j+k/2][d-1],
                                      maxst[i+k/2][j+k/2][d-1]);
            }
        }
    }

    if (!feasible(min(N, M))) {
        printf("-1\n");
        return 0;
    }

    int lo = 1, hi = min(N, M);
    while (lo < hi - 1) {
        int mid = (lo + hi) / 2;
        if (feasible(mid)) hi = mid;
        else lo = mid;
    }

    printf("%d\n", hi);

    return 0;
}
