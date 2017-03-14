// https://www.luogu.org/problem/show?pid=2345
// 奶牛集会

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
int N;
PII cow[20010];

const int MAXL = 32768;

int main() {
    scanf("%d", &N);
    for (int i = 0; i < N; i++) {
        scanf("%d %d", &cow[i].first, &cow[i].second);
    }
    sort(cow, cow + N);

    BIT cnt(MAXL);
    BIT ps(MAXL);

    int64_t ret = 0;
    for (int i = 0; i < N; i++) {
        int v = cow[i].first;
        int x = cow[i].second;
        int64_t sumLeft = (x == 1 ? 0 : ps.get(x-1));
        int64_t cntLeft = (x == 1 ? 0 : cnt.get(x-1));
        int64_t sumRight = ps.get(MAXL) - ps.get(x);
        int64_t cntRight = cnt.get(MAXL) - cnt.get(x);
        cnt.set(x, 1);
        ps.set(x, x);
        ret += v * (cntLeft * x - sumLeft + sumRight - cntRight * x);
    }

    printf("%lld\n", ret);

    return 0;
}
