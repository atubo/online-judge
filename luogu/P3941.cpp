// https://www.luogu.org/problemnew/show/P3941
// 入阵曲

#include <bits/stdc++.h>
using namespace std;

const int MAXN = 410;
const int MAXK = 1e6+10;
int N, M, K;

int A[MAXN][MAXN];
int seen[MAXN];
int cnt[MAXK];

int main() {
    scanf("%d%d%d", &N, &M, &K);
    for (int i = 1; i <= N; i++) {
        for (int j = 1; j <= M; j++) {
            int x;
            scanf("%d", &x);
            A[i][j] = (A[i-1][j] + A[i][j-1] - A[i-1][j-1] + K + x) % K;
        }
    }
    int64_t ans = 0;
    for (int i = 1; i <= M; i++) {
        for (int j = i; j <= M; j++) {
            cnt[0] = 1;
            for (int row = 1; row <= N; row++) {
                int x = (A[row][j] - A[row][i-1] + K) % K;
                ans += cnt[x];
                seen[row] = x;
                cnt[x]++;
            }
            for (int row = 1; row <= N; row++) {
                cnt[seen[row]] = 0;
            }
        }
    }

    printf("%lld\n", ans);
    return 0;
}
