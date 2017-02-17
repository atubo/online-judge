// https://www.luogu.org/problem/show?pid=2059
// [JLOI2013]卡牌游戏

#include <bits/stdc++.h>
using namespace std;

double dp[52][52];
int N, M;
int A[52];

int main() {
    scanf("%d %d", &N, &M);
    for (int i = 0; i < M; i++) {
        scanf("%d", &A[i]);
        A[i]--;
    }

    dp[1][0] = 1;
    for (int n = 2; n <= N; n++) {
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < M; j++) {
                int x = A[j] % n;
                if (x == i) continue;
                int k = (i + n - (x+1) % n) % n;
                dp[n][i] += 1.0/M * dp[n-1][k];
            }
        }
    }
    for (int i = 0; i < N; i++) {
        printf("%.2f%% ", dp[N][i]*100);
    }
    printf("\n");
    return 0;
}
