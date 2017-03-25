// https://www.luogu.org/problem/show?pid=3076
// [USACO13FEB]出租车Taxi

#include <bits/stdc++.h>
using namespace std;

const int MAXN = 100010;
int s[MAXN], t[MAXN];
int N, M;

int main() {
    int64_t ret = 0;
    scanf("%d %d", &N, &M);
    for (int i = 0; i < N; i++) {
        scanf("%d %d", &s[i], &t[i]);
        ret += abs(s[i] - t[i]);
    }

    s[N] = M;
    t[N] = 0;

    sort(s, s+N+1);
    sort(t, t+N+1);
    for (int i = 0; i <= N; i++) {
        ret += abs(s[i] - t[i]);
    }
    printf("%lld\n", ret);
    return 0;
}
