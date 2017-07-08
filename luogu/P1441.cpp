// https://www.luogu.org/problem/show?pid=1441
// 砝码称重

#include <bits/stdc++.h>
using namespace std;

int A[21];
bool rm[21];
int N, M;
int ret;

void calc() {
    vector<bitset<2001>> dp(N+1);
    dp[0][0] = true;
    for (int i = 1; i <= N; i++) {
        dp[i] = dp[i-1];
        if (!rm[i]) dp[i] |= (dp[i-1] << A[i]);
    }

    ret = max(ret, (int)dp[N].count()-1);
}

void dfs(int p, int m) {
    if (m == 0) {
        calc();
        return;
    }

    for (int i = p; i <= N+1-m; i++) {
        rm[i] = true;
        dfs(i+1, m-1);
        rm[i] = false;
    }
}

int main() {
    cin >> N >> M;
    for (int i = 1; i <= N; i++) {
        cin >> A[i];
    }

    dfs(1, M);
    cout << ret << endl;
    
    return 0;
}
