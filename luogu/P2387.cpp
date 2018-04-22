// https://www.luogu.org/problemnew/show/P2387
// [NOI2014]魔法森林

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

    int query(int x, int y) {
        makeRoot(x);
        access(y);
        splay(y);
        return mx[y];
    }


public:
    int *val;
private:
    int N;
    int *fa, *mx;
    int **c;
    int *q;
    bool *rev;

    void alloc() {
        fa = new int[N+1]{};
        val = new int[N+1]{};
        mx = new int[N+1]{};
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
        mx[x] = x;
        if (val[mx[l]] > val[mx[x]]) mx[x] = mx[l];
        if (val[mx[r]] > val[mx[x]]) mx[x] = mx[r];
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

struct Edge {
    int id;
    int x, y, a, b;
    bool operator < (const Edge &other) {
        if (a < other.a) return true;
        if (a > other.a) return false;
        return id < other.id;
    }
} E[200010];

int N, M;

int main() {
    scanf("%d%d", &N, &M);
    LinkCutTree lct(N+M);
    for (int i = 1; i <= N+M; i++) {
        lct.makeRoot(i);
    }

    for (int i = 1; i <= M; i++) {
        int x, y, a, b;
        scanf("%d%d%d%d", &x, &y, &a, &b);
        E[i] = {i, x, y, a, b};
    }
    sort(E+1, E+M+1);
    for (int i = 1; i <= M; i++) {
        lct.val[N+i] = E[i].b;
    }

    int ans = INT_MAX;
    for (int i = 1; i <= M; i++) {
        const Edge &e = E[i];
        if (e.x == e.y) continue;
        if (lct.find(e.x) == lct.find(e.y)) {
            int t = lct.query(e.x, e.y);
            if (lct.val[t] > e.b) {
                lct.cut(E[t-N].x, t);
                lct.cut(E[t-N].y, t);
                lct.link(e.x, N+i);
                lct.link(e.y, N+i);
            }
        } else {
            lct.link(e.x, N+i);
            lct.link(e.y, N+i);
        }
        if (lct.find(1) == lct.find(N)) {
            ans = min(ans, e.a + lct.val[lct.query(1, N)]);
        }
    }
    if (ans == INT_MAX) {
        printf("-1\n");
    } else {
        printf("%d\n", ans);
    }

    return 0;
}
