// https://www.luogu.org/problemnew/show/P2678
// 跳石头

#include <bits/stdc++.h>
using namespace std;

const int MAXN = 50010;

int L, N, M;
int D[MAXN];

bool check(int x) {
    int last = 0;
    int cnt = 0;
    for (int i = 0; i < N; i++) {
        if (D[i] - last < x) cnt++;
        else last = D[i];
    }
    if (L-last < x) cnt++;
    return cnt <= M;
}

int main() {
    scanf("%d%d%d", &L, &N, &M);
    for (int i = 0; i < N; i++) {
        scanf("%d", &D[i]);
    }
    int lo = 1;
    int hi = L+1;
    while (lo < hi - 1) {
        int mid = (lo + hi) / 2;
        if (check(mid)) lo = mid;
        else            hi = mid;
    }
    printf("%d\n", lo);
    return 0;
}
