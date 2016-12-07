// http://www.51nod.com/onlineJudge/questionCode.html#!problemId=1202
#include <bits/stdc++.h>
using namespace std;

const int64_t MOD = 1000000007;

int64_t add(int64_t a, int64_t b) {
    return (a + b) % MOD;
}

int64_t sub(int64_t a, int64_t b) {
    return (a + MOD - b) % MOD;
}

int64_t mul(int64_t a, int64_t b) {
    return (a * b) % MOD;
}

int64_t count(const vector<int64_t>& ps, int p, int q) {
    if (p == 0) return ps[q];
    else return sub(ps[q], ps[p-1]);
}

int main() {
    int N;
    scanf("%d", &N);
    vector<int64_t> A(N+1);
    for (int i = 1; i <= N; i++) {
        scanf("%lld", &A[i]);
    }
    vector<int64_t> dp(N+1);
    vector<int64_t> ps(N+1);
    dp[0] = 1;
    ps[0] = 1;
    vector<int> last(100001, 0);
    for (int i = 1; i <= N; i++) {
        dp[i] = count(ps, last[A[i]], i-1);
        ps[i] = add(ps[i-1], dp[i]);
        last[A[i]] = i;
    }
    cout << ps[N]-1 << endl;
    return 0;
}
