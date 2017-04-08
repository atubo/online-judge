// https://www.luogu.org/problem/show?pid=1011
// 车站

#include <bits/stdc++.h>
using namespace std;
using PII = pair<int, int>;

const int MAXN = 22;
int F[MAXN];
int N;
PII up[MAXN], down[MAXN];

void fib() {
    F[0] = 0;
    F[1] = 1;
    for (int i = 2; i < MAXN; i++) {
        F[i] = F[i-1] + F[i-2];
    }
}

void setup() {
    up[1] = {1, 0};
    up[2] = {0, 1};
    for (int i = 3; i <= N; i++) {
        up[i] = {F[i-2], F[i-1]};
    }
    down[1] = {0, 0};
    down[2] = {0, 1};
    for (int i = 3; i <= N; i++) {
        down[i] = up[i-1];
    }
}

int calc(int a, int b, int n) {
    int ret = 0;
    for (int i = 1; i <= n; i++) {
        ret = ret + (up[i].first * a + up[i].second * b) -
            (down[i].first * a + down[i].second * b);
    }
    return ret;
}


int main() {
    int a, m, x;
    scanf("%d%d%d%d", &a,  &N, &m, &x);
    fib();
    setup();
    int b = 0;
    while (calc(a, b, N-1) < m) b++;
    printf("%d\n", calc(a, b, x));
    return 0;
}
