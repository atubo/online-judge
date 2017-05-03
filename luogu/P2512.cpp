// https://www.luogu.org/problem/show?pid=2512
// [HAOI2008]糖果传递

#include <bits/stdc++.h>
using namespace std;

const int MAXN = 1000010;
int A[MAXN], D[MAXN];

int main() {
    int N;
    scanf("%d", &N);
    int64_t s = 0;
    for (int i = 1; i <= N; i++) {
        scanf("%d", &A[i]);
        s += A[i];
    }
    s = s / N;
    for (int i = 1; i <= N; i++) {
        D[i] = D[i-1] + (s - A[i]);
    }
    sort(D+1, D+N+1);
    int mid = D[N/2];

    int64_t ret = 0;
    for (int i = 1; i <= N; i++) {
        ret += abs(mid - D[i]);
    }
    printf("%lld\n", ret);
    return 0;
}
