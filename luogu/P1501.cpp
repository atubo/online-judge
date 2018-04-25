// https://www.luogu.org/problemnew/show/P1501
// [国家集训队]Tree II

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
        //print();
        return tot[y];
    }

    void updateTerm(int u, int v, int x) {
        makeRoot(u);
        access(v);
        splay(v);
        updateAdd(v, x);
    }

    void updateFactor(int u, int v, int x) {
        makeRoot(u);
        access(v);
        splay(v);
        updateMul(v, x);
        //fac[v] = mul(fac[v], x);
        //ter[v] = mul(ter[v], x);
    }

public:
    int *val;
    const static int MOD = 51061;
private:
    int N;
    int *fa, *tot, *fac, *ter, *sz;
    int **c;
    int *q;
    bool *rev;

    void alloc() {
        fa = new int[N+1]{};
        val = new int[N+1]{};
        tot = new int[N+1]{};
        fac = new int[N+1];
        for (int i = 0; i <= N; i++) fac[i] = 1;
        ter = new int[N+1]{};
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
        delete[] tot;
        delete[] fac;
        delete[] ter;
        delete[] sz;
        for (int i = 1; i <= N; i++) {
            delete[] c[i];
        }
        delete[] c;
        delete[] q;
        delete[] rev;
    }

    void updateAdd(int x, int d) {
        if (!x) return;

        tot[x] = add(tot[x], mul(d, sz[x]));
        val[x] = add(val[x], d);
        ter[x] = add(ter[x], d);
    }

    void updateMul(int x, int d) {
        if (!x) return;

        tot[x] = mul(tot[x], d);
        val[x] = mul(val[x], d);
        fac[x] = mul(fac[x], d);
        ter[x] = mul(ter[x], d);
    }

    int add(int64_t x, int64_t y) {
        return (x + y) % 51061;
    }

    int mul(int64_t x, int64_t y) {
        return (x * y) % 51061;
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

        updateMul(l, fac[x]);
        updateMul(r, fac[x]);
        updateAdd(l, ter[x]);
        updateAdd(r, ter[x]);
        fac[x] = 1;
        ter[x] = 0;
    }

    void pushUp(int x) {
        int l = c[x][0], r = c[x][1];
        sz[x] = 1 + sz[l] + sz[r];
        tot[x] = add(val[x], add(tot[l], tot[r]));
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

public:
#if 0
    void print() {
        printf("fac: ");
        for (int i = 1; i <= N; i++) {
            printf("%d ", fac[i]);
        }
        printf("\n");
        printf("ter: ");
        for (int i = 1; i <= N; i++) {
            printf("%d ", ter[i]);
        }
        printf("\n");
        printf("val: ");
        for (int i = 1; i <= N; i++) {
            printf("%d ", val[i]);
        }
        printf("\n");
        printf("isroot: ");
        for (int i = 1; i <= N; i++) {
            printf("%d ", isSplayRoot(i));
        }
        printf("\n");
        printf("father: ");
        for (int i = 1; i <= N; i++) {
            printf("%d ", fa[i]);
        }
        printf("\n");
    }
#endif
};

int N, Q;

int main() {
    scanf("%d%d", &N, &Q);
    LinkCutTree lct(N);

    for (int i = 1; i <= N; i++) {
        lct.val[i] = 1;
        lct.makeRoot(i);
    }
    for (int i = 0; i < N-1; i++) {
        int u, v;
        scanf("%d%d", &u, &v);
        lct.link(u, v);
    }
    for (int i = 0; i < Q; i++) {
        int u, v, c, u2, v2;
        char cmd[10];
        scanf("%s", cmd);
        switch (cmd[0]) {
            case '+':
                scanf("%d%d%d", &u, &v, &c);
                lct.updateTerm(u, v, c);
                break;
            case '-':
                scanf("%d%d%d%d", &u, &v, &u2, &v2);
                lct.cut(u, v);
                lct.link(u2, v2);
                break;
            case '*':
                scanf("%d%d%d", &u, &v, &c);
                lct.updateFactor(u, v, c);
                break;
            case '/':
                scanf("%d%d", &u, &v);
                printf("%d\n", lct.query(u, v));
                break;
        }
    }

    return 0;
}
