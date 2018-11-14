// https://www.luogu.org/problemnew/show/P1083
// 借教室

#include <bits/stdc++.h>
using namespace std;

const int MAXN = 1e6 + 10;
int A[MAXN];

// support query for range min
// note it's 1-indexed
class SegmentTreeMin {
    int N;
    int *val, *lazy;

public:

    SegmentTreeMin(int N_): N(N_) {
        val = new int[4*N]{};
        lazy = new int[4*N]{};

    }

    ~SegmentTreeMin() {
        delete[] val;
        delete[] lazy;
    }
    // add t to range [a, b]
    int update(int t, int a, int b) {
        return update(1, t, 1, N, a, b);
    }

    void init() {
        init(1, 1, N);
    }

private:

    // add t to range [a, b], current node range is [l, r]
    int update(int k, int t, int l, int r, int a, int b) {
        if (a > b) return INT_MAX;
        if (lazy[k] &&  l != r) {
            lazy[2*k] += lazy[k];
            lazy[2*k+1] += lazy[k];
            val[2*k] += lazy[k];
            val[2*k+1] += lazy[k];
            lazy[k] = 0;
        }
        if (a <= l && r <= b) {
            val[k] += t;
            lazy[k] += t;
            return val[k];
        }
        if (l == r) return val[k];
        int mid = (l + r) / 2;
        int ret = INT_MAX;
        if (a <= mid) ret = update(2*k,   t, l, mid, a, b);
        if (mid < b)  ret = min(ret, update(2*k+1, t, mid+1, r, a, b));
        val[k] = val[2*k] < val[2*k+1] ? val[2*k] : val[2*k+1];
        return ret;
    }

    void init(int k, int l, int r) {
        if (l == r) {
            val[k] = A[l];
            return;
        }
        int mid = (l + r) / 2;
        init(2*k, l, mid);
        init(2*k+1, mid+1, r);
        val[k] = min(val[2*k], val[2*k+1]);
    }
};

int N, M;

int main() {
    scanf("%d%d", &N, &M);
    SegmentTreeMin st(N);
    for (int i = 1; i <= N; i++) {
        scanf("%d", &A[i]);
    }
    st.init();
    int ans = 0, id = -1;
    for (int i = 1; i <= M; i++) {
        int d, s, t;
        scanf("%d%d%d", &d, &s, &t);
        if (st.update(-d, s, t) < 0) {
            ans = -1;
            id = i;
            break;
        }
    }
    printf("%d\n", ans);
    if (ans == -1) printf("%d\n", id);
    return 0;
}
