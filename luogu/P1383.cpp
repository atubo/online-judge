// https://www.luogu.org/problemnew/show/P1383
// 高级打字机

#include <bits/stdc++.h>
using namespace std;

const int MAXN = 100010;

struct ChairmanTree {
    struct Node {
        // L and R are indices of its children
        // real left and right boundaries are not kept in the node
        // to save memory
        int L, R;
        int sz;
        char c;

        Node(): L(0), R(0), sz(0), c(0) {}
    };

    int N; // number of positions, index is 1-based
    int M; // number of weights, index is 0-based
    int T_cnt;

    // use static to avoid dynamic memory management
    static int root[MAXN];
    static Node T[MAXN*18];

    ChairmanTree(int N_, int M_): N(N_), M(M_), T_cnt(1) {}

    // insert a new weight node x with value t
    // current range is [l, r]
    void insert(int &now, int x, int t, char c, int l, int r) {
        T[T_cnt++] = T[now];
        now = T_cnt-1;
        T[now].sz += t;
        if (l == r) {
            T[now].c = c;
            return;
        }
        int mid = (l + r) / 2;
        if (x <= mid) insert(T[now].L, x, t, c, l, mid);
        else          insert(T[now].R, x, t, c, mid+1, r);
    }

    // for user's convenience
    // copy node from to the new node and set index now
    // insert char c to the last
    void insert(int &now, int from, char c) {
        now = from;
        insert(now, T[from].sz, 1, c, 0, M-1);
    }
};

using Node = ChairmanTree::Node;
int ChairmanTree::root[MAXN];
Node ChairmanTree::T[MAXN*18];

int N;

char query(int now, int k, int l, int r) {
    using CT = ChairmanTree;
    if (l == r) {
        return CT::T[now].c;
    }
    int mid = (l + r) / 2;
    int sz = CT::T[CT::T[now].L].sz;
    if (sz >= k+1) return query(CT::T[now].L, k, l, mid);
    else           return query(CT::T[now].R, k-sz, mid+1, r);
}

char query(int now, int k) {
    return query(now, k, 0, N-1);
}

int main() {
    scanf("%d", &N);
    ChairmanTree ct(N, N);
    char cmd[10], letter[10];
    int x;
    for (int i = 1, k = 1; i <= N; i++) {
        scanf("%s", cmd);
        if (cmd[0] == 'T') {
            scanf("%s", letter);
            ct.insert(ct.root[k], ct.root[k-1], letter[0]);
            k++;
        } else if (cmd[0] == 'U') {
            scanf("%d", &x);
            ct.root[k] = ct.root[k-x-1];
            k++;
        } else {
            scanf("%d", &x);
            printf("%c\n", query(ct.root[k-1], x-1));
        }
    }

    return 0;
}
