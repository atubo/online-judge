// https://www.luogu.org/problemnew/show/P3760
// [TJOI2017]异或和

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
        data = new int[sz];
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

    int query(int a, int b) const {
        a += nData_;
        b += nData_;
        int res = NULL_VALUE;
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

    int query() const {
        return data[1];
    }
private:
    int *data;
    int nData_;
    int combine(int a, int b) const {
        return a + b;
    }
};

const int MAXN = 100010;
const int MAXS = 1000010;
int N;
int S[MAXN];
int ans;

void solve(int k) {
    int cnt = 0;
    SegmentTreeSPU st0(MAXS), st1(MAXS);
    st0.update(0, 1);
    for (int i = 1; i <= N; i++) {
        int d = (S[i] >> k) & 1;
        int r = S[i] & ((1<<k) - 1);
        //printf("i=%d d=%d r=%d\n", i, d, r);
        if (d) {
            cnt += st0.query(0, r) + st1.query(r+1, MAXS-1);
            int now = st1.query(r, r);
            st1.update(r, now+1);
        } else {
            cnt += st0.query(r+1, MAXS-1) + st1.query(0, r);
            int now = st0.query(r, r);
            st0.update(r, now+1);
        }
    }
    if (cnt & 1) ans |= (1<<k);
    //printf("k=%d cnt=%d\n", k, cnt);
}

int main() {
    scanf("%d", &N);
    for (int i = 1; i <= N; i++) {
        int x;
        scanf("%d", &x);
        S[i] = S[i-1] + x;
    }
    for (int k = 0; k < 20; k++) {
        solve(k);
    }
    printf("%d\n", ans);
    return 0;
}
