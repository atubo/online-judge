// https://www.luogu.org/problem/show?pid=3402
// 最长公共子序列

#include <bits/stdc++.h>
using namespace std;


class SegmentTree {
public:
    SegmentTree(int n, int init)
        :data(max(3*n, 30), init), nData(n) {}

    void update(int i, int value) {
        i += nData + 1;
        data[i] = value;
        for (; i > 1; i >>= 1) {
            int newVal = max(data[i], data[i^1]);
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
                res = max(res, data[a]);
            }
            if ((b & 0) == 0) {
                res = max(res, data[b]);
            }
        }
        return res;
    }

private:
    vector<int> data;
    int nData;
};

using PII = pair<int, int>;

int main() {
    int N, M;
    scanf("%d %d", &N, &M);
    vector<int> A(N);
    for (int i = 0; i < N; i++) {
        scanf("%d", &A[i]);
    }
    vector<int> B(M);
    for (int i = 0; i < M; i++) {
        scanf("%d", &B[i]);
    }

    vector<PII> AP(N);
    for (int i = 0; i < N; i++) {
        AP[i] = make_pair(A[i], i);
    }
    sort(AP.begin(), AP.end());

    vector<PII> BP(M);
    for (int i = 0; i < M; i++) {
        BP[i] = make_pair(B[i], i);
    }
    sort(BP.begin(), BP.end());

    vector<int> match(N, -1);
    for (int i = 0, j =0; i < N; i++) {
        while (j < M && BP[j].first < AP[i].first) j++;
        if (j == M) break;
        if (BP[j].first == AP[i].first) {
            match[AP[i].second] = BP[j].second;
        }
    }

    SegmentTree st(M, 0);
    for (int i = 0; i < N; i++) {
        int p = match[i];
        if (p >= 0) {
            st.update(p, p == 0 ? 1 : st.query(0, p-1) + 1);
        }
    }

    printf("%d\n", st.query(0, M-1));

    return 0;
}
