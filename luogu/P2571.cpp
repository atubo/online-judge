// https://www.luogu.org/problemnew/show/P2571
// [SCOI2010]传送带

#include <bits/stdc++.h>
using namespace std;

const double EPS = 1e-6;

int Ax, Ay, Bx, By;
int Cx, Cy, Dx, Dy;
int P, Q, R;

double dist(double x1, double y1, double x2, double y2) {
    return sqrt((x2-x1)*(x2-x1) + (y2-y1)*(y2-y1));
}

double solve2(double x, double y) {
    double x1 = Cx, y1 = Cy, x2 = Dx, y2 = Dy;
    while (fabs(x1-x2) > EPS || fabs(y1-y2) > EPS) {
        double xp = x1 + 1.0/3 * (x2 - x1);
        double yp = y1 + 1.0/3 * (y2 - y1);
        double xq = x1 + 2.0/3 * (x2 - x1);
        double yq = y1 + 2.0/3 * (y2 - y1);
        double dp = dist(x, y, xp, yp) / R + dist(Dx, Dy, xp, yp) / Q;
        double dq = dist(x, y, xq, yq) / R + dist(Dx, Dy, xq, yq) / Q;
        if (dp <= dq) {
            x2 = xq;
            y2 = yq;
        } else {
            x1 = xp;
            y1 = yp;
        }
    }
    double xc = (x1 + x2) / 2;
    double yc = (y1 + y2) / 2;
    return dist(x, y, xc, yc) / R + dist(Dx, Dy, xc, yc) / Q;
}

double solve1() {
    double x1 = Ax, y1 = Ay, x2 = Bx, y2 = By;
    while (fabs(x1-x2) > EPS || fabs(y1-y2) > EPS) {
        double xp = x1 + 1.0/3 * (x2 - x1);
        double yp = y1 + 1.0/3 * (y2 - y1);
        double xq = x1 + 2.0/3 * (x2 - x1);
        double yq = y1 + 2.0/3 * (y2 - y1);
        double dp = solve2(xp, yp) + dist(Ax, Ay, xp, yp) / P;
        double dq = solve2(xq, yq) + dist(Ax, Ay, xq, yq) / P;
        if (dp <= dq) {
            x2 = xq;
            y2 = yq;
        } else {
            x1 = xp;
            y1 = yp;
        }
    }
    double xc = (x1 + x2) / 2;
    double yc = (y1 + y2) / 2;
    return solve2(xc, yc) + dist(Ax, Ay, xc, yc) / P;
}

int main() {
    scanf("%d%d%d%d", &Ax, &Ay, &Bx, &By);
    scanf("%d%d%d%d", &Cx, &Cy, &Dx, &Dy);
    scanf("%d%d%d", &P, &Q, &R);
    double x = solve1();
    printf("%.2lf\n", x);
    return 0;
}
