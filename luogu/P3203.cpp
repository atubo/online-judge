// https://www.luogu.org/problemnew/show/P3203
// [HNOI2010]弹飞绵羊

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
        fa[x] = y;
        splay(x);
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

    int query(int x) {
        makeRoot(N);
        access(x);
        splay(x);
        return sz[x] - 1;
    }


public:
    int *val;
private:
    int N;
    int *fa, *sz;
    int **c;
    int *q;
    bool *rev;

    void alloc() {
        fa = new int[N+1]{};
        val = new int[N+1]{};
        sz = new int[N+1]{};
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
        delete[] sz;
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
    }

    void pushUp(int x) {
        int l = c[x][0], r = c[x][1];
        sz[x] = 1 + sz[l] + sz[r];
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
};

const int MAXN = 200010;
int N, M;
int A[MAXN];

void disconnect(LinkCutTree &lct, int x) {
    if (x + A[x] <= N) {
        lct.cut(x, x + A[x]);
    } else {
        lct.cut(x, N+1);
    }
}

void connect(LinkCutTree &lct, int x, int k) {
    A[x] = k;
    if (x + k <= N) {
        lct.link(x, x + k);
    } else {
        lct.link(x, N + 1);
    }
}

int main() {
    scanf("%d", &N);
    LinkCutTree lct(N+1);
    for (int i = 1; i <= N+1; i++) {
        lct.makeRoot(i);
    }
    for (int i = 1; i <= N; i++) {
        int k;
        scanf("%d", &k);
        connect(lct, i, k);
    }
    scanf("%d", &M);
    for (int i = 0; i < M; i++) {
        int t, x, k;
        scanf("%d%d", &t, &x);
        x++;
        if (t == 1) {
            printf("%d\n", lct.query(x));
        } else {
            scanf("%d", &k);
            disconnect(lct, x);
            connect(lct, x, k);
        }
    }

    return 0;
}
