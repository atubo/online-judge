// https://www.luogu.org/problem/show?pid=1101
// 单词方阵

#include <bits/stdc++.h>
using namespace std;

const int MAXN = 110;
char A[MAXN][MAXN], B[MAXN][MAXN];
int N;
int DX[8] = {1, 1, 0, -1, -1, -1, 0, 1};
int DY[8] = {0, 1, 1, 1, 0, -1 ,-1, -1};
char PATTERN[8] = "yizhong";

bool inRange(int p, int q) {
    return (0 <= p && p < N && 0 <= q && q < N);
}

void search(int i, int j, int d) {
    for (int k = 0; k < 7; k++) {
        int p = i + DX[d] * k;
        int q = j + DY[d] * k;
        if (!inRange(p, q) || A[p][q] != PATTERN[k]) return;
    }
    for (int k = 0; k < 7; k++) {
        int p = i + DX[d] * k;
        int q = j + DY[d] * k;
        B[p][q] = 1;
    }
}


int main() {
    scanf("%d", &N);
    char s[200];
    for (int i = 0; i < N; i++) {
        scanf("%s", s);
        for (int j = 0; j < N; j++) {
            A[i][j] = s[j];
        }
    }

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            for (int d = 0; d < 8; d++) {
                search(i, j, d);
            }
        }
    }

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            printf("%c", (B[i][j] ? A[i][j] : '*'));
        }
        printf("\n");
    }
    return 0;
}
