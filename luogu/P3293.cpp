// https://www.luogu.org/problemnew/show/P3293
// [SCOI2016]美味

#include <bits/stdc++.h>
using namespace std;

class PersistentSegmentTree {
public:
    struct Node {
        // L and R are indices of its children
        // real left and right boundaries are not kept in the node
        // to save memory
        int L, R;
        int sum;

        Node(): L(0), R(0), sum(0) {}
    };

    int N; // number of positions, index is 1-based
    int M; // number of weights, index is 0-based
    int *root;
    Node *T;
    int T_cnt = 1;

    PersistentSegmentTree(int N_, int M_): N(N_), M(M_) {
        root = new int[N+1]{};
        T = new Node[(N+1) * int(log2(M)+2)]{};
    }

    ~PersistentSegmentTree() {
        delete[] root;
        delete[] T;
    }

    // for user's convenience
    void insert(int currRootIndex, int prevRootIndex, int x, int t) {
        root[currRootIndex] = root[prevRootIndex];
        insert(root[currRootIndex], x, t, 0, M-1);
    }

    // query in range [start, end]
    int query(int rootIndex, int start, int end) const {
        if (end < start) return 0;
        return query(root[rootIndex], start, end, 0, M-1);
    }

private:
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

    int query(int node, int start, int end, int l, int r) const {
        if (l > r) return 0;
        if (start <= l && r <= end) return T[node].sum;
        int mid = (l + r) / 2;
        int ret = 0;
        if (start <= mid) ret += query(T[node].L, start, end, l, mid);
        if (mid+1 <= end) ret += query(T[node].R, start, end, mid+1, r);
        return ret;
    }
};

int solve(const PersistentSegmentTree &pst,
          int b, int x, int l, int r) {
    int prefix = 0;
    int ans = 0;
    for (int d = 17; d >= 0; d--) {
        if ((b>>d) & 1) {
            int hi = (prefix << (d+1)) + (1<<d) - 1;
            int lo = (prefix << (d+1));
            int cnt = pst.query(r, max(0, lo-x), hi-x) -
                pst.query(l-1, max(0, lo-x), hi-x);
            if (cnt > 0) prefix = (prefix<<1);
            else prefix = (prefix<<1) | 1;
            ans = (ans << 1) | (cnt > 0);
        } else {
            int hi = (prefix << (d+1)) + (1<<(d+1)) - 1;
            int lo = (prefix << (d+1)) + (1<<d);
            int cnt = pst.query(r, max(0, lo-x), hi-x) -
                pst.query(l-1, max(0, lo-x), hi-x);
            if (cnt > 0) prefix = (prefix<<1) | 1;
            else prefix = (prefix<<1);
            ans = (ans << 1) | (cnt > 0);
        }
    }
    return ans;
}


const int MAXN = 200010;
int N, M;

int main() {
    scanf("%d%d", &N, &M);
    PersistentSegmentTree pst(N, 1<<18);
    for (int i = 1; i <= N; i++) {
        int a;
        scanf("%d", &a);
        pst.insert(i, i-1, a, 1);
    }
    for (int i = 0; i < M; i++) {
        int b, x, l, r;
        scanf("%d%d%d%d", &b, &x, &l, &r);
        int ans = solve(pst, b, x, l, r);
        printf("%d\n", ans);
    }
    return 0;
}
