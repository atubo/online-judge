// http://acm.hdu.edu.cn/showproblem.php?pid=3709
// Balanced Number

#include <bits/stdc++.h>
using namespace std;

const int MAXTORQ = 405;
int64_t dp[MAXTORQ+10][19][10];
int digits[19];
int N;

int pivot;

int64_t dfs(int torq, int pos, int d, int ps, bool bounded) {
    assert(torq <= MAXTORQ && torq >= 0);

    bounded = bounded && d == digits[pos];
    if (!bounded && dp[torq][pos][d] != -1) {
        return dp[torq][pos][d];
    }

    int64_t ret = 0;
    int maxd = (bounded ? digits[pos-1] : 9);
    int currTorq = torq + d * (pos  - pivot);
    if (pos > pivot) {
        currTorq += ps;
    }
    if (currTorq > MAXTORQ || currTorq < 0) {
        ret = 0;
        goto FINISH;
    }

    if (pos == 0) {
        ret = (currTorq == 0);
        goto FINISH;
    }

    for (int nextd = 0; nextd <= maxd; nextd++) {
        ret += dfs(currTorq, pos-1, nextd, ps + d, bounded);
    }

FINISH:
    //printf("pivot=%d pos=%d d=%d ret=%lld\n", pivot, pos, d, ret);

    if (!bounded) {
        dp[torq][pos][d] = ret;
    }
    return ret;
}

int64_t solve(int64_t a) {
    if (a == 0) return 1;
    N = 0;
    while (a > 0) {
        digits[N++] = a % 10;
        a /= 10;
    }

    int64_t ans = 0;
    for (pivot = N-1; pivot >= 0; pivot--) {
        memset(dp, -1, sizeof(dp));
        for (int d = 0; d <= digits[N-1]; d++) {
            ans += dfs(0, N-1, d, 0, true);
        }
    }
    return ans - (N-1);
}

int64_t solve(int64_t a, int64_t b) {
    if (a == 0) return solve(b);
    return solve(b) - solve(a-1);
}

int main() {
    //memset(dp, -1, sizeof(dp));
    int T;
    cin >> T;
    while (T--) {
        int64_t a, b;
        cin >> a >> b;
        cout <<solve(a, b) << endl;
    }
    return 0;
}
