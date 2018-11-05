// https://www.luogu.org/problemnew/show/P1378
// 油滴扩展

#include <bits/stdc++.h>
using namespace std;

const int MAXN = 8;
const double PI = 3.1415926;
int N;
int X1, Y1, X2, Y2;
int X[MAXN], Y[MAXN];
double R[MAXN];

double dist(double x, double y) {
    return sqrt(x*x + y*y);
}

double findRadius(const vector<int> &order, int idx) {
    int x = X[order[idx]], y = Y[order[idx]];
    double r = min(min(x-X1, X2-x), min(y-Y1, Y2-y));
    for (int j = 0; j < idx; j++) {
        double d = dist(x-X[order[j]], y-Y[order[j]]);
        if (d <= R[j]) {
            r = 0;
            break;
        }
        r = min(r, d-R[j]);
    }
    return r;
}

int solve(const vector<int> &order) {
    double ans = abs(X1-X2) * abs(Y1-Y2);
    for (int i = 0; i < (int)order.size(); i++) {
        double r = findRadius(order, i);
        ans -= PI * r * r;
        R[i] = r;
    }
    return int(ans + 0.5);
}

int main() {
    scanf("%d", &N);
    scanf("%d%d%d%d", &X1, &Y1, &X2, &Y2);
    if (X1 > X2) swap(X1, X2);
    if (Y1 > Y2) swap(Y1, Y2);
    for (int i = 0; i < N; i++) {
        scanf("%d%d", &X[i], &Y[i]);
    }
    vector<int> order(N);
    iota(order.begin(), order.end(), 0);

    int ans = INT_MAX;
    do {
        ans = min(ans, solve(order));
    } while (next_permutation(order.begin(), order.end()));
    printf("%d", ans);

    return 0;
}
