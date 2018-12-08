// https://www.luogu.org/problemnew/show/P3054
// [USACO12OPEN]跑圈Running Laps

#include <bits/stdc++.h>
using namespace std;

// segment tree with single point update and range query
// 0-indexed
class SegmentTreeSPU {
    static const int NULL_VALUE = 0;
public:
    SegmentTreeSPU(int n) {
        nData_ = 1;
        while (nData_ < n) nData_ = nData_ << 1;
        int sz = 2 * nData_ + 1;
        data = new int64_t[sz];
        for (int i = 0; i < sz; i++) data[i] = NULL_VALUE;
    }

    ~SegmentTreeSPU() {
        delete[] data;
    }

    void update(int i, int value) {
        i += nData_;
        data[i] = value;
        for (; i > 1; i >>= 1) {
            int newVal = combine(data[i], data[i^1]);
            if (data[i>>1] == newVal) break;
            data[i>>1] = newVal;
        }
    }

    void build() {
        // assume all leaf nodes are already set up
        for (int i = nData_-1; i >= 1; i--) {
            data[i] = combine(data[2*i], data[2*i+1]);
        }
    }

    int64_t query(int a, int b) const {
        a += nData_;
        b += nData_;
        int64_t res = NULL_VALUE;
        for (; a <= b; a = (a+1) >> 1, b = (b-1) >> 1) {
            if ((a & 1) != 0) {
                res = combine(res, data[a]);
            }
            if ((b & 1) == 0) {
                res = combine(res, data[b]);
            }
        }
        return res;
    }

private:
    int64_t *data;
    int nData_;
    int64_t combine(int64_t a, int64_t b) const {
        return a + b;
    }
};

const int MAXN = 100010;
int N, L, C;
int V[MAXN];
int toIdx[MAXN];

struct Runner {
    int r;
    int lap;
    int id;
    int order;
    bool operator < (const Runner &other) const {
        if (r < other.r) return true;
        if (other.r < r) return false;
        if (lap < other.lap) return true;
        if (lap > other.lap) return false;
        return id < other.id;
    }
} runner[MAXN];

int main() {
    scanf("%d%d%d", &N, &L, &C);
    for (int i = 0; i < N; i++) {
        scanf("%d", &V[i]);
    }
    sort(V, V+N);
    for (int i = 0; i < N; i++) {
        int lap = 1LL*V[i]*L/V[N-1];
        int r = (1LL*V[i]*L) % V[N-1];
        runner[i] = {r, lap, i};
    }

    sort(runner, runner+N);

    for (int i = 0; i < N; i++) {
        runner[i].order = i;
        toIdx[runner[i].id] = i;
    }

    int64_t ans = 0;
    SegmentTreeSPU st1(N), st2(N);
    for (int i = 0; i < N; i++) {
        int idx = toIdx[i];
        int order = runner[idx].order;
        int lap = runner[idx].lap;
        int n1 = st1.query(0, order-1);
        int s1 = st2.query(0, order-1);
        int n2 = st1.query(order+1, N-1);
        int s2 = st2.query(order+1, N-1);
        ans += 1LL*n1*lap - s1;
        ans += 1LL*n2*(lap-1) - s2;
        st1.update(order, 1);
        st2.update(order, lap);
    }

    printf("%ld", ans);

    return 0;
}
