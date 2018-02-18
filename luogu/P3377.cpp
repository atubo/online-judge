// https://www.luogu.org/problemnew/show/P3377
// 【模板】左偏树（可并堆）

#include <bits/stdc++.h>
using namespace std;

const int MAXN = 100010;
int A[MAXN];

class LeftistTree {
public:

    LeftistTree(int size) {
        N = size;

        f = new int[N+1]{};
        t.resize(N+1);
        d = new int[N+1];
        memset(d, -1, (N+1) * sizeof(int));
    }

    ~LeftistTree() {
        delete[] f;
        delete[] d;
    }

    void clear(int m) {
        int sz = (m + 1) * sizeof(int);
        memset(f, 0, sz);
        memset(d, -1, sz);
        for (int i = 0; i <= m; i++) {
            t[i][0] = t[i][1] = 0;
        }
    }

    // build single node
    void build(int x) {
        f[x] = 0;
        t[x][0] = t[x][1] = 0;
        d[x] = 0;
    }

    bool son(int x) const {
        return t[f[x]][0] == x ? 0 : 1;
    }

    // push to tree at root, return new root
    int push(int root, int x) {
        build(x);
        if (!root) return x;
        else return merge(root, x);
    }

    int top(int root) const {
        assert(!f[root]);
        return A[root];
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
        if (cmp(y, x)) {
            swap(x, y);
        }

        if (t[x][1] == 0) {
            connect(x, y, 1);
        } else if (cmp(y, t[x][1])) {
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
        printf("d: ");
        for (int i = 0; i <= N; i++) {
            printf("%d ", d[i]);
        }
        printf("\n");
    }

    int N;  // number of elements, 0 (NULL) excluded
    int *f;
    vector<array<int, 2>> t;
    int *d;

private:
    bool cmp(int i, int j) {
        if (A[i] < A[j]) return true;
        if (A[i] > A[j]) return false;
        return i < j;
    }

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

int N, M;

int main() {
    scanf("%d%d", &N, &M);
    LeftistTree lt(N);
    for (int i = 1; i <= N; i++) {
        scanf("%d", &A[i]);
        lt.build(i);
    }
    for (int i = 0; i < M; i++) {
        int cmd, x, y;
        scanf("%d", &cmd);
        if (cmd == 1) {
            scanf("%d%d", &x, &y);
            if (A[x] == -1 || A[y] == -1) continue;
            int rx = lt.find(x);
            int ry = lt.find(y);
            if (rx != ry) lt.merge(rx, ry);
        } else {
            scanf("%d", &x);
            if (A[x] == -1) {
                printf("-1\n");
                continue;
            }
            int rx = lt.find(x);
            printf("%d\n", A[rx]);
            lt.pop(rx);
            A[rx] = -1;
        }
    }
    return 0;
}
