// https://www.luogu.org/problem/show?pid=1198
// [JSOI2008]最大数
#include <limits.h>
#include <algorithm>
#include <cstdio>
#include <vector>
using namespace std;

int64_t D;

class SegmentTreeMax {
public:
    SegmentTreeMax(int n, int init):data(max(3*n, 30), init), nData(n) {}

    void update(int i, int value) {
        i += nData + 1;
        data[i] = value;
        for (; i > 1; i >>= 1) {
            int newVal = max(data[i], data[i^1]);
            if (data[i>>1] == newVal) break;
            data[i>>1] = newVal;
        }
    }

    int findMax(int a, int b) const {
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

    int findMax() const {
        return data[1];
    }
private:
    vector<int> data;
    int nData;
};

int64_t add(int64_t a, int64_t b) {
    return (a + b + D) % D;
}

int main() {
    int M;
    scanf("%d %lld", &M, &D);
    int64_t last = 0;
    int64_t x;
    char str[10];
    int count = 0;
    SegmentTreeMax st(M, INT_MIN);

    while (M--) {
        scanf("%s %lld", str, &x);
        if (str[0] == 'Q') {
            last = st.findMax(count-x, count-1);
            printf("%lld\n", last);
        } else {
            st.update(count++, add(last, x));
        }
    }
    return 0;
}
