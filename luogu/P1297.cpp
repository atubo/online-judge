// https://www.luogu.org/problemnew/show/P1297
// [国家集训队]单选错位

#include <bits/stdc++.h>
using namespace std;

const int MAXN = 10000010;
int a[MAXN];

int main() {
    int n, A, B, C;
    scanf("%d%d%d%d%d", &n, &A, &B, &C, a+1);
    for (int i = 2; i <= n; i++) {
        a[i] = ((long long)a[i-1] * A + B) % 100000001;
    }
    for (int i = 1; i <= n; i++) {
        a[i] = a[i] % C + 1;
    }

    double ans;
    for (int i = 1; i < n; i++) {
        ans += 1.0 / max(a[i], a[i+1]);
    }
    ans += 1.0 / max(a[n], a[1]);
    printf("%.3f\n", ans);
    return 0;
}
