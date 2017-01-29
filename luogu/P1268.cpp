// https://www.luogu.org/problem/show?pid=1268
// P1268 树的重量

#include <algorithm>
#include <cstdio>
#include <cstring>
using namespace std;

const int MAXN = 32;
int D[MAXN][MAXN];
int N, M;

bool areLeaves(int p, int q, int& diff) {
    bool initialized = false;
    for (int i = 0; i < M; i++) {
        if (i == p || i == q) continue;
        if (!initialized) {
            diff = D[i][p] - D[i][q];
            initialized = true;
        } else {
            if (D[i][p] - D[i][q] != diff) return false;
        }
    }
    return abs(diff - D[p][q]) % 2 == 0;
}

void swapRow(int p, int q) {
    for (int i = 0; i < M; i++) {
        swap(D[p][i], D[q][i]);
    }
}

void swapCol(int p, int q) {
    for (int i = 0; i < M; i++) {
        swap(D[i][p], D[i][q]);
    }
}

void discard(int p) {
    swapRow(p, M-1);
    swapCol(p, M-1);
}

int main() {
    while (true) {
        scanf("%d", &N);
        if (N == 0) break;
        for (int i = 0; i < N-1; i++) {
            for (int j = i+1; j < N; j++) {
                int x;
                scanf("%d", &x);
                D[i][j] = D[j][i] = x;
            }
        }

        int ans = 0;
        M = N;
NEXT:
        while (M > 2) {
            for (int i = 0; i < M-1; i++) {
                for (int j = i+1; j < M; j++) {
                    int diff;
                    if (areLeaves(i, j, diff)) {
                        int dj = (D[i][j] - diff) / 2;
                        ans += dj;
                        discard(j);
                        M--;
                        goto NEXT;
                    }
                }
            }
        }
        ans += D[0][1];
        printf("%d\n", ans);
    }

    return 0;
}

