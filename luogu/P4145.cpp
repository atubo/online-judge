// https://www.luogu.org/problemnew/show/P4145
// 上帝造题的七分钟2 / 花神游历各国

#include <bits/stdc++.h>
using namespace std;

// note it's 1-indexed
class SegmentTree {
    int N;
    int64_t *val;
    bool *sealed_;

public:
    SegmentTree(int N_): N(N_) {
        val = new int64_t[4*N]{};
        sealed_ = new bool[4*N]{};
    }

    ~SegmentTree() {
        delete[] val;
        delete[] sealed_;
    }
    // add t to range [a, b]
    void update(int a, int b) {
        update(1, 1, N, a, b);
    }

    // query range sum in [a, b]
    int64_t query(int a, int b) {
        return query(1, a, b, 1, N);
    }

    void build(int64_t *arr) {
        build(1, 1, N, arr);
    }

private:
    void build(int k, int l, int r, int64_t *arr) {
        if (l == r) {
            val[k] = arr[l];
            return;
        }

        int mid = (l + r) / 2;
        build(2*k, l, mid, arr);
        build(2*k+1, mid+1, r, arr);
        combine(k);
    }

    void combine(int k) {
        val[k] = val[2*k] + val[2*k+1];
        sealed_[k] = sealed_[2*k] && sealed_[2*k+1];
    }

    void update(int k, int l, int r, int a, int b) {
        if (a > b) return;
        if (sealed_[k]) return;
        if (l == r) {
            val[k] = sqrt(val[k]);
            if (val[k] == 1) sealed_[k] = true;
            return;
        }
        int mid = (l + r) / 2;
        if (a <= mid) update(2*k,   l, mid, a, b);
        if (mid < b)  update(2*k+1, mid+1, r, a, b);
        combine(k);
    }

    // query range sum in [a, b], current node is [L, R]
    int64_t query(int k, int a, int b, int L, int R) {
        if (!k) return 0;
        if (b < L || a > R) return 0;
        if (a <= L && R <= b) return val[k];
        int64_t sum = 0;
        int mid = (L + R) / 2;
        if (a <= mid) sum += query(2*k, a, b, L, mid);
        if (mid < b)  sum += query(2*k+1, a, b, mid+1, R);
        return sum;
    }
};

const int MAXN = 1e5+10;
int N, M;
int64_t A[MAXN];

int main() {
    scanf("%d", &N);
    for (int i = 1; i <= N; i++) {
        scanf("%ld", &A[i]);
    }
    SegmentTree st(N);
    st.build(A);
    scanf("%d", &M);
    for (int i = 0; i < M; i++) {
        int k, l, r;
        scanf("%d%d%d", &k, &l, &r);
        if (l > r) swap(l, r);
        if (k == 0) {
            st.update(l, r);
        } else {
            printf("%ld\n", st.query(l, r));
        }
    }

    return 0;
}
