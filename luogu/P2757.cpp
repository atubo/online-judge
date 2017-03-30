// https://www.luogu.org/problem/show?pid=2757
// 导弹的召唤(数据加强)

#include <bits/stdc++.h>
using namespace std;

const int MAXN = 300010;
int N;
int A[MAXN], B[MAXN];

void init() {
    B[0] = 0;
    for (int i = 1; i <= N; i++) {
        B[i] = INT_MAX;
    }
}

int lis1() {
    init();

    int ret = 0;
    for (int i = 1; i <= N; i++) {
        int *p = upper_bound(B, B+N+1, A[i]);
        *p = A[i];
        ret = max(ret, int(p - B));
    }
    return ret;
}

int lis2() {
    init();

    int ret = 0;
    for (int i = 1; i <= N; i++) {
        int *p = lower_bound(B, B+N+1, A[i]);
        *p = A[i];
        ret = max(ret, int(p - B));
    }
    return ret;
}


int main() {
    while (scanf("%d", &A[N+1]) == 1) {N++;}
    int b = lis2();
    reverse(A+1, A+N+1);
    int a = lis1();
    printf("%d\n%d\n", a, b);
    return 0;
}
