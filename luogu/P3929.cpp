// https://www.luogu.org/problemnew/show/P3929
// SAC E#1 - 一道神题 Sequence1

#include <bits/stdc++.h>
using namespace std;

const int MAXN = 100010;
int N;
int A[MAXN], B[MAXN];

int sgn(int x) {
    if (x > 0) return 1;
    if (x < 0) return -1;
    return 0;
}

bool wiggle() {
    int s = 1;
    int cnt = 0;
    bool consec = false;
    for (int i = 0; i < N-1; i++) {
        int x = sgn(A[i+1] - A[i]);
        B[i] = (x * s < 0);
        s = -s;
        cnt += B[i];
        if (i > 1 && (B[i]*B[i-1] == 1)) consec = true;
    }
    return cnt <= 1 || (cnt == 2 && consec);
}

bool solve() {
    if (wiggle()) return true;
    for (int i = 0; i < N; i++) A[i] = -A[i];
    return wiggle();
}

int main() {
    while (scanf("%d", &N) != EOF) {
        for (int i = 0; i < N; i++) {
            scanf("%d", &A[i]);
        }
        bool ans = solve();
        printf(ans ? "Yes\n" : "No\n");
    }
    return 0;
}
