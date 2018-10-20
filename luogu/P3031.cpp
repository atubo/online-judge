// https://www.luogu.org/problemnew/show/P3031
// [USACO11NOV]高于中位数Above the Median

#include <bits/stdc++.h>
using namespace std;

class BIT {
public:
    // 1-indexed
    BIT(int size): N(size) {
        tree = (int64_t*)malloc((size+1) * sizeof(int64_t));
        clear();
    }

    ~BIT() {
        free(tree);
        tree = NULL;
    }

    void clear() {
        memset(tree, 0, (N+1) * sizeof(int64_t));
    }

    // add v to value at x
    void set(int x, int v) {
        while(x <= N) {
            tree[x] += v;
            x += (x & -x);
        }
    }

    // get cumulative sum up to and including x
    int64_t get(int x) const {
        int64_t res = 0;
        while(x) {
            res += tree[x];
            x -= (x & -x);
        }
        return res;
    }

    // get result for [x, y]
    int64_t get(int x, int y) const {
        return get(y) - (x > 1 ? get(x-1) : 0);
    }

    // index of first element with cumulative sum >= x
    int lowerBound(int64_t x) {
        int clz = __builtin_clz(N);
        int idx = 0, mask = 1 << (31 - clz);     // first power of 2 <= N
        while (mask) {
            int t = idx + mask;
            if (t <= N && x > tree[t]) {
                idx = t;
                x -= tree[t];
            }
            mask >>= 1;
        }
        return idx+1;
    }

    int upperBound(int64_t x) {
        int p = lowerBound(x);
        if (p <= N && get(p) == x) p = lowerBound(x+1);
        return p;
    }

private:
    int64_t* tree;
    const int N;
};

int N, X;

int main() {
    scanf("%d%d", &N, &X);
    int ps = 0;
    int64_t ret = 0;
    BIT ft(2*N);
    ft.set(N, 1);
    for (int i = 0; i < N; i++) {
        int h;
        scanf("%d", &h);
        ps += (h >= X ? 1: -1);
        ret += ft.get(ps+N);
        ft.set(ps+N, 1);
    }
    printf("%ld\n", ret);

    return 0;
}
