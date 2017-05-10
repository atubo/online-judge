// https://www.luogu.org/problem/show?pid=1337
// [JSOI]平衡点

#include <bits/stdc++.h>
using namespace std;

const int MAXN = 1005;
double X[MAXN], Y[MAXN], W[MAXN];
int N;

double fx(double x, double y) {
    double ret = 0;
    for (int i = 0; i < N; i++) {
        double dx = X[i] - x;
        double dy = Y[i] - y;
        double d = sqrt(dx*dx + dy*dy);
        ret += W[i] * dx / d;
    }
    return ret;
}

double dfx(double x, double y) {
    double ret = 0;
    for (int i = 0; i < N; i++) {
        double dx = X[i] - x;
        double dy = Y[i] - y;
        double d = sqrt(dx*dx + dy*dy);
        ret += - W[i]/d + W[i]*dx*dx/(d*d*d);
    }
    return ret;
}

double fy(double x, double y) {
    double ret = 0;
    for (int i = 0; i < N; i++) {
        double dx = X[i] - x;
        double dy = Y[i] - y;
        double d = sqrt(dx*dx + dy*dy);
        ret += W[i] * dy / d;
    }
    return ret;
}

double dfy(double x, double y) {
    double ret = 0;
    for (int i = 0; i < N; i++) {
        double dx = X[i] - x;
        double dy = Y[i] - y;
        double d = sqrt(dx*dx + dy*dy);
        ret += - W[i]/d + W[i]*dy*dy/(d*d*d);
    }
    return ret;
}

int main() {
    scanf("%d", &N);
    double sx = 0, sy = 0;
    for (int i = 0; i < N; i++) {
        scanf("%lf%lf%lf", &X[i], &Y[i], &W[i]);
        sx += X[i];
        sy += Y[i];
    }
    double xp = sx/N + 3.1415926/4, yp = sy/N + 2.71828/8;
    double x, y;
    do {
        x = xp;
        y = yp;
        xp = x - 0.2 * fx(x, y)/dfx(x, y);
        yp = y - 0.2 * fy(x, y)/dfy(x, y);
    } while (fabs(x - xp) > 1e-5 || fabs(y - yp) > 1e-5);

    printf("%.3lf %.3lf\n", x, y);
    return 0;
}
