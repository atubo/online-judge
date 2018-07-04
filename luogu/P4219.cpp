// https://www.luogu.org/problemnew/show/P4219
// [BJOI2014]大融合

#include <bits/stdc++.h>
using namespace std;

class LinkCutTree {
    // tree nodes are 1-indexed

public:
    LinkCutTree(int N_): N(N_) {
        alloc();
    }

    ~LinkCutTree() {
        dealloc();
    }

    void access(int x) {
        for (int t = 0; x; t=x, x=fa[x]) {
            splay(x);
            sizeVirtualChildren[x] += size[c[x][1]] - size[t];
            c[x][1] = t;
            pushUp(x);
        }
    }

    void makeRoot(int x) {
        access(x);
        splay(x);
        rev[x] ^= 1;
    }

    void link(int x, int y) {
        makeRoot(x);
        makeRoot(y);
        fa[x] = y;
        sizeVirtualChildren[y] += size[x];
        splay(x);
        pushUp(y);
    }

    // split out the path from x to y
    void split(int x, int y) {
        makeRoot(x);
        access(y);
        splay(y);
    }

    void cut(int x, int y) {
        split(x, y);
        c[y][0] = fa[x] = 0;
        pushUp(y);
    }

    int find(int x) {
        access(x);
        splay(x);
        int y = x;
        while (c[y][0]) y = c[y][0];
        return y;
    }

    int query(int x, int y) {
        makeRoot(x);
        access(y);
        splay(y);
        return mx[y];
    }

    int queryTot(int x, int y) {
        makeRoot(x);
        access(y);
        splay(y);
        return tot[y];
    }

    void update(int u, int v, int d) {
        makeRoot(u);
        access(v);
        splay(v);
        updateAdd(v, d);
    }

    void print() {
        printf("father: ");
        for (int i = 1; i <= N; i++) {
            printf("%d ", fa[i]);
        }
        printf("\n");
        printf("child: ");
        for (int i = 1; i <= N; i++) {
            printf("(%d %d) ", c[i][0], c[i][1]);
        }
        printf("\n");
        printf("rev: ");
        for (int i = 1; i <= N; i++) {
            printf("%d ", int(rev[i]));
        }
        printf("\n");

        printf("val: ");
        for (int i = 1; i <= N; i++) {
            printf("%d ", val[i]);
        }
        printf("\n");
        printf("tot: ");
        for (int i = 1; i <= N; i++) {
            printf("%d ", tot[i]);
        }
        printf("\n");
        printf("d: ");
        for (int i = 1; i <= N; i++) {
            printf("%d ", delta[i]);
        }
        printf("\n");
    }

public:
    int *val;
    int *size;  // size of subtree in the original tree
private:
    int N;
    int *fa, *mx, *tot, *delta;
    int *sz;    // size of subtree in the splay tree
    int *sizeVirtualChildren;
    int **c;
    int *q;
    bool *rev;

    void alloc() {
        fa = new int[N+1]{};
        val = new int[N+1]{};
        mx = new int[N+1]{};
        tot = new int[N+1]{};
        delta = new int[N+1]{};
        sz = new int[N+1]{};
        size = new int[N+1]{};
        sizeVirtualChildren = new int[N+1]{};
        c = new int*[N+1]{};
        for (int i = 0; i <= N; i++) {
            c[i] = new int[2]{};
        }
        q = new int[N+1]{};
        rev = new bool[N+1]{};
    }

    void dealloc() {
        delete[] fa;
        delete[] val;
        delete[] mx;
        delete[] tot;
        delete[] delta;
        delete[] sz;
        delete[] size;
        delete[] sizeVirtualChildren;
        for (int i = 1; i <= N; i++) {
            delete[] c[i];
        }
        delete[] c;
        delete[] q;
        delete[] rev;
    }

    bool isSplayRoot(int x) {
        return c[fa[x]][1] != x && c[fa[x]][0] != x;
    }

    void pushDown(int x) {
        int l = c[x][0], r = c[x][1];
        if (rev[x]) {
            rev[x] ^= 1; rev[l] ^= 1; rev[r] ^= 1;
            swap(c[x][1], c[x][0]);
        }

        updateAdd(l, delta[x]);
        updateAdd(r, delta[x]);
        delta[x] = 0;
    }

    void pushUp(int x) {
        int l = c[x][0], r = c[x][1];
        mx[x] = val[x];
        mx[x] = max(mx[x], mx[l]);
        mx[x] = max(mx[x], mx[r]);
        sz[x] = 1 + sz[l] + sz[r];
        tot[x] = val[x] + tot[l] + tot[r];
        size[x] = size[l] + size[r] + sizeVirtualChildren[x] + 1;
    }

    void rotate(int x) {
        int y = fa[x], z = fa[y], l, r;
        l = (c[y][1] == x); r = l^1;
        if (!isSplayRoot(y)) c[z][c[z][1]==y] = x;
        fa[c[x][r]] = y; fa[y] = x; fa[x] = z;
        c[y][l] = c[x][r]; c[x][r] = y;
        pushUp(y); pushUp(x);
    }

    void splay(int x) {
        int top = 0;
        q[++top] = x;
        for (int i = x; !isSplayRoot(i); i = fa[i]) {
            q[++top] = fa[i];
        }
        while (top) pushDown(q[top--]);
        while (!isSplayRoot(x)) {
            int y = fa[x], z = fa[y];
            if (!isSplayRoot(y)) {
                if ((c[y][0] == x) ^ (c[z][0] == y)) rotate(x);
                else rotate(y);
            }
            rotate(x);
        }
    }

    void updateAdd(int x, int d) {
        if (!x) return;

        tot[x] += d * sz[x];
        val[x] += d;
        delta[x] += d;
    }
};

int N, Q;

int main() {
    scanf("%d%d", &N, &Q);
    LinkCutTree lct(N);
    char cmd[10];
    int x, y;
    for (int i = 0; i < Q; i++) {
        scanf("%s%d%d", cmd, &x, &y);
        if (cmd[0] == 'A') {
            lct.link(x, y);
        } else {
            lct.makeRoot(x);
            lct.makeRoot(y);
            int64_t st = lct.size[y];
            int64_t sx = lct.size[x];
            int64_t ans = (st-sx) * sx;
            printf("%lld\n", ans);
        }
    }

    return 0;
}
