// https://www.luogu.org/problemnew/show/P4269
// [USACO18FEB]Snow Boots G

#include <bits/stdc++.h>
using namespace std;

// note it's 1-indexed
class SegmentTree {
    int N;
    int *left_, *right_, *mid_;

public:
    SegmentTree(int N_): N(N_) {
        left_ = new int[4*N+1]{};
        right_ = new int[4*N+1]{};
        mid_ = new int[4*N+1]{};
    }

    ~SegmentTree() {
        delete[] left_;
        delete[] right_;
        delete[] mid_;
    }
    // add t to position a
    void update(int a) {
        update(1, 1, N, a);
    }

    int query() {
        return mid_[1];
    }

private:
    void update(int k, int l, int r, int a) {
        if (l == r) {
            left_[k] = right_[k] = mid_[k] = 1;
            return;
        }
        int mid = (l + r) / 2;
        if (a <= mid) update(2*k,   l, mid, a);
        else          update(2*k+1, mid+1, r, a);
        pushUp(k, l, r);
    }

    void pushUp(int k, int l, int r) {
        int mid = (l + r) / 2;
        left_[k] = left_[2*k];
        if (left_[k] == mid - l + 1) left_[k] += left_[2*k+1];
        right_[k] = right_[2*k+1];
        if (right_[k] == r - mid) right_[k] += right_[2*k];
        mid_[k] = max(mid_[2*k], mid_[2*k+1]);
        mid_[k] = max(mid_[k], right_[2*k]+left_[2*k+1]);
        mid_[k] = max(mid_[k], max(left_[k], right_[k]));
    }
};

const int MAXN = 100010;
int N, B;
int F[MAXN];
bool ans[MAXN];

struct Boot {
    int s, d, id;
    bool operator < (const Boot &other) const {
        if (s != other.s) return s < other.s;
        if (d != other.d) return d < other.d;
        return id < other.id;
    }
} S[MAXN];

struct Position {
    int h, x;
    bool operator < (const Position &other) const {
        if (h != other.h) return h < other.h;
        return x < other.x;
    }
} P[MAXN];

int main() {
    scanf("%d%d", &N, &B);
    for (int i = 1; i <= N; i++) {
        scanf("%d", &P[i].h);
        P[i].x = i;
    }
    sort(P+1, P+N+1);
    for (int i = 1; i <= B; i++) {
        int s, d;
        scanf("%d%d", &s, &d);
        S[i] = {s, d, i};
    }
    sort(S+1, S+B+1);

    SegmentTree st(N);
    auto last = P+N+1;
    for (int i = B; i >= 1; i--) {
        int s = S[i].s;
        int d = S[i].d;
        int id = S[i].id;
        auto curr = lower_bound(P+1, P+N+1, Position{s+1, 0});
        for (auto it = curr; it != last; ++it) {
            st.update(it->x);
        }
        ans[id] = (st.query() < d);
        last = curr;
    }

    for (int i = 1; i <= B; i++) {
        printf("%d\n", ans[i]);
    }

    return 0;
}
