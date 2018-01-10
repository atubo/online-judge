// https://www.luogu.org/problemnew/show/P1314
// 聪明的质监员

#include <bits/stdc++.h>
using namespace std;

const int MAXN = 200010;

struct ChairmanTree {
    struct Node {
        // L and R are indices of its children
        // real left and right boundaries are not kept in the node
        // to save memory
        int L, R;
        int sz;
        int64_t sum;

        Node(): L(0), R(0), sum(0) {}
    };

    int N; // number of positions, index is 1-based
    int M; // number of weights, index is 1-based
    int T_cnt;

    // use static to avoid dynamic memory management
    static int root[MAXN];
    static Node T[MAXN*19];

    ChairmanTree(int N_, int M_): N(N_), M(M_), T_cnt(1) {}

    // insert a new weight node x with value t
    // current range is [l, r]
    void insert(int &now, int x, int t, int l, int r) {
        T[T_cnt++] = T[now];
        now = T_cnt-1;
        T[now].sz  += 1;
        T[now].sum += t;
        if (l == r) return;
        int mid = (l + r) / 2;
        if (x <= mid) insert(T[now].L, x, t, l, mid);
        else          insert(T[now].R, x, t, mid+1, r);
    }

    // for user's convenience
    void insert(int &now, int from, int x, int t) {
        now = from;
        insert(now, x, t, 1, M);
    }
};

struct Ore {
    int id, w, v;
    bool operator < (const Ore &other) const {
        if (w < other.w) return true;
        if (w > other.w) return false;
        return id < other.id;
    }
} ore[MAXN];

struct Range {
    int l, r;
} range[MAXN];

using Node = ChairmanTree::Node;
int ChairmanTree::root[MAXN];
Node ChairmanTree::T[MAXN*19];
int N, M;
int64_t S;
int setwt[MAXN];
int64_t vsum[MAXN];

pair<int, int64_t> query(const ChairmanTree &ct, int node, int l, int r,
                         int L, int R) {
    if (node == 0) return make_pair(0, 0LL);
    if (l <= L && R <= r) return make_pair(ct.T[node].sz, ct.T[node].sum);
    int mid = (L + R) / 2;
    int sz = 0;
    int64_t sum = 0;
    if (l <= mid) {
        auto p = query(ct, ct.T[node].L, l, r, L, mid);
        sz += p.first;
        sum += p.second;
    }
    if (mid+1 <= r) {
        auto p = query(ct, ct.T[node].R, l, r, mid+1, R);
        sz += p.first;
        sum += p.second;
    }
    return make_pair(sz, sum);
}

int64_t eval(const ChairmanTree &ct, int w) {
    int* pos = lower_bound(setwt+1, setwt+N+1, w);
    int x = pos - setwt - 1;
    int64_t ans = 0;
    for (int i = 0; i < M; i++) {
        int l = range[i].l, r = range[i].r;
        auto p = query(ct, ct.root[x], l, r, 1, N);
        //printf("sz=%d sum=%lld\n", p.first, p.second);
        ans += (r - l + 1 - p.first) * (vsum[r] - vsum[l-1] - p.second);
    }
    //printf("w=%d, ans=%lld\n", w, ans);
    return ans;
}

int main() {
    scanf("%d%d%lld", &N, &M, &S);
    int maxw = 0;
    for (int i = 1; i <= N; i++) {
        int w, v;
        scanf("%d%d", &w, &v);
        ore[i] = {i, w, v};
        setwt[i] = w;
        vsum[i] = v + vsum[i-1];
        maxw = max(maxw, w);
    }
    sort(setwt+1, setwt+N+1);
    sort(ore+1, ore+N+1);

    for (int i = 0; i < M; i++) {
        scanf("%d%d", &range[i].l, &range[i].r);
    }

    ChairmanTree ct(N, N);
    for (int i = 1; i <= N; i++) {
        //printf("%d %d %d\n", ore[i].id, ore[i].w, ore[i].v);
        ct.insert(ct.root[i], ct.root[i-1], ore[i].id, ore[i].v);
    }

    int64_t diff = S - eval(ct, 0);
    if (diff >= 0) {
        printf("%lld\n", diff);
        return 0;
    }

    int lo = 0, hi = maxw+1;
    while (lo < hi - 1) {
        int mid = (lo + hi) / 2;
        diff = S - eval(ct, mid);
        if (diff < 0) lo = mid;
        else          hi = mid;
    }

    printf("%lld\n", min(eval(ct, lo)-S, S-eval(ct, hi)));
    return 0;
}
