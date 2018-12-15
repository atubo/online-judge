// https://www.luogu.org/problemnew/show/P2120
// [ZJOI2007]仓库建设

#include <bits/stdc++.h>
using namespace std;

namespace ConvextHullTrick {

    const int MAXN = 1e6+10;
    int64_t D[MAXN], P[MAXN], C[MAXN];
    int64_t Q[MAXN], R[MAXN];
    int64_t dp[MAXN];
    int64_t buf[MAXN];
    int N;

    int64_t Y(int i) {
        return dp[i] + R[i];
    }

    int64_t X(int i) {
        return Q[i];
    }

    int64_t numer(int k, int j) {
        return Y(j) - Y(k);
    }

    int64_t denom(int k, int j) {
        return X(j) - X(k);
    }

    bool isConvex(int a, int b, int c) {
        return numer(a, b) * denom(b, c) < numer(b, c) * denom(a, b);
    }

    int64_t getDp(int i, int j) {
        int64_t ret = dp[j] - Q[j]*D[i] + R[j] + Q[i]*D[i] - R[i] + C[i];
        return ret;
    }

    void runDp() {
        dp[0] = 0;
        int p = 0, q = 0;
        buf[q++] = 0;
        for (int i = 1; i <= N; i++) {
            while (q-p > 1 &&
                   numer(buf[p], buf[p+1]) <= denom(buf[p], buf[p+1]) * D[i]) {
                p++;
            }
            dp[i] = getDp(i, buf[p]);
            while (q-p > 1 && !isConvex(buf[q-2], buf[q-1], i)) {
                q--;
            }
            buf[q++] = i;
        }
    }
}

int main() {
    using ConvextHullTrick::N;
    using ConvextHullTrick::D;
    using ConvextHullTrick::P;
    using ConvextHullTrick::C;
    using ConvextHullTrick::Q;
    using ConvextHullTrick::R;

    scanf("%d", &N);
    for (int i = 1; i <= N; i++) {
        scanf("%ld%ld%ld", &D[i], &P[i], &C[i]);
    }
    for (int i = 1; i <= N; i++) {
        Q[i] = Q[i-1] + P[i];
        R[i] = R[i-1] + P[i]*D[i];
    }
    ConvextHullTrick::runDp();
    printf("%ld\n", ConvextHullTrick::dp[N]);
    return 0;
}
