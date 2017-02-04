// https://www.luogu.org/problem/show?pid=1020
// 导弹拦截

#include <bits/stdc++.h>
using namespace std;

typedef vector<int>::iterator Iter;

class Solution {
private:
    int N;
    vector<int> A;
public:
    Solution() {
        int x;
        N = 0;
        while (scanf("%d", &x) == 1) {
            A.push_back(x);
            N++;
        }
    }

    int lds() {
        vector<int> dp(N+1, INT_MIN);
        dp[0] = INT_MAX;
        for (int i = 0; i < N; i++) {
            int x = A[i];
            Iter it = upper_bound(dp.begin(), dp.end(), x, greater<int>());
            *it = max(x, *it);
        }
        int ans = N;
        for (int i = N; i >= 0; i--) {
            if (dp[i] != INT_MIN) {
                ans = i;
                break;
            }
        }
        return ans;
    }

    int lis() {
        vector<int> dp(N+1, INT_MAX);
        dp[0] = INT_MIN;
        for (int i = 0; i < N; i++) {
            int x = A[i];
            Iter it = lower_bound(dp.begin(), dp.end(), x);
            *it = min(*it, x);
        }
        int ans = N;
        for (int i = N; i >= 0; i--) {
            if (dp[i] != INT_MAX) {
                ans = i;
                break;
            }
        }
        return ans;
    }

    void solve() {
        int ans1 = lds();
        int ans2 = lis();
        printf("%d\n%d\n", ans1, ans2);
    }
};

int main() {
    Solution solution;
    solution.solve();
    return 0;
}
