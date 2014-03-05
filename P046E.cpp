#include <iostream>
#include <cstdio>
using namespace std;

int main()
{
    int n, m;
    cin >> n >> m;
    int64_t a[n][m+1];
    for (int i = 0; i < n; i++) {
        a[i][0] = 0;
        for (int j = 1; j <= m; j++) {
            int x;
            scanf("%d", &x);
            a[i][j] = x;
        }
    }

    int sum[n][m+1];
    for (int i = 0; i < n; i++) {
        sum[i][0] = 0;
        for (int j = 1; j <= m; j++) {
            sum[i][j] = sum[i][j-1] + a[i][j];
        }
    }

    int64_t dp[n][m+1];
    dp[0][0] = 0;
    for (int j = 1; j <= m; j++) {
        dp[0][j] = sum[0][j];
    }
    for (int j = m-1; j >= 1; j--) {
        dp[0][j] = max(dp[0][j], dp[0][j+1]);
    }

    for (int i = 1; i < n; i++) {
        dp[i][0] = 0;
        if (i % 2 == 1) {
            for (int j = 1; j < m; j++) {
                dp[i][j] = sum[i][j] + dp[i-1][j+1];
            }
            for (int j = 2; j < m; j++) {
                dp[i][j] = max(dp[i][j-1], dp[i][j]);
            }
        } else {
            for (int j = 2; j <= m; j++) {
                dp[i][j] = sum[i][j] + dp[i-1][j-1];
            }
            for (int j = m-1; j > 1; j--) {
                dp[i][j] = max(dp[i][j+1], dp[i][j]);
            }
        }
    }
    if (n % 2 == 1) {
        cout << dp[n-1][2] << endl;
    } else {
        cout << dp[n-1][m-1] << endl;
    }

    return 0;
}
