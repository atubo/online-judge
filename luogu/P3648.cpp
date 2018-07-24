// https://www.luogu.org/problemnew/show/P3648
// [APIO2014]序列分割

#include <bits/stdc++.h>
using namespace std;

const int MAXN = 100010;
int N, K;
int64_t dp[MAXN][210];
int split[MAXN][210];
int A[MAXN];
int64_t ps[MAXN];
int curr_k;

namespace ConvextHullTrick {

    int64_t Y(int i) {
        int64_t res = ps[i]*ps[i] - dp[i][curr_k-1];
        return res;
    }

    int64_t X(int i) {
        return ps[i];
    }

    int64_t numer(int k, int j) {
        return Y(j) - Y(k);
    }

    int64_t denom(int k, int j) {
        return X(j) - X(k);
    }

    bool isConvex(int a, int b, int c) {
        return numer(a, b) * denom(b, c) < numer(b, c) * denom(a, b);
    }

    int64_t getDp(int i, int j) {
        int64_t res = dp[j][curr_k-1] + (ps[i]-ps[j]) * ps[j];
        return res;
    }

    void runDp() {
        // initialize N and S

        deque<int> q;
        q.push_back(curr_k-1);
        for (int i = curr_k; i <= N; i++) {
            // it may make sense to skip 0 elements
            // if that's the case, un-comment the following
            /*
            if (S[i] == S[i-1]) {
                dp[i] = dp[i-1];
                continue;
            }
            */
            while (q.size() > 1 && numer(q[0], q[1]) <= denom(q[0], q[1]) * ps[i]) {
                q.pop_front();
            }
            dp[i][curr_k] = getDp(i, q.front());
            split[i][curr_k] = q.front();
            while (q.size() > 1 && !isConvex(q[q.size()-2], q[q.size()-1], i)) {
                q.pop_back();
            }
            q.push_back(i);
        }
    }
}


int main() {
    scanf("%d%d", &N, &K);
    K++;
    for (int i = 1; i <= N; i++) {
        scanf("%d", &A[i]);
        ps[i] = ps[i-1] + A[i];
    }
    for (int i = 1; i <= N; i++) {
        dp[i][1] = 0;
        split[i][1] = i;
    }
    for (curr_k = 2; curr_k <= K; curr_k++) {
        ConvextHullTrick::runDp();
    }
    printf("%lld\n", dp[N][K]);
    vector<int> ans(K);
    for (int k = K, p = N; k > 1; k--) {
        ans[k-1] = split[p][k];
        p = ans[k-1];
        printf("%d ", p);
    }
    return 0;
}
