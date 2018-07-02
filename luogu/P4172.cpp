// https://www.luogu.org/problemnew/show/P4172
// [WC2006]水管局长

#include <bits/stdc++.h>
using namespace std;


const int MAXM = 100010;
struct Pipe {
    int x, y, t;
} pipes[MAXM];

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

    void update(int u, int d) {
        makeRoot(u);
        access(u);
        val[u] = mx[u] = d;
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
        mx[x] = val[x];
        if (pipes[mx[l]].t > pipes[mx[x]].t) mx[x] = mx[l];
        if (pipes[mx[r]].t > pipes[mx[x]].t) mx[x] = mx[r];
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

const int MAXQ = 100010;
int N, M, Q;
int nodesToEdge[1002020];
bool isBad[MAXM];
struct Query {
    int k, a, b;
} queries[MAXQ];

int vnode(int x) {
    return N+x;
}

int hashNodes(int x, int y) {
    return x * (N+1) + y;
}

void link(LinkCutTree &lct, int x, int y, int t, int eidx) {
    int v = vnode(eidx);
    if (lct.find(x) != lct.find(y)) {
        lct.link(x, v);
        lct.link(v, y);
        lct.update(v, eidx);
    } else {
        // find largest edge
        // if it > t cut and link
        int e = lct.query(x, y);
        if (pipes[e].t > t) {
            int p = pipes[e].x;
            int q = pipes[e].y;
            lct.cut(p, e+N);
            lct.cut(q, e+N);
            lct.link(x, v);
            lct.link(v, y);
            lct.update(v, eidx);
        }
    }
}

int main() {
    scanf("%d%d%d", &N, &M, &Q);
    for (int i = 1; i <= M; i++) {
        int x, y, t;
        scanf("%d%d%d", &x, &y, &t);
        if (x > y) swap(x, y);
        pipes[i] = {x, y, t};
        int h = hashNodes(x, y);
        nodesToEdge[h] = i;
    }
    for (int i = 0; i < Q; i++) {
        int k, a, b;
        scanf("%d%d%d", &k, &a, &b);
        if (a > b) swap(a, b);
        if (k == 2) {
            int h = hashNodes(a, b);
            int e = nodesToEdge[h];
            isBad[e] = true;
        }
        queries[i] = {k, a, b};
    }

    LinkCutTree lct(N+M);

    for (int i = 1; i <= M; i++) {
        int x = pipes[i].x, y = pipes[i].y, t = pipes[i].t;
        if (!isBad[i]) {
            link(lct, x, y, t, i);
        }
    }

    vector<int> ans;
    for (int i = Q-1; i >= 0; i--) {
        int k = queries[i].k, a = queries[i].a, b = queries[i].b;
        if (k == 1) {
            int e = lct.query(a, b);
            ans.push_back(pipes[e].t);
        } else {
            int h = hashNodes(a, b);
            int eidx = nodesToEdge[h];
            int t = pipes[eidx].t;
            link(lct, a, b, t, eidx);
        }
    }

    reverse(ans.begin(), ans.end());
    for (int x: ans) {
        printf("%d\n", x);
    }

    return 0;
}
