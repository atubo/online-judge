// https://www.luogu.org/problem/show?pid=1048
// 采药

#include <algorithm>
#include <cstdio>
using namespace std;

const int MAXT = 1010;
const int MAXM = 110;

int dp[MAXM][MAXT];
int value[MAXM];
int tm[MAXM];

int main() {
    int T, M;
    scanf("%d %d", &T, &M);
    for (int i = 1; i <= M; i++) {
        scanf("%d %d", &tm[i], &value[i]);
    }

    for (int m = 1; m <= M; m++) {
        for (int t = 1; t <= T; t++) {
            dp[m][t] = dp[m-1][t];
            if (t >= tm[m]) {
                dp[m][t] = max(dp[m][t], dp[m-1][t-tm[m]] + value[m]);
            }
        }
    }
    printf("%d\n", dp[M][T]);
    return 0;
}
