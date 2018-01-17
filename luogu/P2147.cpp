// https://www.luogu.org/problemnew/show/P2147
// [SDOI2008]Cave 洞穴勘测

#include <bits/stdc++.h>
using namespace std;

const int MAXN = 10010;
struct LinkCutTree {
    // use static memory allocation
    static int fa[MAXN], c[MAXN][2], q[MAXN];
    static bool rev[MAXN];

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

    void rotate(int x) {
        int y = fa[x], z = fa[y], l, r;
        l = (c[y][1] == x); r = l^1;
        if (!isSplayRoot(y)) c[z][c[z][1]==y] = x;
        fa[c[x][r]] = y; fa[y] = x; fa[x] = z;
        c[y][l] = c[x][r]; c[x][r] = y;
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

    void access(int x) {
        for (int t = 0; x; t=x, x=fa[x]) {
            splay(x);
            c[x][1] = t;
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
    }

    int find(int x) {
        access(x);
        splay(x);
        int y = x;
        while (c[y][0]) y = c[y][0];
        return y;
    }
};

int LinkCutTree::fa[MAXN];
int LinkCutTree::c[MAXN][2];
int LinkCutTree::q[MAXN];
bool LinkCutTree::rev[MAXN];

int N, M;
LinkCutTree lct;
int main() {
    scanf("%d%d", &N, &M);
    char cmd[10];
    int u, v;
    for (int i = 0; i < M; i++) {
        scanf("%s%d%d", cmd, &u, &v);
        if (cmd[0] == 'C') {
            lct.link(u, v);
        } else if (cmd[0] == 'D') {
            lct.cut(u, v);
        } else {
            int x = lct.find(u);
            int y = lct.find(v);
            if (x == y) printf("Yes\n");
            else printf("No\n");
        }
    }
    return 0;
}
