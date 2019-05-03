// https://www.luogu.org/problemnew/show/P2917
// [USACO08NOV]玩具Toys

#include <bits/stdc++.h>
using namespace std;

// note it's 1-indexed
class SegmentTree {
    int N;
    int *val, *lazy;

public:
    SegmentTree(int N_): N(N_) {
        val = new int[4*N+1]{};
        lazy = new int[4*N+1]{};
    }

    ~SegmentTree() {
        delete[] val;
        delete[] lazy;
    }
    // set 0 to range [a, b]
    void update(int a, int b) {
        update(1, 1, N, a, b);
    }

    // set value at position x to t
    void set(int t, int x) {
        set(1, t, 1, N, x);
    }

    // query range sum in [a, b]
    int query(int a, int b) {
        return query(1, 1, N, a, b);
    }

private:
    // set 0 to range [a, b], current node range is [l, r]
    void update(int k, int l, int r, int a, int b) {
        if (a > b) return;
        pushDown(k, l, r);
        if (a <= l && r <= b) {
            val[k] = 0;
            lazy[k] = 1;
            return;
        }
        if (l == r) return;
        int mid = (l + r) / 2;
        if (a <= mid) update(2*k,   l, mid, a, b);
        if (mid < b)  update(2*k+1, mid+1, r, a, b);
        val[k] = val[2*k] + val[2*k+1];
    }

    void pushDown(int k, int l, int r) {
        if (!lazy[k] || l == r) return;
        lazy[2*k] = lazy[k];
        lazy[2*k+1] = lazy[k];
        val[2*k] = val[2*k+1] = 0;
        lazy[k] = 0;
    }

    // query range sum in [a, b], current node is [l, r]
    int query(int k, int l, int r, int a, int b) {
        if (!k) return 0;
        if (b < l || a > r) return 0;
        pushDown(k, l, r);
        if (a <= l && r <= b) return val[k];
        int sum = 0;
        int mid = (l + r) / 2;
        if (a <= mid) sum += query(2*k, l, mid, a, b);
        if (mid < b)  sum += query(2*k+1, mid+1, r, a, b);
        return sum;
    }

    void set(int k, int t, int l, int r, int x) {
        if (l == r) {
            val[k] = t;
            lazy[k] = 0;
            return;
        }
        pushDown(k, l, r);
        int mid = (l + r) / 2;
        if (x <= mid) set(2*k, t, l, mid, x);
        else          set(2*k+1, t, mid+1, r, x);
        val[k] = val[2*k] + val[2*k+1];
    }
};

const int MAXD = 100010;
int D;
int T[MAXD], S[MAXD];
int TC, N1, N2, C1, C2;

int solve1() {
    int ans = 0;
    for (int i = 1; i <= D; i++) {
        ans += T[i];
    }
    return TC*ans;
}

void update(SegmentTree &st, int r, int x) {
    int lo = 0, hi = r+1;
    while (lo < hi - 1) {
        int mid = (lo + hi) / 2;
        int q = st.query(mid, r);
        if (q >= x) lo = mid;
        else hi = mid;
    }
    int t = st.query(lo, r) - x;
    st.update(lo, r);
    st.set(t, lo);
}


int solve(int mid) {
    memset(S, 0, (D+1)*sizeof(int));
    int tot = mid;
    int ans = tot * TC;
    int p2 = 1;
    deque<int> dq;
    for (int t = 1; t <= D; t++) {
        if (t-N1 >= 1) dq.push_back(t-N1);
        S[t] = T[t];
        if (tot >= T[t]) {
            tot -= T[t];
        } else {
            int r = T[t] - tot;
            tot = 0;
            while (r > 0 && p2 <= t - N2) {
                if (S[p2] <= r) {
                    ans += S[p2]*C2;
                    r -= S[p2];
                    S[p2] = 0;
                    p2++;
                } else {
                    ans += r*C2;
                    S[p2] -= r;
                    r = 0;
                }
            }
            while (!dq.empty() && dq.front() <= t-N2) dq.pop_front();
            while (r > 0) {
                int p1 = dq.back();
                if (S[p1] <= r) {
                    ans += S[p1]*C1;
                    r -= S[p1];
                    S[p1] = 0;
                    dq.pop_back();
                } else {
                    ans += r*C1;
                    S[p1] -= r;
                    r = 0;
                }
            }
        }
    }
    return ans;
}

int find_lo() {
    SegmentTree st(D);
    int ans = 0;
    for (int t = 1; t <= D; t++) {
        int q = st.query(1, t-N1);
        if (T[t] <= q) {
            update(st, t-N1, T[t]);
        } else {
            st.update(1, t-N1);
            ans += T[t]-q;
        }
        st.set(T[t], t);
    }
    return ans;
}

int main() {
    scanf("%d%d%d%d%d%d", &D, &N1, &N2, &C1, &C2, &TC);
    int tot = 0;
    for (int i = 1; i <= D; i++) {
        scanf("%d", &T[i]);
        tot += T[i];
    }

    if (TC <= min(C1, C2)) {
        printf("%d\n", solve1());
        return 0;
    }

    if (N1 > N2) {
        swap(N1, N2);
        swap(C1, C2);
    }
    C2 = min(C1, C2);

    int lo = find_lo(), hi = tot;
    while (lo < hi - 3) {
        int d = (hi - lo) / 3;
        int mid1 = lo + d;
        int mid2 = lo + 2*d;
        int c1 = solve(mid1);
        int c2 = solve(mid2);
        if (c2 < c1) lo = mid1;
        else hi = mid2;
    }

    int ans = INT_MAX;
    for (int i = lo; i <= hi; i++) {
        ans = min(ans, solve(i));
    }

    printf("%d\n", ans);

    return 0;
}
