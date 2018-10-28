// https://www.luogu.org/problemnew/show/P3948
// 数据结构

#include <bits/stdc++.h>
using namespace std;

const int MAXN = 80010;
int N, P, MOD, LO, HI;
int64_t A[MAXN];

void solve(int l, int r) {
    int ans = 0;
    int64_t x = 0;
    for (int i = 1; i <= r; i++) {
        x += A[i];
        if (i >= l) {
            int rx = (1LL * x * i) % MOD;
            ans += (rx >= LO && rx <= HI);
        }
    }
    printf("%d\n", ans);
}

void solve2(int l, int r) {
    printf("%ld\n", A[r] - A[l-1]);
}

void process() {
    int64_t x = 0;
    for (int i = 1; i <= N; i++) {
        x += A[i];
        int rx = (1LL * x * i) % MOD;
        A[i] = A[i-1] + (rx >= LO && rx <= HI);
    }
}

int main() {
    scanf("%d%d%d%d%d", &N, &P, &MOD, &LO, &HI);
    char cmd[5];
    for (int i = 0; i < P; i++) {
        int l, r, x;
        scanf("%s", cmd);
        if (cmd[0] == 'A') {
            scanf("%d%d%d", &l, &r, &x);
            A[l] += x;
            A[r+1] -= x;
        } else {
            scanf("%d%d", &l, &r);
            solve(l, r);
        }
    }

    process();

    int final;
    scanf("%d", &final);
    while (final--) {
        int l, r;
        scanf("%d%d", &l, &r);
        solve2(l, r);
    }
    return 0;
}
