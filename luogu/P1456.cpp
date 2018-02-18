// https://www.luogu.org/problem/show?pid=1456
// Monkey King

#include <bits/stdc++.h>
using namespace std;


template <class Cmp = less<int>>
class LeftistTree {
public:

    LeftistTree(int size) {
        N = size;

        f = new int[N+1]{};
        t.resize(N+1);
        val = new int[N+1]{};
        d = new int[N+1]{-1};
    }

    ~LeftistTree() {
        delete[] f;
        delete[] val;
        delete[] d;
    }

    void clear(int m) {
        int sz = (m + 1) * sizeof(int);
        memset(f, 0, sz);
        memset(val, 0, sz);
        memset(d, -1, sz);
        for (int i = 0; i <= m; i++) {
            t[i][0] = t[i][1] = 0;
        }
    }

    // build single node
    void build(int x, int v) {
        f[x] = 0;
        t[x][0] = t[x][1] = 0;
        val[x] = v;
        d[x] = 0;
    }

    bool son(int x) const {
        return t[f[x]][0] == x ? 0 : 1;
    }

    // push to tree at root, return new root
    int push(int root, int x, int v) {
        build(x, v);
        if (!root) return x;
        else return merge(root, x);
    }

    int top(int root) const {
        assert(!f[root]);
        return val[root];
    }

    // must be a root, return new root
    int pop(int x) {
        assert(!f[x]);
        int lc = t[x][0], rc = t[x][1];
        if (lc) cut(lc);
        if (rc) cut(rc);
        if (rc) return merge(lc, rc);
        else return lc;
    }

    // merge two trees rooted at x and y, return new root
    int merge(int x, int y) {
        assert(x && y);
        if (cmp(val[y], val[x])) {
            swap(x, y);
        }

        if (t[x][1] == 0) {
            connect(x, y, 1);
        } else if (cmp(val[y], val[t[x][1]])) {
            int rc = t[x][1];
            cut(rc);
            connect(x, y, 1);
            merge(y, rc);
        } else {
            merge(t[x][1], y);
        }

        if (d[t[x][1]] > d[t[x][0]]) {
            swap(t[x][0], t[x][1]);
        }
        d[x] = d[t[x][1]] + 1;
        return x;
    }

    int find(int x) const {
        while (f[x] != 0) x = f[x];
        return x;
    }

    void print() {
        printf("f: ");
        for (int i = 0; i <= N; i++) {
            printf("%d ", f[i]);
        }
        printf("t: ");
        for (int i = 0; i <= N; i++) {
            printf("(%d %d) ", t[i][0], t[i][1]);
        }
        printf("val: ");
        for (int i = 0; i <= N; i++) {
            printf("%d ", val[i]);
        }
        printf("d: ");
        for (int i = 0; i <= N; i++) {
            printf("%d ", d[i]);
        }
        printf("\n");
    }

    int N;  // number of elements, 0 (NULL) excluded
    int *f;
    vector<array<int, 2>> t;
    int *val;
    int *d;
    Cmp cmp;

private:
    // cut x from its parent
    void cut(int x) {
        assert(x && f[x] && (t[f[x]][son(x)] == x));
        t[f[x]][son(x)] = 0;
        f[x] = 0;
    }

    // connect y as x's child, z = 0 -> left, 1 -> right
    void connect(int x, int y, int z) {
        assert(!f[y] && !t[x][z]);
        f[y] = x;
        t[x][z] = y;
    }
};

using Lt = LeftistTree<greater<int>>;

const int MAXN = 100010;
int N, M;
int A[MAXN];

int half(Lt &lt, int r) {
    if (lt.t[r][0] == 0) {
        lt.val[r] /= 2;
        return r;
    }
    int s = lt.pop(r);
    lt.val[r] /= 2;
    return lt.merge(s, r);
}

int main() {
    LeftistTree<greater<int>> lt(MAXN);
    while (scanf("%d", &N) == 1) {
        lt.clear(N);
        for (int i = 1; i <= N; i++) {
            int v;
            scanf("%d", &v);
            lt.build(i, v);
        }
        scanf("%d", &M);
        for (int i = 0; i < M; i++) {
            int a, b;
            scanf("%d%d", &a, &b);
            int ra = lt.find(a);
            int rb = lt.find(b);
            if (ra == rb) {
                printf("-1\n");
                continue;
            }
            int nra = half(lt, ra);
            int nrb = half(lt, rb);
            int r = lt.merge(nra, nrb);
            printf("%d\n", lt.top(r));
        }
    }
    return 0;
}
