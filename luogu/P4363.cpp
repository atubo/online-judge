// https://www.luogu.org/problemnew/show/P4363
// [九省联考2018]一双木棋chess

#include <bits/stdc++.h>
using namespace std;

int N, M;
int A[12][12], B[12][12];
unordered_map<int64_t, int> dp;

int64_t encode(int *a) {
    int64_t ret = 0;
    for (int i = 0; i < N; i++) {
        ret |= (int64_t(a[i]) << (i*4));
    }
    return ret;
}

int solve(int *a, int d) {
    int64_t code = encode(a);
    if (dp.find(code) != dp.end()) return dp[code];
    int& ret = dp[code];
    if (d == N*M) return ret = 0;

    bool fei = ((d & 1) == 0);
    if (fei) ret = -1e8;
    else ret = 1e8;

    for (int i = N-1; i > 0; i--) {
        if (a[i] < a[i-1]) {
            a[i]++;
            if (fei) {
                ret = max(ret, A[i][a[i]-1] + solve(a, d+1));
            } else {
                ret = min(ret, -B[i][a[i]-1] + solve(a, d+1));
            }
            a[i]--;
        }
    }
    if (a[0] < M) {
        a[0]++;
        if (fei) {
            ret = max(ret, A[0][a[0]-1] + solve(a, d+1));
        } else {
            ret = min(ret, -B[0][a[0]-1] + solve(a, d+1));
        }
        a[0]--;
    }
    return ret;
}

int main() {
    scanf("%d%d", &N, &M);
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            scanf("%d", &A[i][j]);
        }
    }
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            scanf("%d", &B[i][j]);
        }
    }
    int a[N] = {0};
    int ans = solve(a, 0);
    printf("%d\n", ans);
    return 0;
}
