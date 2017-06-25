// https://www.luogu.org/problem/show?pid=2401
// 不等数列

#include <bits/stdc++.h>
using namespace std;

int add(int a, int b) {return (a+b) % 2015;}
int dp[1010];
int main() {
    int N, K;
    scanf("%d%d", &N, &K);
    dp[0] = 1;
    for (int i = 1; i <= N; i++) {
        for (int j = min(i, K); j > 0; j--) {
            dp[j] = add((j+1) * dp[j], (i-j) * dp[j-1]);
        }
    }
    printf("%d\n", dp[K]);
    return 0;
}
