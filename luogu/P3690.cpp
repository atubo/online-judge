// https://www.luogu.org/problem/P3690
// 【模板】Link Cut Tree （动态树）

#include <bits/stdc++.h>
using namespace std;

class LinkCutTree {
    // tree nodes are 1-indexed

public:
    LinkCutTree(int N): N_(N) {
        alloc();
    }

    ~LinkCutTree() {
        dealloc();
    }

    void access(int x) {
        for (int t = 0; x; t=x, x=fa_[x]) {
            splay(x);
            c_[x][1] = t;
            pushUp(x);
        }
    }

    void makeRoot(int x) {
        access(x);
        splay(x);
        rev_[x] ^= 1;
    }

    void link(int x, int y) {
        makeRoot(x);
        makeRoot(y);
        fa_[x] = y;
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
        c_[y][0] = fa_[x] = 0;
        pushUp(y);
    }

    bool isConnected(int x, int y) {
        split(x, y);
        return c_[y][0] == x;
    }

    int find(int x) {
        access(x);
        splay(x);
        int y = x;
        while (c_[y][0]) y = c_[y][0];
        return y;
    }

    int query(int x, int y) {
        makeRoot(x);
        access(y);
        splay(y);
        return tot_[y];
    }

    void update(int u, int d) {
        makeRoot(u);
        tot_[u] ^= d;
        val[u] ^= d;
    }

public:
    int *val, *tot_;
private:
    const int N_;
    int *fa_;
    int **c_;
    int *q_;
    bool *rev_;

    void alloc() {
        fa_ = new int[N_+1]{};
        val = new int[N_+1]{};
        tot_ = new int[N_+1]{};
        c_ = new int*[N_+1]{};
        for (int i = 0; i <= N_; i++) {
            c_[i] = new int[2]{};
        }
        q_ = new int[N_+1]{};
        rev_ = new bool[N_+1]{};
    }

    void dealloc() {
        delete[] fa_;
        delete[] val;
        delete[] tot_;
        for (int i = 0; i <= N_; i++) {
            delete[] c_[i];
        }
        delete[] c_;
        delete[] q_;
        delete[] rev_;
    }

#define isSplayRoot(x) (c_[fa_[x]][1] != x && c_[fa_[x]][0] != x)

    void pushDown(int x) {
        int l = c_[x][0], r = c_[x][1];
        if (rev_[x]) {
            rev_[x] ^= 1; rev_[l] ^= 1; rev_[r] ^= 1;
            swap(c_[x][1], c_[x][0]);
        }
    }

    void pushUp(int x) {
        int l = c_[x][0], r = c_[x][1];
        tot_[x] = val[x] ^ tot_[l] ^ tot_[r];
    }

    void rotate(int x) {
        int y = fa_[x], z = fa_[y], l, r;
        l = (c_[y][1] == x); r = l^1;
        if (!isSplayRoot(y)) c_[z][c_[z][1]==y] = x;
        fa_[c_[x][r]] = y; fa_[y] = x; fa_[x] = z;
        c_[y][l] = c_[x][r]; c_[x][r] = y;
        pushUp(y); pushUp(x);
    }

    void splay(int x) {
        int top = 0;
        q_[++top] = x;
        for (int i = x; !isSplayRoot(i); i = fa_[i]) {
            q_[++top] = fa_[i];
        }
        while (top) pushDown(q_[top--]);
        while (!isSplayRoot(x)) {
            int y = fa_[x], z = fa_[y];
            if (!isSplayRoot(y)) {
                if ((c_[y][0] == x) ^ (c_[z][0] == y)) rotate(x);
                else rotate(y);
            }
            rotate(x);
        }
    }
};

int N, M;

int main() {
    scanf("%d%d", &N, &M);
    LinkCutTree lct(N);
    for (int i = 1; i <= N; i++) {
        int x;
        scanf("%d", &x);
        lct.val[i] = x;
    }

    for (int i = 0; i < M; i++) {
        int t, x, y;
        scanf("%d%d%d", &t, &x, &y);
        if (t == 0) {
            printf("%d\n", lct.query(x, y));
        } else if (t == 1) {
            if (lct.find(x) != lct.find(y)) lct.link(x, y);
        } else if (t == 2) {
            if (lct.isConnected(x, y)) lct.cut(x, y);
        } else {
            lct.update(x, y^lct.val[x]);
        }
    }

    return 0;
}
