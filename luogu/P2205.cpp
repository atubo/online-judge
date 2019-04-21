// https://www.luogu.org/problemnew/show/P2205
// [USACO13JAN]画栅栏Painting the Fence

#include <bits/stdc++.h>
using namespace std;

// note it's 1-indexed
class SegmentTree {
    int N;
    int64_t *val, *lazy;

public:
    SegmentTree(int N_): N(N_) {
        val = new int64_t[4*N]{};
        lazy = new int64_t[4*N]{};
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
        return query(1, a, b, 1, N);
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

    // query range sum in [a, b], current node is [L, R]
    int64_t query(int k, int a, int b, int L, int R) {
        if (!k) return 0;
        if (b < L || a > R) return 0;
        pushDown(k, L, R);
        if (a <= L && R <= b) return val[k];
        int64_t sum = 0;
        int mid = (L + R) / 2;
        if (a <= mid) sum += query(2*k, a, b, L, mid);
        if (mid < b)  sum += query(2*k+1, a, b, mid+1, R);
        return sum;
    }
};

int N, K;

int main() {
    scanf("%d%d", &N, &K);
    int curr = 0;
    vector<int> a;
    a.push_back(curr);
    for (int i =0; i < N; i++) {
        int x;
        char line[10];
        scanf("%d %s", &x, line);
        if (line[0] == 'L') {
            curr -= x;
        } else {
            curr += x;
        }
        a.push_back(curr);
    }
    vector<int> sorted = a;
    sort(sorted.begin(), sorted.end());
    sorted.erase(unique(sorted.begin(), sorted.end()), sorted.end());

    const int m = sorted.size();

    for (int i = 0; i < (int)a.size(); i++) {
        a[i] = lower_bound(sorted.begin(), sorted.end(), a[i])
            - sorted.begin();
    }

    SegmentTree st(2*m);
    for (int i = 1; i < (int)a.size(); i++) {
        int l = a[i-1];
        int r = a[i];
        if (l > r) swap(l, r);
        st.update(1, 2*l+1, 2*r-1);
    }

    int ans = 0;
    for (int i = 0; i < m-1; i++) {
        int c = st.query(2*i+1, 2*i+1);
        if (c >= K) {
            ans += sorted[i+1] - sorted[i];
        }
    }
    printf("%d\n", ans);

    return 0;
}
