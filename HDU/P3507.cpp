// http://acm.hdu.edu.cn/showproblem.php?pid=3507
// Print Article

#include <inttypes.h>
#include <cstdio>
#include <deque>
#include <iostream>
using namespace std;

const int MAXN = 500010;
int64_t C[MAXN];
int64_t S[MAXN];
int64_t dp[MAXN];
int N, M;

int64_t Y(int i) {
    return dp[i] + S[i] * S[i];
}

int64_t X(int i) {
    return 2 * S[i];
}

int64_t numer(int k, int j) {
    return Y(j) - Y(k);
}

int64_t denom(int k, int j) {
    return X(j) - X(k);
}

bool isConvex(int a, int b, int c) {
    return numer(a, b) * denom(b, c) <= numer(b, c) * denom(a, b);
}

int64_t getDp(int i, int j) {
    return dp[j] + (S[i] - S[j]) * (S[i] - S[j]) + M;
}

int main() {
    // initialize N and S
    while (scanf("%d %d", &N, &M) == 2) {
        for (int i = 1; i <= N; i++) {
            scanf("%lld", &C[i]);
            S[i] = S[i-1] + C[i];
        }

        dp[0] = 0;
        deque<int> q;
        q.push_back(0);
        for (int i = 1; i <= N; i++) {
            if (S[i] == S[i-1]) {
                dp[i] = dp[i-1];
                continue;
            }
            while (q.size() > 1 && numer(q[0], q[1]) <= denom(q[0], q[1]) * S[i]) {
                q.pop_front();
            }
            dp[i] = getDp(i, q.front());
            while (q.size() > 1 && !isConvex(q[q.size()-2], q[q.size()-1], i)) {
                q.pop_back();
            }
            q.push_back(i);
        }
        printf("%lld\n", dp[N]);
    }
    return 0;
}
