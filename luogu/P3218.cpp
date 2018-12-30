// https://www.luogu.org/problemnew/show/P3218
// [HNOI2011]赛车游戏

#include <bits/stdc++.h>
using namespace std;

const int MAXR = 10010;
int T;
double A, B, VMAX, F;
int R;
double X[MAXR], Y[MAXR];
double S[MAXR], D[MAXR];

bool feasible(double v) {
    double f = F;
    for (int i = 0; i < R; i++) {
        double c = max(0.0, A*v + B*S[i]);
        f -= c * D[i];
        if (f < 0) return false;
    }
    return true;
}

bool check(double mid) {
    double f = F;
    for (int i = 0; i < R; i++) {
        double v = min(VMAX, max(mid, -B*S[i]/A));
        double c = max(0.0, A*v + B*S[i]);
        f -= c * D[i];
        if (f < 0) return false;
    }
    return true;
}

double calcTime(double v) {
    double res = 0;
    for (int i = 0; i < R;  i++) {
        double vi = min(VMAX, max(v, -B*S[i]/A));
        res += D[i]/vi;
    }
    return res;
}

double solve() {
    scanf("%lf%lf%lf%lf", &A, &B, &VMAX, &F);
    scanf("%d", &R);
    for (int i = 0; i < R; i++) {
        scanf("%lf%lf", &X[i], &Y[i]);
        X[i] /= 1000;
        Y[i] /= 1000;
        S[i] = Y[i] / X[i];
        D[i] = sqrt(X[i]*X[i] + Y[i]*Y[i]);
    }

    if (!feasible(0)) return -1;
    if (feasible(VMAX)) return calcTime(VMAX);
    double lo = 0, hi = VMAX;
    const double EPS = 1e-13;
    while (lo < hi-EPS) {
        double mid = (lo + hi)/2;
        if (check(mid)) lo = mid;
        else hi = mid;
    }
    return calcTime(lo);
}

int main() {
    scanf("%d", &T);
    while (T--) {
        double ans = solve();
        if (ans < 0) printf("IMPOSSIBLE\n");
        else printf("%.5f\n", ans);
    }
    return 0;
}
