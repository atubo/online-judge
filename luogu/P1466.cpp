// https://www.luogu.org/problemnew/show/P1466
// 集合 Subset Sums

#include <bits/stdc++.h>
using namespace std;

int N;
int64_t dp[400];

int main() {
    scanf("%d", &N);
    dp[0] = 1;
    for (int i = 1; i <= N; i++) {
        for (int j = 399; j >= i; j--) {
            dp[j] += dp[j-i];
        }
    }
    if ((N*(N+1)/2) & 1) printf("0\n");
    else printf("%ld\n", dp[N*(N+1)/4]/2);

    return 0;
}
