// https://www.luogu.org/problem/show?pid=1542
// 包裹快递

#include <bits/stdc++.h>
using namespace std;

int N;
const int MAXN = 200010;
long double X[MAXN], Y[MAXN], S[MAXN];

bool feasible(long double v) {
    long double t = 0;
    for (int i = 0; i < N; i++) {
        long double tn = t + S[i]/v;
        if (tn > Y[i]) return false;
        t = max(tn, X[i]);
    }
    return true;
}


int main() {
    scanf("%d", &N);
    long double hi = 0;
    for (int i = 0; i < N; i++) {
        scanf("%Lf%Lf%Lf", &X[i], &Y[i], &S[i]);
        hi = max(hi, S[i]/(X[i] - (i > 0 ? X[i-1] : 0)));
    }
    long double lo = 0;
    while (lo < hi - 0.000001) {
        long double mid = (lo + hi) / 2;
        if (feasible(mid)) hi = mid;
        else lo = mid;
    }
    printf("%.2Lf\n", hi);
    return 0;
}
