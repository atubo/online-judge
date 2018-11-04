// https://www.luogu.org/problemnew/show/P1393
// 动态逆序对

#include <bits/stdc++.h>
using namespace std;

struct SegmentInFenwick {
    int N;  // number of positions, index is 1-based
    int M;  // number of weights, index is 0-based
    int T_cnt;
    int *root;
    int16_t *val;
    int *lc, *rc;

    // cap is the number of elements to be added
    SegmentInFenwick(int N_, int M_, int cap): N(N_), M(M_), T_cnt(1) {
        root = new int[N+1]{};
        const int numOfNodes = cap * int(log2(N)+2) * int(log2(M)+2);
        val = new int16_t[numOfNodes]{};
        lc = new int[numOfNodes]{};
        rc = new int[numOfNodes]{};
    }

    ~SegmentInFenwick() {
        delete[] root;
        delete[] val;
        delete[] lc;
        delete[] rc;
    }

    // add value t to weight node w at position x
    void add(int x, int w, int t) {
        for (int i = x; i <= N; i += lowbit(i)) {
            update(root[i], w, t, 0, M-1);
        }
    }

    // weight sum [l, r] for position [1, k]
    int query(int k, int l, int r) const {
        if (l > r) return 0;
        int sum = 0;
        for (int j = k; j; j -= lowbit(j)) {
            sum += querySingleTree(root[j], 0, M-1, l, r);
        }
        return sum;
    }

private:
    int lowbit(int x) const {return x & -x;}

    void update(int &now, int w, int t, int l, int r) {
        if (!now) now = T_cnt++;
        val[now] += t;
        if (l == r) return;
        int mid = (l + r) / 2;
        if (w <= mid) update(lc[now], w, t, l, mid);
        else          update(rc[now], w, t, mid+1, r);
    }

    int querySingleTree(int node, int L, int R, int l, int r) const {
        if (L >= l && R <= r) return val[node];
        if (L > r || R < l) return 0;
        int sum = 0;
        int mid = (L + R) / 2;
        if (l <= mid) sum += querySingleTree(lc[node], L, mid, l, r);
        if (mid < r)  sum += querySingleTree(rc[node], mid+1, R, l, r);
        return sum;
    }
};
const int MAXN = 40010;
int N, M;
int A[MAXN], B[MAXN], C[MAXN];

int merge(int l, int r) {
    if (l == r) return 0;
    int mid = (l + r) / 2;
    int ans = merge(l, mid);
    ans += merge(mid+1, r);
    int p = l, q = mid+1, curr = l;
    while (p <= mid && q <= r) {
        if (B[p] < B[q]) {
            C[curr++] = B[p++];
        } else {
            ans += mid - p + 1;
            C[curr++] = B[q++];
        }
    }
    while (p <= mid) {
        C[curr++] = B[p++];
    }
    while (q <= r) {
        C[curr++] = B[q++];
    }
    assert(curr == r+1);
    for (int i = l; i <= r; i++) {
        B[i] = C[i];
    }
    return ans;
}

int main() {
    scanf("%d%d", &N, &M);
    for (int i = 1; i <= N; i++) {
        int x;
        scanf("%d", &x);
        A[i] = B[i] = x;
    }
    sort(B+1, B+N+1);
    for (int i = 1; i <= N; i++) {
        A[i] = lower_bound(B+1, B+N+1, A[i]) - B;
    }

    for (int i = 1; i <= N; i++) B[i] = A[i];
    int ans = merge(1, N);
    printf("%d ", ans);

    SegmentInFenwick sif(N, N+1, N);
    
    for (int i = 1; i <= N; i++) {
        sif.add(i, A[i], 1);
    }

    for (int i = 1; i <= M; i++) {
        int p;
        scanf("%d", &p);
        int x = A[p];
        int d = sif.query(p-1, x, N) +
            sif.query(N, 1, x-1) - sif.query(p, 1, x-1);
        sif.add(p, A[p], -1);
        ans -= d;
        printf("%d ", ans);
    }
    
    return 0;
}
