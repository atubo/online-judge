// https://www.luogu.org/problem/show?pid=1368
// 均分纸牌（加强版）

#include <bits/stdc++.h>
using namespace std;

const int MAXN = 1000010;
int A[MAXN], B[MAXN];
int N;

int main() {
    scanf("%d", &N);
    for (int i = 1; i <= N; i++) {
        scanf("%d", &A[i]);
        A[i] += A[i-1];
    }
    int avg = A[N]/N;
    for (int i = 1; i <= N; i++) {
        B[i] = A[i] - i * avg;
    }
    sort(B+1, B+N+1);
    int k = B[(N+1)/2];
    int64_t ret = 0;
    for (int i = 1; i <= N; i++) {
        ret += abs(B[i] - k);
    }
    printf("%lld\n", ret);
    return 0;
}
