// https://www.luogu.org/problemnew/show/P1667
// 数列

#include <bits/stdc++.h>
using namespace std;

const int MAXN = 100010;
int N;
int64_t A[MAXN], sorted[MAXN];

int main() {
    scanf("%d", &N);
    for (int i = 1; i <= N; i++) {
        scanf("%lld", &A[i]);
        A[i] += A[i-1];
        if (A[i] <= 0) {
            printf("-1\n");
            return 0;
        }
        sorted[i] = A[i];
    }
    sort(sorted, sorted+N+1);
    int64_t *endp = unique(sorted, sorted+N+1);
    if (endp - sorted < N+1) {
        printf("-1\n");
        return 0;
    }

    for (int i = 1; i <= N; i++) {
        A[i] = lower_bound(sorted, sorted+N+1, A[i]) - sorted;
    }
    int ans = 0;
    int i = 1;
    while (i <= N) {
        while (A[i] != i) {
            swap(A[i], A[A[i]]);
            ans++;
        }
        i++;
    }
    printf("%d", ans);
    return 0;
}
