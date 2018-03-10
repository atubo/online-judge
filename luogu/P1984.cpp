// https://www.luogu.org/problemnew/show/P1984
// [SDOI2008]烧水问题

#include <bits/stdc++.h>
using namespace std;

int N;

int main() {
    scanf("%d", &N);
    long double ans = 1, last = 1;
    for (int i = 1; i < N; i++) {
        long double tmp = last * (2*i-1)/ (2*i);
        ans += tmp;
        last = tmp;
    }
    printf("%.2Lf\n", ans * 100 * 4200 / N);
    return 0;
}
