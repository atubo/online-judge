// http://codeforces.com/problemset/problem/487/B

#include <iostream>
#include <vector>

using namespace std;

#define INF 123456789

#define READ_ARRAY(N, A) \
    for (int i = 0; i < N; i++) {\
        cin >> A[i];\
    }

template <typename T>
void printVector(const vector<T>& A) {
    for (const T& x: A) {
        cout << x << " ";
    }
    cout << endl;
}

#include <iostream>
#include <algorithm>
#include <functional>
#include <vector>
#include <limits>
using namespace std;

class SegmentTreeMin {
public:
    SegmentTreeMin(int n, int init, function<int(int, int)> combine_)
        :data(max(3*n, 30), init), nData(n), combine(combine_) {}

    void update(int i, int value) {
        i += nData + 1;
        data[i] = value;
        for (; i > 1; i >>= 1) {
            int newVal = combine(data[i], data[i^1]);
            if (data[i>>1] == newVal) break;
            data[i>>1] = newVal;
        }
    }

    int findMin(int a, int b) const {
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

    int findMin() const {
        return data[1];
    }
private:
    vector<int> data;
    int nData;
    function<int(int, int)> combine;
};

class Solution {
private:
    int N, S, L;
    vector<int> A;
public:
    Solution() {
        cin >> N >> S >> L;
        A.resize(N);
        READ_ARRAY(N, A);
    }

    void solve() {
        auto combMin = [](int a, int b) {return min(a, b);};
        auto combMax = [](int a, int b) {return max(a, b);};

        SegmentTreeMin st(N, 0, combMin);
        SegmentTreeMin hiMark(N, 0, combMax);
        SegmentTreeMin loMark(N, 0, combMin);

        vector<int> dp(N, INF);
        hiMark.update(0, A[0]);
        loMark.update(0, A[0]);
        dp[0] = (L == 1 ? 1 : INF);
        st.update(0, dp[0]);
        for (int i = 1; i < N; i++) {
            hiMark.update(i, A[i]);
            loMark.update(i, A[i]);
            int j = searchBoundary(hiMark, loMark, i);
            if (i - j < L) {
                dp[i] = INF;
            } else {
                if (j < 0) {
                    dp[i] = 1;
                } else {
                    dp[i] = st.findMin(j, i-L);
                    if (dp[i] != INF) dp[i]++;
                }
            }
            st.update(i, dp[i]);
        }
        cout << (dp[N-1] == INF ? -1 : dp[N-1]) << endl;
    }

    int rangeDiff(const SegmentTreeMin& hiMark,
                  const SegmentTreeMin& loMark,
                  int i, int j) {
        return hiMark.findMin(i, j) - loMark.findMin(i, j);
    }

    int searchBoundary(const SegmentTreeMin& hiMark,
                       const SegmentTreeMin& loMark,
                       int pos) {
        if (rangeDiff(hiMark, loMark, 0, pos) <= S) return -1;
        int lo = 0, hi = pos;
        while (lo < hi - 1) {
            int mid = (lo + hi) / 2;
            if (rangeDiff(hiMark, loMark, mid, pos) <= S) hi = mid;
            else lo = mid;
        }
        return lo;
    }
};

int main() {
    Solution solution;
    solution.solve();
    return 0;
}
