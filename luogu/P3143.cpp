// https://www.luogu.org/problem/show?pid=3143
// [USACO16OPEN]钻石收藏家Diamond Collector

#include <bits/stdc++.h>
using namespace std;

const int MAXN = 50010;
int N, K;
int A[MAXN], B[MAXN], C[MAXN], D[MAXN], E[MAXN], F[MAXN];

class BIT {
public:
    // Note size needs to be power of 2
    BIT(int size): N(size) {
        tree = (int*)malloc((size+1) * sizeof(int));
        clear();
    }
    
    ~BIT() {
        free(tree);
        tree = NULL;
    }

    void clear() {
        memset(tree, 0, (N+1) * sizeof(int));
    }

    // add v to value at x
    void set(int x, int v) {
        while(x <= N) {
            tree[x] += v;
            x += (x & -x);
        }
    }

    // get cumulative sum up to and including x
    int get(int x) const {
        int res = 0;
        while(x) {
            res += tree[x];
            x -= (x & -x);
        }
        return res;
    }

    // get result for [x, y]
    int get(int x, int y) const {
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
    int* tree;
    const int N;
};

int main() {
    scanf("%d %d", &N, &K);
    for (int i = 1; i <= N; i++) {
        scanf("%d", &A[i]);
    }
    sort(A + 1, A + N + 1);

    B[1] = A[1];
    C[1] = 1;
    int M = 0;
    for (int p = 2, q = 1; p <= N; p++) {
        if (B[q] == A[p]) {
            C[q]++;
        } else {
            q++;
            B[q] = A[p];
            C[q] = 1;
        }
        M  = q;
    }

    BIT ft(65536);
    for (int i = 1; i <= M; i++) {
        ft.set(i, C[i]);
    }

    for (int i = M; i >= 1; i--) {
        int j = upper_bound(B+i, B+M+1, B[i] + K) - B;
        D[i] = ft.get(i, j-1);
        E[i] = max(E[i+1], D[i]);
        F[i] = j;
    }

    int ret = 0;
    for (int i = 1; i <= M; i++) {
        ret = max(ret, D[i] + E[F[i]]);
    }

    printf("%d\n", ret);

    return 0;
}
