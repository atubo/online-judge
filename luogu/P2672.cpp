// https://www.luogu.org/problem/show?pid=2672
// 推销员

#include <bits/stdc++.h>
using namespace std;

int N;
const int MAXN = 100010;
int S[MAXN], A[MAXN];

using PII = pair<int, int>;

class SegmentTree {
public:
    SegmentTree(int n, function<PII(PII, PII)> combine_)
        :data(max(3*n, 30)), nData(n), combine(combine_) {}

    void update(int i, int value) {
        i += nData + 1;
        data[i] = make_pair(value, i - nData - 1);
        for (; i > 1; i >>= 1) {
            PII newVal = combine(data[i], data[i^1]);
            if (data[i>>1] == newVal) break;
            data[i>>1] = newVal;
        }
    }

    PII query(int a, int b) const {
        a += nData + 1;
        b += nData + 1;
        PII res = data[a];
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

    PII query() const {
        return data[1];
    }
private:
    vector<PII> data;
    int nData;
    function<PII(PII, PII)> combine;
};

PII select(const PII& left, const PII& right, int s0) {
    if (left.first > right.first - s0) return left;
    else return right;
}

int main() {
    scanf("%d", &N);
    for (int i = 0; i < N; i++) {
        scanf("%d", &S[i]);
    }
    for (int i = 0; i < N; i++) {
        scanf("%d", &A[i]);
    }

    auto f = [](const PII& a, const PII& b) {
        return max(a, b);
    };

    SegmentTree st1(N, f) , st2(N, f);
    for (int i = 0; i < N; i++) {
        st1.update(i, A[i]);
        st2.update(i, 2*S[i] + A[i]);
    }

    int64_t ret = 0;
    int d = -1;
    for (int i = 0; i < N; i++) {
        PII left = make_pair(INT_MIN/4, -1), right = make_pair(INT_MIN/4, -1);
        if (d >= 1) left = st1.query(0, d-1);
        if (d < N-1) right = st2.query(d+1, N-1);
        PII pick = select(left, right, d < 0 ? 0 : 2 * S[d]);
        if (pick.second > d) {
            ret += pick.first - (d < 0 ? 0 : 2 * S[d]);
            d = pick.second;
        }
        else {
            ret += pick.first;
        }
        st1.update(pick.second, 0);
        printf("%lld\n", ret);
    }

    return 0;
}
