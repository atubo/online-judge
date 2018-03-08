// https://www.luogu.org/problemnew/show/P1326
// 足球

#include <bits/stdc++.h>
using namespace std;

int64_t N, S, T;

int64_t maxPts() {
    if (S - T >= N) return 3 * N;
    else if (S - T == N-1) return 3 * N - 2;
    else {
        if (T > 0) {
            return 3*min(N-1, S) + max((int64_t)0, N-1-S);
        } else {
            return 3*min(N, S) + max((int64_t)0, N-S);
        }
    }
}

int64_t minPts() {
    if (T - S >= N) return 0;
    if (S > T) return 3 + max((int64_t)0, N-1-T);
    return min(N-T+S, 3 + max((int64_t)0, N-1-T));
}

int main() {
    while (scanf("%lld%lld%lld", &S, &T, &N) == 3) {
        printf("%lld %lld\n", maxPts(), minPts());
    }
    return 0;
}
