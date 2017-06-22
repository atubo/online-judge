// https://www.luogu.org/problem/show?pid=1353
// [USACO08JAN]跑步Running

#include <bits/stdc++.h>
using namespace std;

int main() {
    int N, M;
    scanf("%d%d", &N, &M);
    vector<int> dp1Prev(M+1, INT_MIN), dp1Curr(M+1, INT_MIN);
    vector<int> dp2Prev(M+1, INT_MIN), dp2Curr(M+1, INT_MIN);

    vector<int> D(N+1);
    for (int i = 1; i <= N; i++) {
        scanf("%d", &D[i]);
    }

    dp2Prev[0] = 0;
    for (int i = 1; i <= N; i++) {
        dp1Curr[1] = dp2Prev[0] + D[i];
        for (int j = 2; j <= M; j++) {
            dp1Curr[j] = dp1Prev[j-1] + D[i];
        }
        for (int j = M-1; j >= 0; j--) {
            dp2Curr[j] = max(dp1Prev[j+1], dp2Prev[j+1]);
        }
        dp2Curr[0] = max(dp2Curr[0], dp2Prev[0]);
        swap(dp1Prev, dp1Curr);
        swap(dp2Prev, dp2Curr);
    }
    printf("%d\n", dp2Prev[0]);
    return 0;
}
