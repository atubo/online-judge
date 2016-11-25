// http://www.tyvj.cn/p/1059
#include <bits/stdc++.h>
using namespace std;

class Solution {
private:
    int L, S, T, M;
    vector<int> stones;
public:
    Solution() {
        cin >> L >> S >> T >> M;
        stones.resize(M);
        for (int i = 0; i < M; i++) {
            cin >> stones[i];
        }
        sort(stones.begin(), stones.end());
    }

    int solve1() {
        return count_if(stones.begin(), stones.end(),
                        [this](int x) { return x % T == 0;});
    }

    int calc(const map<int, int>& dp, int p) {
        int mx = INT_MAX;
        for (int i = p + S; i <= p + T; i++) {
            mx = min(mx, dp.at(i));
        }
        return mx;
    }

    int calcShift(map<int, int>& dp, int p) {
        int ret = INT_MAX;
        for (int i = p - 1; i >= p - T; i--) {
            dp[i] = calc(dp, i);
            ret = min(ret, dp[i]);
        }
        return ret;
    }

    int solve2(vector<int>& st) {
        map<int, int> dp;
        if (st.empty()) return 0;
        int p = st.back();
        dp[p] = 1;
        for (int i = 1; i <= T; i++) {
            dp[p+i] = 0;
        }
        while (!st.empty()) {
            p = st.back();
            st.pop_back();
            int q = (st.empty() ? 0 : st.back());
            if (p - q >= T * T + 1) {
                return calcShift(dp, p) + solve2(st);
            } else {
                for (int i = p-1; i >= q; i--) {
                    dp[i] = calc(dp, i);
                }
                if (q > 0) dp[q]++;
            }
        }
        return dp[0];
    }

    void solve() {
        int ret = (S == T ? solve1() : solve2(stones));
        cout << ret << endl;
    }
};

int main() {
    Solution solution;
    solution.solve();
    return 0;
}

