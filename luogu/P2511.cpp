// https://www.luogu.org/problemnew/show/P2511
// [HAOI2008]木棍分割

#include <bits/stdc++.h>
using namespace std;

const int MAXN = 50010;
const int MOD = 10007;
int N, M;
int L[MAXN];
int dp1[MAXN], dp2[MAXN], dp3[MAXN];

bool check(int t) {
    int s = 0, p = 0;
    for (int q = 1; q <= N; q++) {
        if (L[q] - L[p] > t) {
            s++;
            p = q - 1;
        }
    }
    return s <= M;
}

int solve(int len) {
    int ans = 0;
    int *p1 = dp1, *p2= dp2, *p3 = dp3;
    p1[0] = 1;
    for (int m = 1; m <= M+1; m++) {
        p3[0] = p1[0];
        for (int i = 1; i <= N; i++) {
            p3[i] = (p1[i] + p3[i-1]) % MOD;
        }
        p2[0] = 0;
        int p = 0;
        for (int i = 1; i <= N; i++) {
            p2[i] = 0;
            while (L[i] - L[p] > len) p++;
            p2[i] = (p3[i-1] - (p == 0 ? 0 : p3[p-1]) + MOD) % MOD;
        }

        swap(p1, p2);
        ans = (ans + p1[N]) % MOD;
    }

    return ans;
}

int main() {
    scanf("%d%d", &N, &M);
    int maxl = 0;
    for (int i = 1; i <= N; i++) {
        scanf("%d", &L[i]);
        maxl = max(maxl, L[i]);
        L[i] += L[i-1];
    }
    int lo = maxl-1, hi = L[N];
    while (lo < hi-1) {
        int mid = (lo + hi) / 2;
        if (check(mid)) hi = mid;
        else lo = mid;
    }
    printf("%d %d", hi, solve(hi));
    return 0;
}
