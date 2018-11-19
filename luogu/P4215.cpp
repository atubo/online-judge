// https://www.luogu.org/problemnew/show/P4215
// 踩气球

#include <bits/stdc++.h>
using namespace std;

struct SegmentInFenwick {
    int N;  // number of positions, index is 1-based
    int M;  // number of weights, index is 0-based
    int T_cnt;
    int *root;
    int *val, *lc, *rc;

    // cap is the number of elements to be added
    SegmentInFenwick(int N_, int M_, int cap): N(N_), M(M_), T_cnt(1) {
        root = new int[N+1]{};
        //const int numOfNodes = cap * int(log2(N)+2) * int(log2(M)+2);
        const int numOfNodes = 1e7;
        val = new int[numOfNodes]{};
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

const int MAXN = 1e5+10;
int N, M, Q;
int A[MAXN];
int L[MAXN], R[MAXN];

int main() {
    set<int> ones;
    scanf("%d%d", &N, &M);
    for (int i = 1; i <= N; i++) {
        scanf("%d", &A[i]);
        if (A[i] > 0) ones.insert(i);
    }
    for (int i = 1; i <= M; i++) {
        scanf("%d%d", &L[i], &R[i]);
    }
    scanf("%d", &Q);
    SegmentInFenwick st(N+1, N+1, Q);
    for (int i = 1; i <= M; i++) {
        st.add(L[i], R[i], 1);
    }
    int lastans = 0;
    for (int i = 1; i <= Q; i++) {
        int x;
        scanf("%d", &x);
        x = (x + lastans - 1) % N + 1;
        if (--A[x] == 0) {
            auto it = ones.find(x);
            int left = 1;
            if (it != ones.begin()) {
                auto it1 = it;
                --it1;
                left = *it1 + 1;
            }
            int right = N;
            auto it2 = it;
            it2++;
            if (it2 != ones.end()) right = *it2 - 1;
            int d = st.query(x, x, right) - st.query(left-1, x, right);
            lastans += d;
            printf("%d\n", lastans);

            ones.erase(it);
        } else {
            printf("%d\n", lastans);
        }
    }

    return 0;
}
