// https://www.luogu.org/problem/show?pid=3198
// [HNOI2008]遥远的行星

#include <bits/stdc++.h>
using namespace std;

int N;
int64_t M[100010], ps[100010];
const int UP = 67;

int main() {
    double A;
    scanf("%d %lf", &N, &A);
    for (int i = 1; i <= N; i++) {
        scanf("%lld", &M[i]);
        ps[i] = M[i] + ps[i-1];
    }
    for (int j = 1; j <= N; j++) {
        double ans = 0;
        int imax = A * j + 0.0001;
        if (imax <= UP) {
            for (int i = 1; i <= imax; i++) {
                ans += (double)M[i] * M[j] / (j - i);
            }
        } else {
            ans = ps[imax] * M[j] / (j - ((imax+1)>>1));
        }
        printf("%.6lf\n", ans);
    }

    return 0;
}
