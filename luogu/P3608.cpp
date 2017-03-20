// https://www.luogu.org/problem/show?pid=3608
// [USACO17JAN]Balanced Photo平衡的照片

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

using PII = pair<int, int>;

const int MAXN = 100010;
int N;
PII A[MAXN];
int B[MAXN];

int main() {
    scanf("%d", &N);
    for (int i = 1; i <= N; i++) {
        A[i].second = i;
        scanf("%d", &A[i].first);
    }
    sort(A + 1, A + N + 1);

    for (int i = 1; i <= N; i++) {
        B[A[i].second] = i;
    }

    int ret = 0;
    BIT ft(131072);
    for (int i = 1; i <= N; i++) {
        int h = B[i];
        int k = ft.get(h-1);
        int left = (i-1) - k;
        int right = (N-i) - (h-1-k);
        if (max(left, right) > 2 * min(left, right)) {
            ret++;
        }
        ft.set(h, 1);
    }
    printf("%d\n", ret);
    return 0;
}
