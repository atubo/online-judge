// https://www.luogu.org/problemnew/show/P3950
// 部落冲突

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
    }

    int find(int x) {
        access(x);
        splay(x);
        int y = x;
        while (c_[y][0]) y = c_[y][0];
        return y;
    }

private:
    const int N_;
    int *fa_;
    int **c_;
    int *q_;
    bool *rev_;

    void alloc() {
        fa_ = new int[N_+1]{};
        c_ = new int*[N_+1]{};
        for (int i = 0; i <= N_; i++) {
            c_[i] = new int[2]{};
        }
        q_ = new int[N_+1]{};
        rev_ = new bool[N_+1]{};
    }

    void dealloc() {
        delete[] fa_;
        for (int i = 0; i <= N_; i++) {
            delete[] c_[i];
        }
        delete[] c_;
        delete[] q_;
        delete[] rev_;
    }

#define ISROOT(x) (c_[fa_[x]][1] != x && c_[fa_[x]][0] != x)

    void pushDown(int x) {
        int l = c_[x][0], r = c_[x][1];
        if (rev_[x]) {
            rev_[x] ^= 1; rev_[l] ^= 1; rev_[r] ^= 1;
            swap(c_[x][1], c_[x][0]);
        }
    }

    void rotate(int x) {
        int y = fa_[x], z = fa_[y], l, r;
        l = (c_[y][1] == x); r = l^1;
        if (!ISROOT(y)) c_[z][c_[z][1]==y] = x;
        fa_[c_[x][r]] = y; fa_[y] = x; fa_[x] = z;
        c_[y][l] = c_[x][r]; c_[x][r] = y;
    }

    void splay(int x) {
        int top = 0;
        q_[++top] = x;
        for (int i = x; !ISROOT(i); i = fa_[i]) {
            q_[++top] = fa_[i];
        }
        while (top) pushDown(q_[top--]);
        while (!ISROOT(x)) {
            int y = fa_[x], z = fa_[y];
            if (!ISROOT(y)) {
                if ((c_[y][0] == x) ^ (c_[z][0] == y)) rotate(x);
                else rotate(y);
            }
            rotate(x);
        }
    }
};

const int MAXM = 300010;
int N, M;

struct War {
    int p, q;
} wars[MAXM];
int wid;

int main() {
    scanf("%d%d", &N, &M);
    LinkCutTree lct(N);
    for (int i = 0; i < N-1; i++) {
        int p, q;
        scanf("%d%d", &p, &q);
        lct.link(p, q);
    }
    char cmd[5];
    int p, q;
    for (int i = 0; i < M; i++) {
        scanf("%s", cmd);
        if (cmd[0] == 'Q') {
            scanf("%d%d", &p, &q);
            bool ok = (lct.find(p) == lct.find(q));
            printf(ok ? "Yes\n" : "No\n");
        } else if (cmd[0] == 'C') {
            scanf("%d%d", &p, &q);
            wars[++wid] = {p, q};
            lct.cut(p, q);
        } else {
            int x;
            scanf("%d", &x);
            lct.link(wars[x].p, wars[x].q);
        }
    }

    return 0;
}
