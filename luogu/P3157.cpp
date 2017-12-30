// https://www.luogu.org/problemnew/show/P3157
// [CQOI2011]动态逆序对

#include <bits/stdc++.h>
using namespace std;

const int MAXN = 100000 * 90;

int val[MAXN], lc[MAXN], rc[MAXN];
int root[100010];

struct ChairmanInFenwick {
    struct Node {
        Node() : L(0), R(0), sum(0) {}
        // note L and R are children's index, not query range
        int L, R, sum;
    };

    int n;  // number of positions
    int tn; // number of weights
    int T_cnt;
    //vector<int> root;
    //vector<Node> T;

    ChairmanInFenwick(int n_, int tn_):
        n(n_), tn(tn_), T_cnt(1) {}

    int lowbit(int x) {return x & -x;}

    // add value t to weight node w at position x
    void add(int x, int w, int t) {
        for (int i = x; i <= n; i += lowbit(i)) {
            update(root[i], w, t, 1, tn);
        }
    }

    void update(int &now, int w, int t, int l, int r) {
        if (!now) now = T_cnt++;
        val[now] += t;
        if (l == r) return;
        int mid = (l + r) / 2;
        if (w <= mid) update(lc[now], w, t, l, mid);
        else          update(rc[now], w, t, mid+1, r);
    }

    // weight sum [l, r] for position [1, k]
    int query(int k, int l, int r) {
        if (l > r) return 0;
        int sum = 0;
        for (int j = k; j; j -= lowbit(j)) {
            sum += querySingleTree(root[j], 1, tn, l, r);
        }
        return sum;
    }

    int querySingleTree(int node, int L, int R, int l, int r) {
        if (L >= l && R <= r) return val[node];
        if (L > r || R < l) return 0;
        int sum = 0;
        int mid = (L + R) / 2;
        if (l <= mid) sum += querySingleTree(lc[node], L, mid, l, r);
        if (mid < r)  sum += querySingleTree(rc[node], mid+1, R, l, r);
        return sum;
    }
};

int N, M;
int POS[100010], A[100010];
bool D[100010];
int B[50010];
int64_t res[50010];

int main() {
    scanf("%d%d", &N, &M);
    ChairmanInFenwick cf(N, N);
    int64_t ans = 0;
    for (int i = 1; i <= N; i++) {
        scanf("%d", &A[i]);
        POS[A[i]] = i;
    }
    for (int i = 0; i < M; i++) {
        scanf("%d", &B[i]);
        D[B[i]] = true;
    }
    for (int i = 1; i <= N; i++) {
        int x = A[i];
        if (D[x]) continue;
        if (i > 1) ans += cf.query(i-1, x+1, N);
        cf.add(i, x, 1);
    }
    for (int i = M-1; i >= 0; i--) {
        int x = B[i];
        int pos = POS[x];
        if (pos > 1) ans += cf.query(pos-1, x+1, N);
        ans += cf.query(N, 1, x-1) - (pos > 1 ? cf.query(pos-1, 1, x-1) : 0);
        cf.add(pos, x, 1);
        res[i] = ans;
    }

    for (int i = 0; i < M; i++) {
        printf("%lld\n", res[i]);
    }

    return 0;
}
