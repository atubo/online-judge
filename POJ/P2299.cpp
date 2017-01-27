// http://poj.org/problem?id=2299
// Ultra-QuickSort

#include <inttypes.h>
#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <utility>
using namespace std;

typedef pair<int, int> PII;

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

    void clear(int n) {
        memset(tree, 0, (n+1) * sizeof(int64_t));
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

const int MAXN = 500010;
PII A[MAXN];
BIT fenwick(524288);

int main() {
    int N;
    while (true) {
        scanf("%d", &N);
        if (N == 0) break;
        for (int i = 0; i < N; i++) {
            scanf("%d", &A[i].first);
            A[i].second = i+1;
        }
        sort(A, A+N);
        fenwick.clear(N);
        int64_t ans = 0;
        for (int i = 0; i < N; i++) {
            ans += fenwick.get(A[i].second, N);
            fenwick.set(A[i].second, 1);
        }
        printf("%lld\n", ans);
    }

    return 0;
}
