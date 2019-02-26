// https://www.luogu.org/problemnew/show/P3745
// [六省联考2017]期末考试

#include <bits/stdc++.h>
using namespace std;

const int MAXN = 100010;
int64_t A, B, C;
int N, M;
int T[MAXN], R[MAXN];
int64_t ps1[MAXN], ps2[MAXN], ps_t[MAXN];
int rmax;

int64_t cost(int x) {
    int64_t m = lower_bound(T, T+N, x) - T;
    int64_t ret = 0;
    if (m > 0) {
        ret += 1LL * C * (m * x - ps_t[m-1]);
    }

    m = lower_bound(R, R+M, x) - R;
    int64_t l = 0, r = 0;
    if (m < M) {
        r = ps2[m] - (M - m) * x;
    }
    if (m > 0) {
        l = m * x - ps1[m-1];
    }

    if (A < B) {
        if (r >= l) ret += (r-l) * B + l * A;
        else ret += r * A;
    } else {
        ret += r * B;
    }

    return ret;
}

int main() {
    scanf("%ld%ld%ld", &A, &B, &C);
    scanf("%d%d", &N, &M);
    for (int i = 0; i < N; i++) {
        scanf("%d", &T[i]);
    }
    sort(T, T+N);
    ps_t[0] = T[0];
    for (int i = 1; i < N; i++) ps_t[i] = ps_t[i-1] + T[i];

    for (int i = 0; i < M; i++) {
        scanf("%d", &R[i]);
        rmax = max(rmax, R[i]);
    }
    sort(R, R+M);
    ps1[0] = R[0];
    for (int i = 1; i < M; i++) ps1[i] = ps1[i-1] + R[i];
    ps2[M-1] = R[M-1];
    for (int i = M-2; i >= 0; i--) ps2[i] = ps2[i+1] + R[i];

    if (C == 1e16) {
        printf("%ld", cost(T[0]));
        return 0;
    }
    int lo = 0, hi = rmax;
    while (lo < hi - 2) {
        int d = (hi - lo) / 3;
        int mid1 = lo + d;
        int mid2 = hi - d;
        int64_t cost1 = cost(mid1);
        int64_t cost2 = cost(mid2);
        if (cost1 <= cost2) hi = mid2;
        else lo = mid1;
    }
    int64_t ans = cost(lo);
    for (int i = lo+1; i <= hi; i++) {
        ans = min(ans, cost(i));
    }
    printf("%ld", ans);

    return 0;
}
