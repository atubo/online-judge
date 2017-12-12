// https://www.luogu.org/problemnew/show/P1800
// software_NOI导刊2010提高（06）

#include <bits/stdc++.h>
using namespace std;

const int MAXN = 110;
int N, M;
int D1[MAXN], D2[MAXN];
int dpPrev[MAXN], dpCurr[MAXN];

bool check(int T) {
    memset(dpPrev, -127, sizeof(int)*MAXN);
    dpPrev[0] = 0;
    for (int i = 0; i < N; i++) {
        memset(dpCurr, -127, sizeof(int)*MAXN);
        int d1 = D1[i], d2 = D2[i];
        for (int x = 0; x <= M; x++) {
            for (int p = 0; p <= min(T/d1, x); p++) {
                dpCurr[x] = max(dpCurr[x],
                                dpPrev[x-p] + (T - p*d1)/d2);
            }
        }
        swap(dpPrev, dpCurr);
    }
    return dpPrev[M] >= M;
}

int main() {
    scanf("%d%d", &N, &M);
    for (int i = 0; i < N; i++) {
        scanf("%d%d", &D1[i], &D2[i]);
    }
    int lo = 0, hi = 20000;
    while (lo < hi - 1) {
        int mid = (lo + hi) / 2;
        if (check(mid)) hi = mid;
        else lo = mid;
    }
    printf("%d\n", hi);
    return 0;
}
