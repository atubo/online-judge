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
        auto comb = [](int a, int b) {return min(a, b);};
        SegmentTreeMin st(N, 0, comb);
        vector<int> hiMark, loMark;
        vector<int> dp(N, INF);
        hiMark.push_back(0);
        loMark.push_back(0);
        dp[0] = (L == 1 ? 1 : INF);
        for (int i = 1; i < N; i++) {
            printf("i=%d\n", i);
            printVector(hiMark);
            printVector(loMark);
            int j = searchBoundary(hiMark, loMark, A[i]);
            printf("j=%d\n", j);
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
            update(hiMark, loMark, i);
        }
        cout << dp[N-1] << endl;
        printVector(dp);
    }

    int searchBoundary(const vector<int>& hiMark,
                       const vector<int>& loMark,
                       int x) {
        return max(search(hiMark, x), search(loMark, x));
    }

    int search(const vector<int>& mark, int x) {
        if (ptInRange(mark[0], x)) return -1;
        int lo = 0, hi = mark.size()-1;
        if (!ptInRange(mark[hi], x)) return mark[hi];
        while (lo < hi - 1) {
            int mid = (lo + hi) / 2;
            if (ptInRange(mark[mid], x)) hi = mid;
            else lo = mid;
        }
        return mark[lo];
    }

    bool ptInRange(int pos, int x) {
        return abs(A.at(pos) - x) <= S;
    }

    void update(vector<int>& hiMark, vector<int>& loMark, int pos) {
        while (!hiMark.empty() && A[pos] >= A[hiMark.back()]) {
            hiMark.pop_back();
        }
        hiMark.push_back(pos);
        while (!loMark.empty() && A[pos] <= A[loMark.back()]) {
            loMark.pop_back();
        }
        loMark.push_back(pos);
    }
};

int main() {
    Solution solution;
    solution.solve();
    return 0;
}
