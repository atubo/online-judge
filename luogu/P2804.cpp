// https://www.luogu.org/problem/show?pid=2804
// 神秘数字

#include <bits/stdc++.h>
using namespace std;
using PII = pair<int, int>;

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

const int MAXN = 200010;
int N, M;
int S[MAXN], T[MAXN], A[MAXN];
PII P[MAXN];

int add(int a, int b) {
    return (a + b) % 92084931;
}

int main() {
    scanf("%d %d", &N, &M);
    for (int i = 1; i <= N; i++) {
        scanf("%d", &S[i]);
        S[i] += S[i-1];
        T[i] = S[i] - M * i;
        P[i] = make_pair(T[i], i);
    }
    sort(P, P + N + 1);

    int order = 1;
    A[P[0].second] = order;
    int p = 0, q = 1;
    while (true) {
        while (q <= N && P[q].first == P[p].first) {
            A[P[q].second] = order;
            q++;
        }
        if (q > N) break;
        order++;
        A[P[q].second] = order;
        p = q;
        q++;
    }

    BIT bit(262144);
    int ret = 0;
    for (int i = 0; i <= N; i++) {
        int x = A[i];
        ret = add(ret, bit.get(x-1));
        bit.set(x, 1);
    }

    printf("%d\n", ret);
        
    return 0;
}
