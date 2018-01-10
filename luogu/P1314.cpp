// https://www.luogu.org/problemnew/show/P1314
// 聪明的质监员

#include <bits/stdc++.h>
using namespace std;

const int MAXN = 200010;

int N, M;
int64_t S;
int64_t psum[MAXN], vsum[MAXN];
int W[MAXN], V[MAXN], L[MAXN], R[MAXN];

int64_t eval(int w) {
    int64_t ans = 0;
    for (int i = 1; i <= N; i++) {
        psum[i] = psum[i-1];
        vsum[i] = vsum[i-1];
        if (W[i] >= w) {
            psum[i] += 1;
            vsum[i] += V[i];
        }
    }
    for (int i = 0; i < M; i++) {
        int l = L[i], r = R[i];
        int cnt = psum[r] - psum[l-1];
        int64_t sum = vsum[r] - vsum[l-1];
        ans += cnt * sum;
    }
    return ans;
}

int main() {
    scanf("%d%d%lld", &N, &M, &S);
    for (int i = 1; i <= N; i++) {
        scanf("%d%d", &W[i], &V[i]);
    }

    for (int i = 0; i < M; i++) {
        scanf("%d%d", &L[i], &R[i]);
    }

    int64_t diff = S - eval(0);
    if (diff >= 0) {
        printf("%lld\n", diff);
        return 0;
    }

    int lo = 0, hi = *max_element(W+1, W+N+1) + 1;
    while (lo < hi - 1) {
        int mid = (lo + hi) / 2;
        diff = S - eval(mid);
        if (diff < 0) lo = mid;
        else          hi = mid;
    }

    printf("%lld\n", min(eval(lo)-S, S-eval(hi)));
    return 0;
}
