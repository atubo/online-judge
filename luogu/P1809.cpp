// https://www.luogu.org/problem/show?pid=1809
// 过河问题_NOI导刊2011提高（01）

#include <bits/stdc++.h>
using namespace std;

int N;
int64_t A[100010];

int main() {
    scanf("%d", &N);
    for (int i = 1; i <= N; i++) {
        scanf("%lld", &A[i]);
    }
    sort(A+1, A+N+1);

    if (N <= 2) {
        printf("%lld\n", A[N]);
        return 0;
    }

    int p = upper_bound(A+1, A+N+1, 2*A[2]-A[1]) - A;

    int64_t ret = 0;
    int i;
    for (i = N; i >= p+1; i -= 2) {
        ret += A[1] + A[2] * 2 + A[i];
    }

    for (; i >= 2; i--) {
        ret += A[1] + A[i];
    }
    ret -= A[1];

    printf("%lld\n", ret);
    return 0;
}
