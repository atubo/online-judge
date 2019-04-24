// https://www.luogu.org/problemnew/show/P4113
// [HEOI2012]采花

#include <bits/stdc++.h>
using namespace std;

class BIT {
public:
    // 1-indexed
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
        if (x == 0) return;
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

private:
    int* tree;
    const int N;
};

const int MAXN = 2e6+10;
int N, C, M;
int A[MAXN];
int nxt[MAXN], first[MAXN];
int ans[MAXN];

struct Query {
    int l, r, id;
    bool operator < (const Query &other) const {
        if (l != other.l) return l < other.l;
        return id < other.id;
    }
} Q[MAXN];

int main() {
    scanf("%d%d%d", &N, &C, &M);
    for (int i = 1; i <= N; i++) {
        scanf("%d", &A[i]);
        A[i]--;
    }
    for (int i = 0; i < C; i++) {
        first[i] = N+1;
    }
    for (int i = N; i >= 1; i--) {
        int c = A[i];
        nxt[i] = first[c];
        first[c] = i;
    }

    BIT ft(N+1);
    for (int i = 0; i < C; i++) {
        ft.set(nxt[first[i]], 1);
    }

    for (int i = 0; i < M; i++) {
        int l, r;
        scanf("%d%d", &l, &r);
        Q[i] = {l, r, i};
    }
    sort(Q, Q+M);

    for (int i = 0, j= 0; i <  M; i++) {
        for (; j < Q[i].l; j++) {
            ft.set(nxt[j], -1);
            ft.set(nxt[nxt[j]], 1);
        }
        ans[Q[i].id] = ft.get(Q[i].l, Q[i].r);
    }

    for (int i = 0; i < M; i++) {
        printf("%d\n", ans[i]);
    }

    return 0;
}
