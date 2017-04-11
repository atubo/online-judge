// https://www.luogu.org/problem/show?pid=1114
// “非常男女”计划

#include <bits/stdc++.h>
using namespace std;

const int MAXN = 100010;
int L[2*MAXN];
int N;

int main() {
    memset(L, -1, sizeof(L));
    scanf("%d", &N);
    L[N] = 0;
    int ret = 0, s = 0;
    for (int i = 1; i <= N; i++) {
        int x;
        scanf("%d", &x);
        if (x == 1) s++;
        else s--;
        if (L[s+N] != -1) ret = max(ret, i - L[s+N]);
        else L[s+N] = i;
    }
    printf("%d\n", ret);
    return 0;
}
