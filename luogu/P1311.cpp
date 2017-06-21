// https://www.luogu.org/problem/show?pid=1311
// 选择客栈

#include <bits/stdc++.h>
using namespace std;

class SegmentTree {
public:
    SegmentTree(int n, int init) :data(max(3*n, 30), init), nData(n) {}

    void update(int i, int value) {
        i += nData + 1;
        data[i] = value;
        for (; i > 1; i >>= 1) {
            int newVal = min(data[i], data[i^1]);
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
                res = min(res, data[a]);
            }
            if ((b & 0) == 0) {
                res = min(res, data[b]);
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
};

int N, K, P;

int main() {
    scanf("%d%d%d", &N, &K, &P);
    vector<vector<int>> lodge(K);
    SegmentTree st(N, INT_MAX);

    for (int i = 0; i < N; i++) {
        int c, p;
        scanf("%d%d", &c, &p);
        lodge[c].push_back(i);
        if (p <= P) st.update(i, i);
    }

    int64_t res = 0;
    for (int k = 0; k < K; k++) {
        for (int x: lodge[k]) {
            int y = st.query(x, N-1);
            if (y == INT_MAX) break;
            res += lodge[k].end() - lower_bound(lodge[k].begin(),
                                                lodge[k].end(),
                                                y)
                - (y == x);
        }
    }

    printf("%lld\n", res);
    return 0;
}
