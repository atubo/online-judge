// https://www.luogu.org/problemnew/show/P2344
// 奶牛抗议

#include <bits/stdc++.h>
using namespace std;

const int MOD = 1000000009;

int64_t add(int64_t a, int64_t b) {
    return (a + b) % MOD;
}

class BIT {
public:
    // Note size needs to be power of 2
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
            tree[x] = add(tree[x], v);
            x += (x & -x);
        }
    }

    // get cumulative sum up to and including x
    int64_t get(int x) const {
        int64_t res = 0;
        while(x) {
            res = add(res, tree[x]);
            x -= (x & -x);
        }
        return res;
    }

    // get result for [x, y]
    int64_t get(int x, int y) const {
        return get(y) - (x > 1 ? get(x-1) : 0);
    }

    // get largest value with cumulative sum less than or equal to x;
    // for smallest, pass x-1 and add 1 to result
    int getind(int x) {
        int idx = 0, mask = N;
        while(mask && idx < N) {
            int t = idx + mask;
            if(x >= tree[t]) {
                idx = t;
                x -= tree[t];
            }
            mask >>= 1;
        }
        return idx;
    }

private:
    int64_t* tree;
    const int N;
};

const int MAXN = 131072;
int N;
int A[MAXN], sorted[MAXN], dp[MAXN];
int *endp;

int id(int i) {
    return lower_bound(sorted, endp, i) - sorted + 1;
}

int main() {
    scanf("%d", &N);
    for (int i = 1; i <= N; i++) {
        scanf("%d", &A[i]);
        A[i] += A[i-1];
    }
    memcpy(sorted, A, (N+1)*sizeof(int));
    sort(sorted, sorted+N+2);
    endp = unique(sorted, sorted+N+2);
    dp[0] = 1;
    BIT ft(MAXN);
    ft.set(id(0), 1);
    for (int i = 1; i <= N; i++) {
        int d = id(A[i]);
        dp[i] = ft.get(d);
        ft.set(d, dp[i]);
    }
    printf("%d\n", dp[N]);

    return 0;
}
