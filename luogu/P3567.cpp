// https://www.luogu.org/problemnew/show/P3567
// [POI2014]KUR-Couriers

#include <bits/stdc++.h>
using namespace std;

const int MAXN = 500010;

struct ChairmanTree {
    struct Node {
        // L and R are indices of its children
        // real left and right boundaries are not kept in the node
        // to save memory
        int L, R;
        int sum;

        Node(): L(0), R(0), sum(0) {}
    };

    int N; // number of positions, index is 1-based
    int M; // number of weights, index is 1-based
    int T_cnt;

    // use static to avoid dynamic memory management
    static int root[MAXN];
    static Node T[MAXN*21];

    ChairmanTree(int N_, int M_): N(N_), M(M_), T_cnt(1) {}

    // insert a new weight node x with value t
    // current range is [l, r]
    void insert(int &now, int x, int t, int l, int r) {
        T[T_cnt++] = T[now];
        now = T_cnt-1;
        T[now].sum += t;
        if (l == r) return;
        int mid = (l + r) / 2;
        if (x <= mid) insert(T[now].L, x, t, l, mid);
        else          insert(T[now].R, x, t, mid+1, r);
    }

    // for user's convenience
    void insert(int &now, int x, int t) {
        insert(now, x, t, 1, M);
    }
};

using Node = ChairmanTree::Node;
int ChairmanTree::root[MAXN];
Node ChairmanTree::T[MAXN*21];

int N, M;

int main() {
    scanf("%d%d", &N, &M);
    ChairmanTree ct(N, N);
    for (int i = 1; i <= N; i++) {
        int x;
        scanf("%d", &x);
        ct.root[i] = ct.root[i-1];
        ct.insert(ct.root[i], x, 1);
    }
    for (int i = 0; i < M; i++) {
        int a, b;
        scanf("%d%d", &a, &b);
        int half = (b - a + 1) / 2 + 1;
        int pa = ct.root[a-1], pb = ct.root[b];
        int l = 1, r = N;
        while (true) {
            if (ct.T[pb].sum - ct.T[pa].sum < half) {
                printf("0\n");
                break;
            }
            if (l == r) {
                printf("%d\n", l);
                break;
            }
            int mid = (l + r) / 2;
            int lca = ct.T[pa].L, rca = ct.T[pa].R;
            int lcb = ct.T[pb].L, rcb = ct.T[pb].R;
            int lcnt = ct.T[lcb].sum - ct.T[lca].sum;
            int rcnt = ct.T[rcb].sum - ct.T[rca].sum;
            if (lcnt >= rcnt) {
                pb = lcb;
                pa = lca;
                r = mid;
            } else {
                pb = rcb;
                pa = rca;
                l = mid+1;
            }
        }
    }
    return 0;
}
