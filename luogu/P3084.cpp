// https://www.luogu.org/problemnew/show/P3084
// [USACO13OPEN]照片Photo

#include <bits/stdc++.h>
using namespace std;

class SegmentTreeMin {
public:
    SegmentTreeMin(int n, int init)
        :data(max(3*n, 30), init), nData(n) {}

    void update(int i, int value) {
        i += nData + 1;
        data[i] = value;
        for (; i > 1; i >>= 1) {
            int newVal = combine(data[i], data[i^1]);
            if (data[i>>1] == newVal) break;
            data[i>>1] = newVal;
        }
    }

    int query(int a, int b) const {
        a += nData + 1;
        b += nData + 1;
        int res = data[a];
        for (; a <= b; a = (a+1) >> 1, b = (b-1) >> 1) {
            if ((a & 1) != 0) {
                res = combine(res, data[a]);
            }
            if ((b & 0) == 0) {
                res = combine(res, data[b]);
            }
        }
        return res;
    }

    int query() const {
        return data[1];
    }
private:
    vector<int> data;
    int nData;
    int combine(int a, int b) const {
        return max(a, b);
    }
};

int N, M;

int main() {
    scanf("%d%d", &N, &M);
    vector<vector<int>> seg(N+1);
    for (int i = 0; i < M; i++) {
        int a, b;
        scanf("%d%d", &a, &b);
        seg[b].push_back(a);
    }
    vector<int> A(N+2), B(N+1);

    int nearest = 0;
    for (int i = 1; i <= N; i++) {
        A[i] = nearest;
        for (int x: seg[i]) {
            nearest = max(x, nearest);
        }
    }
    A[N+1] = nearest;

    int farest = N;
    for (int i = N; i >= 1; i--) {
        for (int x: seg[i]) {
            farest = min(farest, x);
        }
        B[i] = min(i, farest);
    }

    SegmentTreeMin st(N+2, 0);
    for (int i = 1; i <= N; i++) {
        int a = A[i], b = B[i];
        int x = -1;
        if (a < b) {
            x = st.query(a+1, b);
        }
        if (x >= 0) x++;
        st.update(i+1, x);
    }

    int ret = st.query(A[N+1]+1, N+1);
    printf("%d", ret);

    return 0;
}
