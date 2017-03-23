// https://www.luogu.org/problem/show?pid=2115
// [USACO14MAR]破坏Sabotage

#include <bits/stdc++.h>
using namespace std;

const int MAXN = 100010;
int N;
int ps[2*MAXN], q[MAXN];

double slope(int x1, int x2) {
    return ((double)ps[x2] - ps[x1])/(x2-x1);
}

double minSlope(int t, int i, int j) {
    if (j - i <= 5) {
        double ret = 1e30;
        for (int k = i; k <= j; k++) {
            ret = min(ret, slope(t, q[k]));
        }
        return ret;
    }

    int lm = i + (j-i)/3;
    int rm = i + 2*(j-i)/3;
    if (slope(t, q[lm]) <= slope(t, q[rm])) {
        return minSlope(t, i, rm);
    } else {
        return minSlope(t, lm, j);
    }
}

int slopeCmp(int x1, int x2, int x3, int x4) {
    return (ps[x2]-ps[x1])*(x4-x3) - (ps[x4]-ps[x3])*(x2-x1);
}

int main() {
    scanf("%d", &N);
    for (int i = 1; i <= N; i++) {
        scanf("%d", &ps[i]);
        ps[i+N] = ps[i];
    }

    for (int i = 1; i <= 2*N; i++) {
        ps[i] += ps[i-1];
    }

    double ret = 1e30;
    int i = 0, j = 0;
    for (int k = N - 2; k >= 1; k--) {
        int t = k + N;
        while (j > i+1 && slopeCmp(k+1, q[j-1], q[j-1], q[j-2]) <= 0) j--;
        q[j++] = k+1;
        ret = min(ret, minSlope(t, i, j-1));
    }

    printf("%.3lf\n", ret);
    return 0;
}
