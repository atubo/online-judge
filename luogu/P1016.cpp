// https://www.luogu.org/problem/show?pid=1016
// 旅行家的预算

#include <bits/stdc++.h>
using namespace std;

const int MAXN = 1010;
double P[MAXN], D[MAXN], R[MAXN];
double D1, C, D2;
int N;

bool feasible() {
    for (int i = 1; i < N; i++) {
        if (D[i+1] - D[i] > C * D2) return false;
    }
    return true;
}

void update(int b, int e, double d) {
    for (int i = b; i <= e; i++) {
        R[i] -= d;
    }
}

int main() {
    scanf("%lf%lf%lf%lf%d", &D1, &C, &D2, &P[1], &N);
    N = N + 2;
    P[N] = 0;
    D[N] = D1;
    for (int i = 2; i <= N-1; i++) {
        scanf("%lf%lf", &D[i], &P[i]);
    }

    if (!feasible()) {
        printf("No Solution");
        return 0;
    }

    int L = 1;
    R[1] = C;
    double ret = 0;
    for (int i = 2; i <= N; i++) {
        double d = (D[i] - D[i-1]) / D2;
        while (d > 0) {
            double minp = 1e40;
            int pos1 = -1;
            for (int j = i-1; j >= L; j--) {
                if (P[j] < minp) {
                    minp = P[j];
                    pos1 = j;
                }
            }
            double minr = 1e40;
            int pos2 = -1;
            for (int j = i-1; j >= pos1; j--) {
                if (R[j] < minr) {
                    minr = R[j];
                    pos2 = j;
                }
            }
            if (minr < d) {
                d = d - minr;
                L = pos2 + 1;
                ret += P[pos1] * minr;
                update(L, i-1, minr);
            } else {
                ret += P[pos1] * d;
                update(pos1, i-1, d);
                d = 0;
            }
        }
        R[i] = C;
    }
    printf("%.2lf\n", ret);
    return 0;
}
