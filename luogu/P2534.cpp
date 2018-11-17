// https://www.luogu.org/problemnew/show/P2534
// [AHOI2012]铁盘整理

#include <bits/stdc++.h>
using namespace std;

const int MAXN = 52;
int N;
int R[MAXN], order[MAXN], target[MAXN];

int DMAX;

int cost() {
    int ret = 0;
    for (int i = 1; i < N; i++) {
        if (abs(R[i]-R[i-1]) != 1) ret++;
    }
    return ret;
}

bool check() {
    for (int i = 0; i < N; i++) {
        if (R[i] != target[i]) return false;
    }
    return true;
}

bool dfs(int d) {
    if (d > DMAX) return false;
    if (check()) return true;
    int f = d + cost();
    if (f > DMAX) return false;
    for (int i = 1; i < N; i++) {
        reverse(R, R+i+1);
        if (dfs(d+1)) return true;
        reverse(R, R+i+1);
    }
    return false;
}

int main() {
    scanf("%d", &N);
    for (int i = 0; i < N; i++) {
        scanf("%d", &R[i]);
        order[i] = R[i];
    }
    sort(order, order+N);
    for (int i = 0; i < N; i++) {
        R[i] = lower_bound(order, order+N, R[i]) - order;
        target[i] = i;
    }
    for (DMAX = 1; DMAX <= 2*(N-1); DMAX++) {
        if (dfs(0)) {
            printf("%d", DMAX);
            break;
        }
    }
    return 0;
}
