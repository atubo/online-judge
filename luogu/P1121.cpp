// https://www.luogu.org/problemnew/show/P1121
// 环状最大两段子段和

#include <bits/stdc++.h>
using namespace std;

const int MAXN = 200010;
int N;
int A[MAXN], B[MAXN], C[MAXN];

int solve() {
    int ps = 0, mn = 0;
    B[0] = INT_MIN;
    for (int i = 1; i <= N; i++) {
        ps += A[i];
        B[i] = max(B[i-1], ps - mn);
        mn = min(mn, ps);
    }

    ps = 0, mn = 0;
    C[N+1] = INT_MIN;
    for (int i = N; i >= 1; i--) {
        ps += A[i];
        C[i] = max(C[i+1], ps - mn);
        mn = min(mn, ps);
    }

    int64_t ret = INT_MIN;
    for (int i = 1; i <= N; i++) {
        ret = max(ret, (int64_t)B[i] + C[i+1]);
    }
    return ret;
}

int solve2() {
    int ps = A[1], mn = A[1];
    B[1] = INT_MIN;
    for (int i = 2; i <= N; i++) {
        ps += A[i];
        B[i] = max(B[i-1], ps - mn);
        mn = min(mn, ps);
    }
    ps = mn = A[N];
    C[N] = INT_MIN;
    for (int i = N-1; i >= 1; i--) {
        ps += A[i];
        C[i] = max(C[i+1], ps - mn);
        mn = min(mn, ps);
    }

    int64_t ret = INT_MIN;
    for (int i = 2; i <= N-3; i++) {
        ret = max(ret, (int64_t)B[i] + C[i+2]);
    }
    return ret;
}

int main() {
    scanf("%d", &N);
    for (int i = 1; i <= N; i++) {
        scanf("%d", &A[i]);
    }

    int ret = solve();
    int total = 0;
    for (int i = 1; i <= N; i++) {
        total += A[i];
        A[i] = -A[i];
    }
    ret = max(ret, total + solve2());
    printf("%d", ret);
    return 0;
}
