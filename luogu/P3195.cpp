// https://www.luogu.org/problem/show?pid=3195
// P3195 [HNOI2008]玩具装箱TOY

#include <inttypes.h>
#include <cstdio>
#include <deque>
using namespace std;

const int MAXN = 50010;
int64_t C[MAXN];
int64_t S[MAXN];
int64_t dp[MAXN];
int N, L;

int64_t Y(int i) {
    return dp[i] + S[i]*S[i] + 2 * S[i] * (L+1);
}

int64_t X(int i) {
    return 2 * S[i];
}

int64_t numer(int j, int k) {
    return Y(j) - Y(k);
}

int64_t denom(int j, int k) {
    return X(j) - X(k);
}

bool isConvex(int a, int b, int c) {
    return numer(b, a) * denom(c, b) <= numer(c, b) * denom(b, a);
}

int64_t getDp(int i, int j) {
    return dp[j] + (S[i] - S[j] - L - 1) * (S[i] - S[j] - L - 1);
}

int main() {
    scanf("%d %d", &N, &L);
    for (int i = 1; i <= N; i++) {
        scanf("%lld", &C[i]);
        S[i] = C[i] + S[i-1];
    }
    for (int i = 1; i <= N; i++) {
        S[i] += i;
    }

    dp[0] = 0;
    deque<int> q;
    q.push_back(0);
    for (int i = 1; i <= N; i++) {
        while (q.size() > 1 && numer(q[1], q[0]) <= denom(q[1], q[0]) * S[i]) {
            q.pop_front();
        }
        dp[i] = getDp(i, q.front());
        while (q.size() > 1 && !isConvex(q[q.size()-2], q[q.size()-1], i)) {
            q.pop_back();
        }
        q.push_back(i);
    }

    printf("%lld\n", dp[N]);
    return 0;
}
