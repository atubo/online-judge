// https://www.luogu.org/problemnew/show/P2070
// 刷墙

#include <bits/stdc++.h>
using namespace std;

// note it's 1-indexed
class SegmentTree {
    int N;
    int *val, *lazy;

public:
    SegmentTree(int N_): N(N_) {
        val = new int[4*N]{};
        lazy = new int[4*N]{};
    }

    ~SegmentTree() {
        delete[] val;
        delete[] lazy;
    }
    // add t to range [a, b]
    void update(int t, int a, int b) {
        update(1, t, 1, N, a, b);
    }

    // query range sum in [a, b]
    int64_t query(int a, int b) {
        return query(1, 1, N, a, b);
    }

private:
    // add t to range [a, b], current node range is [l, r]
    void update(int k, int t, int l, int r, int a, int b) {
        if (a > b) return;
        pushDown(k, l, r);
        if (a <= l && r <= b) {
            val[k] += t * (r-l+1);
            lazy[k] += t;
            return;
        }
        if (l == r) return;
        int mid = (l + r) / 2;
        if (a <= mid) update(2*k,   t, l, mid, a, b);
        if (mid < b)  update(2*k+1, t, mid+1, r, a, b);
        val[k] = val[2*k] + val[2*k+1];
    }

    void pushDown(int k, int l, int r) {
        if (!lazy[k] || l == r) return;
        lazy[2*k] += lazy[k];
        lazy[2*k+1] += lazy[k];
        int mid = (l + r) / 2;
        val[2*k] += (mid - l + 1) * lazy[k];
        val[2*k+1] += (r - mid) * lazy[k];
        lazy[k] = 0;
    }

    // query range sum in [a, b], current node is [l, r]
    int64_t query(int k, int l, int r, int a, int b) {
        if (!k) return 0;
        if (b < l || a > r) return 0;
        pushDown(k, l, r);
        if (a <= l && r <= b) return val[k];
        int64_t sum = 0;
        int mid = (l + r) / 2;
        if (a <= mid) sum += query(2*k, l, mid, a, b);
        if (mid < b)  sum += query(2*k+1, mid+1, r, a, b);
        return sum;
    }
};

const int MAXN = 100010;
int N;
struct Move {
    int start, end;
} moves[MAXN];

int main() {
    scanf("%d", &N);
    int curr = 0;
    vector<int> ordered;
    for (int i = 0; i < N; i++) {
        int dist;
        char dir[5];
        scanf("%d%s", &dist, dir);
        if (dir[0] == 'L') dist = -dist;
        int start = curr;
        int end = curr + dist;
        curr = end;
        if (start > end) swap(start, end);
        moves[i] = {start, end};
        ordered.push_back(start);
        ordered.push_back(end);
        ordered.push_back(start+1);
        ordered.push_back(start-1);
        ordered.push_back(end+1);
    }

    sort(ordered.begin(), ordered.end());
    ordered.erase(unique(ordered.begin(), ordered.end()), ordered.end());

    SegmentTree st(5*N);
    for (int i = 0; i < N; i++) {
        int start = lower_bound(ordered.begin(), ordered.end(),
                                moves[i].start) - ordered.begin();
        int end = lower_bound(ordered.begin(), ordered.end(),
                              moves[i].end) - ordered.begin();
        st.update(1, start, end);
    }

    const int m = ordered.size();
    int p = 0;
    int ans = 0;
    while (p < m) {
        while (p < m && st.query(p, p) < 2) p++;
        if (p == m) break;
        int q = p + 1;
        while (q < m && st.query(q, q) >= 2) q++;
        ans += ordered[q-1] - ordered[p];
        p = q;
    }

    printf("%d\n", ans);

    return 0;
}
