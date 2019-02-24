// https://www.luogu.org/problemnew/show/P3933
// Chtholly Nota Seniorious

#include <bits/stdc++.h>
using namespace std;

const int MAXN = 2048;
int N, M;
int A[MAXN][MAXN];
int mx, mn;
int rt[MAXN];

bool check1(int mid) {
    memset(rt, 0x7F, sizeof(rt));
    for (int i = 0; i < N; i++) {
        int right = (i == 0 ? M : rt[i-1]);
        for (int j = 0; j < right; j++) {
            if (A[i][j] < mx - mid) {
               rt[i] = j;
               break;
            }
        }
        rt[i] = min(rt[i], right);
    }
    for (int i = 0; i < N; i++) {
        for (int j = rt[i]; j < M; j++) {
            if (A[i][j] > mn + mid) return false;
        }
    }
    return true;
}

void reflect_x() {
    for (int j = 0; j < M; j++) {
        for (int i = 0; i < N/2; i++) {
            swap(A[i][j], A[N-1-i][j]);
        }
    }
}

void rotate() {
    for (int i = 0; i < N/2; i++) {
        for (int j = 0; j < M; j++) {
            swap(A[i][j], A[N-1-i][M-1-j]);
        }
    }
    if (N & 1) {
        for (int j = 0; j < M/2; j++) {
            swap(A[N/2][j], A[N/2][M-1-j]);
        }
    }
}
        

bool check(int mid) {
    if (check1(mid)) return true;
    rotate();
    if (check1(mid)) return true;
    reflect_x();
    if (check1(mid)) return true;
    rotate();
    return check1(mid);
}

int main() {
    scanf("%d%d", &N, &M);
    mn = INT_MAX;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            scanf("%d", &A[i][j]);
            mx = max(mx, A[i][j]);
            mn = min(mn, A[i][j]);
        }
    }
    int lo = -1, hi = mx - mn;
    while (lo < hi-1) {
        int mid = (lo + hi) / 2;
        if (check(mid)) hi = mid;
        else lo = mid;
    }
    printf("%d", hi);
    return 0;
}
