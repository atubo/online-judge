// http://poj.org/problem?id=3186
//#include <bits/stdc++.h>
#include <algorithm>
#include <cstdio>
#include <iostream>
#include <numeric>
#include <vector>
using namespace std;

class Solution {
private:
    int N;
    vector<int> V;
    vector<int> ps;
public:
    Solution() {
        cin >> N;
        V.resize(N);
        for (int i = 0; i < N; i++) {
            scanf("%d", &V[i]);
        }
        ps.resize(N);
        partial_sum(V.begin(), V.end(), ps.begin());
    }

    void solve() {
        vector<vector<int> > dp(N, vector<int>(N, 0));
        for (int i = 0; i < N; i++) {
            dp[i][i] = V[i];
        }
        for (int len = 2; len <= N; len++) {
            for (int i = 0; i <= N - len; i++) {
                int j = i + len - 1;
                int x1 = V[i] + ps_query(i+1, j) + dp[i+1][j];
                int x2 = ps_query(i, j-1) + dp[i][j-1] + V[j];
                dp[i][j] = max(x1, x2);
            }
        }
        cout << dp[0][N-1] << endl;
    }

    int ps_query(int i, int j) {
        if (i == 0) return ps[j];
        else return ps[j] - ps[i-1];
    }
};

int main() {
    Solution solution;
    solution.solve();
    return 0;
}
