// https://www.luogu.org/problem/show?pid=2119
// 魔法阵

#include <bits/stdc++.h>
using namespace std;

const int MAXN = 15010, MAXM = 40010;
int N, M;
int A[MAXN], B[MAXN], C[MAXN], D[MAXN], bucket[MAXN], ps1[MAXN], ps2[MAXN];
int magic[MAXM];

int main() {
    scanf("%d%d", &N, &M);
    for (int i = 0; i < M; i++) {
        scanf("%d", &magic[i]);
        bucket[magic[i]]++;
    }

    for (int t = 1; t <= N/9; t++) {
        memset(ps1, 0, sizeof(ps1));
        memset(ps2, 0, sizeof(ps2));
        for (int x = 1; x + 2*t <= N; x++) {
            ps1[x] = ps1[x-1] + bucket[x] * bucket[x+2*t];
        }
        for (int x = N; x - t >= 1; x--) {
            ps2[x] = ps2[x+1] + bucket[x] * bucket[x-t];
        }
        for (int x = 1; x + 9*t + 1 <= N; x++) {
            A[x] += bucket[x+2*t] * ps2[x+9*t+1];
            B[x+2*t] += bucket[x] * ps2[x+9*t+1];
        }
        for (int x = N; x - 9*t - 1 >= 1; x--) {
            D[x] += bucket[x-t] * ps1[x-9*t-1];
            C[x-t] += bucket[x] * ps1[x-9*t-1];
        }
    }

    for (int i = 0; i < M; i++) {
        printf("%d %d %d %d\n",
               A[magic[i]], B[magic[i]], C[magic[i]], D[magic[i]]);
    }
    return 0;
}
