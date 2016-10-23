// http://codeforces.com/problemset/problem/343/C
#include <algorithm>
#include <iostream>
#include <map>
#include <vector>

using namespace std;

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

class Solution {
private:
    int N, M;
    vector<int64_t> H, P;
    map<int64_t, int> posToIdx;
    vector<int64_t> pos;
public:
    Solution() {
        cin >> N >> M;
        H.resize(N);
        READ_ARRAY(N, H);
        P.resize(M);
        READ_ARRAY(M, P);
    }

    void solve() {
        pos = H;
        pos.insert(pos.end(), P.begin(), P.end());
        sort(pos.begin(), pos.end());
        pos.erase(unique(pos.begin(), pos.end()), pos.end());

        for (int i = 0; i < (int)pos.size(); i++) {
            posToIdx[pos[i]] = i;
        }

        for (int i = 0; i < N; i++) {
            H[i] = posToIdx[H[i]];
        }

        const int T = pos.size();
        vector<int64_t> dp(T);

        // initial condition
        int p = H[0];
        for (int i = 0; i <= p; i++) {
            dp[i] = dist(0, p);
        }
        for (int i = p+1; i < (N==1 ? T : H[1]); i++) {
            dp[i] = dist(0, p, i);
        }

        for (int idx = 1; idx < N; idx++) {
            p = H[idx];
            int q = H[idx-1];
            int imax = (idx == N-1 ? T : H[idx+1]);
            for (int i = p; i < imax; i++) {
                dp[i] = search(dp, q, p, i);
            }
        }
        cout << dp.back() << endl;
    }

    int64_t dist(int i, int j) {
        return pos[j] - pos[i];
    }

    int64_t dist(int i, int j, int k) {
        return pos[k] - pos[i] + min(pos[j]-pos[i], pos[k]-pos[j]);
    }

    int64_t search(const vector<int64_t>& dp, int q, int p, int i) {
        // search range is [q+1, p]
        if (dist(q+1, p, i) <= dp[q]) return dp[q];
        if (dist(p, p, i) >= dp[p-1]) return dist(p, p, i);
        int lo = q+1, hi = p;
        while (lo < hi - 1) {
            int mid = (lo + hi) / 2;
            if (dist(mid, p, i) > dp[mid-1]) lo = mid;
            else hi = mid;
        }
        return min(max(dist(lo, p, i), dp[lo-1]),
                   max(dist(hi, p, i), dp[hi-1]));
    }
};

int main() {
    Solution solution;
    solution.solve();
    return 0;
}

