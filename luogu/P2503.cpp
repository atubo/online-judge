// https://www.luogu.org/problemnew/show/P2503
// [HAOI2006]均分数据

#include <bits/stdc++.h>
using namespace std;

const int MAXN = 22;
int N, M;
double XAVE;
int A[MAXN], S[MAXN];
double dp[MAXN][7];
double ans;

double solve(int *arr) {
    for (int i = 1; i <= N; i++) {
        S[i] = S[i-1] + arr[i];
    }
    for (int i = N; i >= 1; i--) {
        double x = fabs(S[N]-S[i-1]-XAVE);
        dp[i][1] = x * x;
    }
    for (int k = 2; k <= M; k++) {
        for (int i = 1; i <= N+1-k; i++) {
            dp[i][k] = 1e18;
            for (int j = i+1; j <= N+2-k; j++) {
                double x = fabs(S[j-1]-S[i-1]-XAVE);
                dp[i][k] = min(dp[i][k], dp[j][k-1] + x*x);
            }
        }
    }
    return dp[1][M];
}

void anneal() {
    double nowans = ans, T = 2000;
    while (T > 1e-6) {
        int x = 0, y = 0;
        while (x == y) {
            x = rand() % N + 1;
            y = rand() % N + 1;
        }
        swap(A[x], A[y]);
        double now = solve(A);
        double delta = now-ans;
        if (delta < 0) ans = nowans = now;
        else if (exp(-delta/T)*RAND_MAX > rand()) nowans = now;
        else swap(A[x], A[y]);
        T *= 0.993;
    }

    for (int i = 1; i <= N; i++) {
        for (int j = 1; j <= N; j++) {
            swap(A[i], A[j]);
            ans = min(ans, solve(A));
            swap(A[i], A[j]);
        }
    }
}

void solve() {
    ans = 1e10;
    while ((double)clock()/CLOCKS_PER_SEC < 0.8) anneal();
}

int main() {
    srand(19260817);
    srand(rand());
    srand(rand());
    scanf("%d%d", &N, &M);
    double tot = 0;
    for (int i = 1; i <= N; i++) {
        scanf("%d", &A[i]);
        tot += A[i];
    }
    XAVE = tot/M;

    solve();
    if (ans / M < 1e-6) printf("0.00\n");
    else printf("%.2f\n", sqrt(ans/M));

    return 0;
}
