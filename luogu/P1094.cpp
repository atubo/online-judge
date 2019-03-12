// https://www.luogu.org/problemnew/show/P1094
// 纪念品分组

#include <bits/stdc++.h>
using namespace std;

const int MAXN = 30010;
int W, N;
int P[MAXN];

int main() {
    scanf("%d", &W);
    scanf("%d", &N);
    for (int i = 0; i < N; i++) {
        scanf("%d", &P[i]);
    }
    sort(P, P+N);
    int p = 0, q = N-1;
    int ans = 0;
    while (p < q) {
        if (P[p] + P[q] <= W) {
            p++;
            q--;
        } else {
            q--;
        }
        ans++;
    }
    ans += (p == q);
    printf("%d\n", ans);
    return 0;
}
