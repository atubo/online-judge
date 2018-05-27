// https://www.luogu.org/problemnew/show/P2312
// 解方程

#include <bits/stdc++.h>
using namespace std;

const int MAXN = 110;
const int MOD = 1000000007;
int N, M;
int64_t A[MAXN];
int res[1000003];
int cnt;

int64_t read() {
    int64_t sum = 0, fg = 1;
    char c = getchar();
    while (c < '0' || c > '9') {
        if (c == '-') fg = -1;
        c = getchar();
    }
    while (c >= '0' && c <= '9') {
        sum = (sum * 10 + c - '0') % MOD;
        c = getchar();
    }
    return sum * fg;
}

int add(int64_t a, int64_t b) {
    return (a + b) % MOD;
}

int mul(int64_t a, int64_t b) {
    return (a * b) % MOD;
}

bool check(int x) {
    int64_t y = A[N];
    for (int i = N-1; i >= 0; i--) {
        y = mul(y, x) + A[i];
        if (y >= MOD) y -= MOD;
    }
    return y == 0;
}

int main() {
    scanf("%d%d", &N, &M);
    for (int i = 0; i <= N; i++) {
        A[i] = read();
    }
    for (int x = 1; x <= M; x++) {
        if (check(x)) res[cnt++] = x;
    }
    printf("%d\n", cnt);
    for (int i = 0; i < cnt; i++) {
        printf("%d\n", res[i]);
    }
    return 0;
}
