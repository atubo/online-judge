// https://www.luogu.org/problemnew/show/P2474
// [SCOI2008]天平

#include <bits/stdc++.h>
using namespace std;


const int MAXN = 52;
int N, A, B;
char R[MAXN][MAXN];
int D1[MAXN][MAXN], D2[MAXN][MAXN];


int main() {
    scanf("%d%d%d", &N, &A, &B);
    A--; B--;
    for (int i = 0; i < N; i++) {
        scanf("%s", R[i]);
    }
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            if (R[i][j] == '=' || i == j) {
                D1[i][j] = D2[i][j] = 0;
            } else if (R[i][j] == '+') {
                D1[i][j] = 2;
                D2[i][j] = 1;
            } else if (R[i][j] == '-') {
                D1[i][j] = -1;
                D2[i][j] = -2;
            } else {
                D1[i][j] = 2;
                D2[i][j] = -2;
            }
        }
    }
    for (int k = 0; k < N; k++) {
        for (int i = 0; i < N; i++) {
            if (i == k) continue;
            for (int j = 0; j < N; j++) {
                if (j == i) continue;
                D1[i][j] = min(D1[i][j], D1[i][k] + D1[k][j]);
                D2[i][j] = max(D2[i][j], D2[i][k] + D2[k][j]);
            }
        }
    }

    int ans1 = 0, ans2 = 0, ans3 = 0;
    for (int i = 0; i < N; i++) {
        if (i == A || i == B) continue;
        for (int j = i+1; j < N; j++) {
            if (j == A || j == B) continue;
            if (D2[A][i] > D1[j][B] || D2[A][j] > D1[i][B]) ans1++;
            if (D1[A][i] < D2[j][B] || D1[A][j] < D2[i][B]) ans3++;
            if ((D1[A][i] == D2[A][i] && D1[j][B] == D2[j][B] &&
                D1[A][i] == D1[j][B]) ||
                (D1[A][j] == D2[A][j] && D1[i][B] == D2[i][B] &&
                 D1[A][j] == D1[i][B])) ans2++;
        }
    }
    printf("%d %d %d", ans1, ans2, ans3);

    return 0;
}
