// https://www.luogu.org/problemnew/show/P2587
// [ZJOI2008]泡泡堂

#include <bits/stdc++.h>
using namespace std;

const int MAXN = 100010;
int N;
int A[MAXN], B[MAXN];

int solve(int *x, int *y) {
    int b1 = 0, b2 = 0, e1 = N-1, e2 = N-1;
    int ret = 0;
    while (b1 <= e1) {
        if (x[b1] > y[b2]) {
            ret += 2;
            b1++;
            b2++;
            continue;
        }
        if (x[e1] > y[e2]) {
            ret += 2;
            e1--;
            e2--;
            continue;
        }
        ret += (x[e1] == y[b2]);
        e1--;
        b2++;
    }
    return ret;
}

int main() {
    scanf("%d", &N);
    for (int i = 0; i < N; i++) {
        scanf("%d", &A[i]);
    }
    for (int i = 0; i < N; i++) {
        scanf("%d", &B[i]);
    }
    sort(A, A+N, greater<int>());
    sort(B, B+N, greater<int>());
    int a= solve(A, B), b = solve(B, A);
    printf("%d %d\n", a, 2*N-b);
    return 0;
}
