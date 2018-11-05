// https://www.luogu.org/problemnew/show/P1430
// 序列取数

#include <bits/stdc++.h>
using namespace std;

const int MAXN = 1010;
int T, N;
int64_t A[MAXN], B[MAXN];
int64_t minl[MAXN], minr[MAXN];

int64_t solve() {
    memset(minl, 0, (N+1)*sizeof(int64_t));
    memset(minr, 0, (N+1)*sizeof(int64_t));
    int64_t ans = 0;
    for (int k = 1; k <= N; k++) {
        for (int l = 1; l <= N-k+1; l++) {
            int r = l + k - 1;
            int64_t rt = 0;
            if (r > l) {
                rt = min(rt, minl[l]);
                rt = min(rt, minr[r]);
            }
            rt = B[r] - B[l-1] - rt;
            minl[l] = min(minl[l], rt);
            minr[r] = min(minr[r], rt);
            if (k == N) ans = rt;
        }
    }

    return ans;
}

int main() {
    scanf("%d", &T);

    while (T--) {
        scanf("%d", &N);
        for (int i = 1; i <= N; i++) {
            scanf("%ld", &A[i]);
            B[i] = A[i] + B[i-1];
        }
        int64_t ans = solve();
        printf("%ld\n", ans);
    }
    return 0;
}
