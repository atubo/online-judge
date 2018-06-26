// https://www.luogu.org/problemnew/show/P3750
// [六省联考2017]分手是祝愿

#include <bits/stdc++.h>
using namespace std;

// (g, x, y) that a*x + b*y = g
void ext_gcd(int64_t a, int64_t b, int64_t &g, int64_t &x, int64_t &y) {
    if (b == 0) {
        g = a; x = 1; y = 0;
        return;
    }
    int64_t dp, xp, yp;
    ext_gcd(b, a % b, dp, xp, yp);
    g = dp;
    x = yp;
    y = xp - a / b * yp;
}

// find x that a*x = b mod n
int64_t mod_solve(int64_t a, int64_t b, int n) {
    int64_t d, xp, yp;
    ext_gcd(a, n, d, xp, yp);
    if (b % d == 0) {
        int64_t x0 = (xp * (b / d) % n + n) % n;
        return x0;
    } else {
        abort();
    }
}

const int P = 100003;
const int MAXN = 100010;
int N, K;
bool status[MAXN];

int solveSteps() {
    vector<vector<int>> f(N+1);
    for (int i = 2; i < N; i++) {
        for (int j = i; j <= N; j+=i) {
            f[j].push_back(i);
        }
    }
    int ans = 0;
    for (int i = N; i > 0; i--) {
        if (status[i]) {
            ans++;
            status[1] = !status[1];
            for (int x: f[i]) {
                status[x] = !status[x];
            }
        }
    }
    return ans;
}

int add(int64_t a, int64_t b) {
    return (a + b) % P;
}

int mul(int64_t a, int64_t b) {
    return (a * b) % P;
}

void solve(int nsteps) {
    vector<int> f(N+1);
    f[N] = 1;
    for (int i = N-1; i > K; i--) {
        int inv = mod_solve(i, 1, P);
        f[i] = add(1, mul(mul(N-i, f[i+1]+1), inv));
    }
    int ans = min(K, nsteps);
    for (int i = K+1; i <= nsteps; i++) {
        ans = add(ans, f[i]);
    }
    for (int i = 2; i <= N; i++) {
        ans = mul(ans, i);
    }
    printf("%d\n", ans);
}

int main() {
    scanf("%d%d", &N, &K);
    for (int i = 1; i <= N; i++) {
        int x;
        scanf("%d", &x);
        status[i] = (x == 1);
    }
    int nsteps = solveSteps();
    solve(nsteps);
    return 0;
}
