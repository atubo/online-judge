// https://www.luogu.org/problem/show?pid=2985
// [USACO10FEB]吃巧克力Chocolate Eating

#include <bits/stdc++.h>
using namespace std;

int N, D;
int64_t ps[50010];

bool feasible(int64_t x) {
    int p = 0;
    int64_t prev = 0;
    for (int i = 0; i < D; i++) {
        int64_t *q = lower_bound(ps + p, ps + N + 1, ps[p] + x - prev/2);
        if (q == ps + N + 1) return false;
        prev = prev/2 + *q - ps[p];
        p = q - ps;
    }
    return true;
}

void distribute(int64_t x) {
    int p = 0;
    int64_t prev = 0;
    for (int i = 1; i <= D; i++) {
        int64_t *q = lower_bound(ps + p, ps + N + 1, ps[p] + x - prev/2);
        for (int64_t* it = ps + p; it != q; it++) {
            printf("%d\n", i);
        }
        prev = prev/2 + *q - ps[p];
        p = q - ps;
    }
    for (int i = p + 1; i <= N; i++) {
        printf("%d\n", D);
    }
}

int main() {
    scanf("%d %d", &N, &D);
    for (int i = 1; i <= N; i++) {
        scanf("%lld", &ps[i]);
        ps[i] += ps[i-1];
    }

    int64_t lo = 0, hi = ps[N] + 1;
    while (lo < hi - 1) {
        int64_t mid = (lo + hi) / 2;
        if (feasible(mid)) lo = mid;
        else hi = mid;
    }
    printf("%lld\n", lo);
    distribute(lo);
    return 0;
}
