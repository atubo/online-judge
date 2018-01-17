// https://www.luogu.org/problemnew/show/P1070
// 道路游戏

#include <bits/stdc++.h>
using namespace std;

const int MAXN = 1010;
int N, T, P;
int dp1[MAXN][MAXN], dp2[MAXN], M[MAXN][MAXN], S[MAXN][MAXN], C[MAXN];
struct Item {
    int t, v;
} items[MAXN][MAXN];
int front[MAXN], back[MAXN];

int id(int i, int t) {
    return ((i - t) % N + N) % N;
}

void print() {
    for (int i = 0; i < N; i++){
        for (int j = front[i]-1; j >= back[i]; j--) {
            printf("[%d %d] ", items[i][j].t, items[i][j].v);
        }
        printf("\n");
    }
}

int main() {
    scanf("%d%d%d", &N, &T, &P);
    for (int i = 0; i < N; i++) {
        for (int j = 1; j <= T; j++) {
            scanf("%d", &M[i][j]);
        }
    }
    for (int i = 0; i < N; i++) {
        scanf("%d", &C[i]);
    }

    for (int d = 0; d < N; d++) {
        for (int t = 1; t <= T; t++) {
            S[d][t] = M[(d+t)%N][t] + S[d][t-1];
        }
    }
    for (int i = 0; i < N; i++) {
        int d = id(i, T+1);
        items[d][front[d]++] = {T+1, S[d][T]};
    }

    for (int t = T; t >= 1; t--) {
        dp2[t] = INT_MIN;
        for (int i = 0; i < N; i++) {
            int d = id(i, t);
            int &b = back[d];
            while (items[d][b].t > t+P) b++;
            dp1[d][t] = items[d][b].v - S[d][t-1] - C[i];
            dp2[t] = max(dp2[t], dp1[d][t]);
        }
        for (int i = 0; i < N; i++) {
            int d = id(i, t);
            int &b = back[d];
            int &f = front[d];
            while (f > b && dp2[t] + S[d][t-1] >= items[d][f-1].v) f--;
            items[d][f++] = {t, dp2[t] + S[d][t-1]};
        }
    }
    printf("%d\n", dp2[1]);

    return 0;
}
