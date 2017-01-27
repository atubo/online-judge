// https://www.luogu.org/problem/show?pid=1474
// P1474 货币系统 Money Systems

#include <inttypes.h>
#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

int64_t dp[26][10001];

int main() {
    int V, N;
    cin >> V >> N;
    vector<int> D(V);
    for (int i = 0; i < V; i++) {
        cin >> D[i];
    }
    sort(D.begin(), D.end());
    D.erase(unique(D.begin(), D.end()), D.end());
    V = D.size();

    for (int i = 0; i <= V; i++) {
        dp[i][0] = 1;
    }
    for (int i = 1; i <= N; i++) {
        dp[0][i] = 0;
    }

    for (int v = 1; v <= V; v++) {
        for (int n = 1; n <= N; n++) {
            dp[v][n] = dp[v-1][n];
            if (n - D[v-1] >= 0) {
                dp[v][n] += dp[v][n-D[v-1]];
            }
        }
    }
    cout << dp[V][N] << endl;
    return 0;
}
