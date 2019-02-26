// https://www.luogu.org/problemnew/show/P1485
// 火枪打怪

#include <bits/stdc++.h>
using namespace std;

const int MAXN = 500010;
int N, K;
int64_t M[MAXN];
int64_t A0[MAXN], A1[MAXN], A2[MAXN];
int64_t ps0[MAXN], ps1[MAXN], ps2[MAXN];

void reset() {
    memset(A0, 0, sizeof(A0));
    memset(A1, 0, sizeof(A1));
    memset(A2, 0, sizeof(A2));
    memset(ps0, 0, sizeof(ps0));
    memset(ps1, 0, sizeof(ps1));
    memset(ps2, 0, sizeof(ps2));
}

bool check(int64_t mid) {
    reset();
    int64_t cnt = 0;
    int64_t a = M[0] / mid + 1;
    cnt += a;
    int radius = int64_t(sqrt(mid) + 1e-9);
    int64_t d = min(N-1, radius);
    A2[1] += a;
    A2[d+1] -= a;
    for (int i = 1; i < N; i++) {
        ps2[i] = ps2[i-1] + A2[i];
        ps1[i] = ps1[i-1] + A1[i];
        ps0[i] = ps0[i-1] + A0[i];
        int64_t r = M[i] - (ps2[i]*mid - (ps2[i]*i*i + ps1[i]*i + ps0[i]));
        if (r >= 0) {
            a = r / mid + 1;
            cnt += a;
            d = min(N-1-i, radius);
            A2[i+1] += a;
            A2[i+d+1] -= a;
            A1[i+1] += -2LL*a*i;
            A1[i+d+1] -= -2LL*a*i;
            A0[i+1] += a*i*i;
            A0[i+d+1] -= a*i*i;
        }
    }
    return cnt <= K;
}

int main() {
    scanf("%d%d", &N, &K);
    int64_t mx = 0;
    for (int i = 0; i < N; i++) {
        scanf("%ld", &M[N-1-i]);
        mx = max(mx, M[N-1-i]);
    }
    int64_t lo = 0, hi = mx + 1LL*N*N;
    while (lo < hi - 1) {
        int64_t mid = (lo + hi) / 2;
        if (check(mid)) hi = mid;
        else lo = mid;
    }
    printf("%ld", hi);
    return 0;
}
