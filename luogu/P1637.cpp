// https://www.luogu.org/problem/show?pid=1637
// 三元上升子序列

#include <bits/stdc++.h>
using namespace std;

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

using PII = pair<int64_t, int>;

const int MAXN = 30010;
int N;
int64_t A[MAXN], dp1[MAXN];
PII B[MAXN];

int main() {
    scanf("%d", &N);
    for (int i = 0; i < N; i++) {
        scanf("%lld", &A[i]);
        B[i] = make_pair(A[i], i);
    }
    sort(B, B+N);

    A[B[0].second] = 1;
    for (int i = 1; i < N; i++) {
        A[B[i].second] = A[B[i-1].second] + (B[i].first > B[i-1].first);
    }

    BIT ft1(32768);
    for (int i = 0; i < N; i++) {
        int x = A[i];
        dp1[i] = ft1.get(x-1);
        ft1.set(x, 1);
    }

    BIT ft2(32768);
    int64_t ret = 0;
    for (int i = 0; i < N; i++) {
        int x = A[i];
        ret += ft2.get(x-1);
        ft2.set(x, dp1[i]);
    }

    printf("%lld\n", ret);

    return 0;
}
