// http://acm.hdu.edu.cn/showproblem.php?pid=2829
// Lawrence

#include <bits/stdc++.h>
using namespace std;


const int MAXN = 1010;
int64_t C[MAXN];    // save input array here
int64_t T[MAXN];
int64_t S[MAXN];
int64_t dp[2][MAXN];
int N, M;
int m;

int64_t Y(int i) {
    return dp[(m+1)%2][i] + T[i];
}

int64_t X(int i) {
    return S[i];
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
    return dp[(m+1)%2][j] + S[i]*(S[i]-S[j]) - (T[i]-T[j]);
}

int main() {
    // initialize N and S
    while (true) {
        scanf("%d %d", &N, &M);
        if (N == 0) break;

        for (int i = 1; i <= N; i++) {
            scanf("%lld", &C[i]);
            S[i] = S[i-1] + C[i];
            T[i] = T[i-1] + S[i]*C[i];
        }
        for (int i = 0; i <= N; i++) {
            dp[0][i] = S[i]*S[i] - T[i];
        }

        for (m = 1; m <= M; m++) {
            dp[m%2][0] = S[N] * S[N] - T[N];
            deque<int> q;
            q.push_back(0);
            for (int i = 1; i <= N; i++) {
                while (q.size() > 1 && numer(q[0], q[1]) <= denom(q[0], q[1]) * S[i]) {
                    q.pop_front();
                }
                dp[m%2][i] = getDp(i, q.front());
                while (q.size() > 1 && !isConvex(q[q.size()-2], q[q.size()-1], i)) {
                    q.pop_back();
                }
                q.push_back(i);
            }
        }
        printf("%lld\n", dp[M%2][N]);
    }
    return 0;
}
