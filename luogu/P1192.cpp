// https://www.luogu.org/problem/show?pid=1192
// 台阶问题

#include <bits/stdc++.h>
using namespace std;

const int MOD = 100003;

int add(int a, int b) {
    return (a + b) % MOD;
}

int sub(int a, int b) {
    return (a + MOD - b) % MOD;
}

int dp[100010];
int ps[100010];
int N, K;

int main() {
    cin >> N >> K;
    dp[1] = 1;
    ps[1] = 1;
    for (int i = 2; i <= N+1; i++) {
        dp[i] = sub(ps[i-1], ps[max(0, i-K-1)]);
        ps[i] = add(ps[i-1], dp[i]);
    }
    cout << dp[N+1] << endl;
    return 0;
}
