// https://www.luogu.org/problem/show?pid=2184
// 贪婪大陆

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

int main() {
    int N, M;
    scanf("%d%d", &N, &M);
    BIT fenwickLeft(131072), fenwickRight(131072);
    for (int i = 0; i < M; i++) {
        int q, u, v;
        scanf("%d%d%d", &q, &u, &v);
        u += 2; v += 2;
        if (q == 1) {
            fenwickLeft.set(u, 1);
            fenwickRight.set(v, 1);
        } else {
            printf("%lld\n", fenwickLeft.get(v) - fenwickRight.get(u-1));
        }
    }
    return 0;
}
