// https://www.luogu.org/problemnew/show/P3185
// [HNOI2007]分裂游戏

#include <bits/stdc++.h>
using namespace std;

const int MAXN = 30;
int T;
int N;
int P[MAXN], Q[MAXN];
int SG[MAXN], mark[MAXN*MAXN];

void build() {
    memset(mark, 0x7F, sizeof(mark));
    SG[N-1] = 0;
    for (int i = N-2; i >= 0; i--) {
        for (int j = i+1; j < N; j++) {
            for (int k = j; k < N; k++) {
                mark[SG[j]^SG[k]] = i;
            }
        }
        for (int j = 0; j <= N*N; j++) {
            if (mark[j] != i) {
                SG[i] = j;
                break;
            }
        }
    }
}

int main() {
    scanf("%d", &T);
    while (T--) {
        scanf("%d", &N);
        for (int i = 0; i < N; i++) {
            scanf("%d", &P[i]);
        }
        build();
        int g = 0;
        for (int i = 0; i < N; i++) {
            if (P[i] & 1) g ^= SG[i];
        }
        if (g == 0) {
            printf("-1 -1 -1\n0\n");
            continue;
        }

        int ans = 0;
        bool found = false;
        for (int i = 0; i < N-1; i++) {
            if (P[i] > 0) {
                for (int j = i+1; j < N; j++) {
                    for (int k = j; k < N; k++) {
                        if ((SG[j] ^ SG[k]) == (SG[i] ^ g)) {
                            if (!found) {
                                printf("%d %d %d\n", i, j, k);
                                found = true;
                            }
                            ans++;
                        }
                    }
                }
            }
        }
        printf("%d\n", ans);
    }

    return 0;
}
