// https://www.luogu.org/problem/show?pid=1356
// 数列的整数性

#include <bits/stdc++.h>
using namespace std;

int mod(int a, int b) {
    return ((a % b) + b) % b;
}

bool dp[2][100];

void init() {
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 100; j++) {
            dp[i][j] = false;
        }
    }
    dp[0][0] = true;
}

int main() {
    int M;
    scanf("%d", &M);
    while (M--) {
        int N, K;
        scanf("%d%d", &N, &K);
        init();
        int curr = 0;
        for (int i = 1; i <= N; i++) {
            int x;
            scanf("%d", &x);
            x = mod(x, K);
            for (int j = 0; j < K; j++) {
                dp[curr^1][j] = false;
            }
            for (int j = 0; j < K; j++) {
                if (dp[curr][j]) {
                    dp[curr^1][mod(j+x, K)] = dp[curr^1][mod(j-x, K)] = true;
                }
            }
            curr = curr ^ 1;
        }
        printf(dp[curr][0] ? "Divisible\n" : "Not divisible\n");
    }
    return 0;
}
