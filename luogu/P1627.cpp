// https://www.luogu.org/problem/show?pid=1627
// 中位数
#include <bits/stdc++.h>
using namespace std;

int N, B;
const int SHIFT = 100000;
int A[100010], C[200010];

int main() {
    scanf("%d %d", &N, &B);
    int k = 0;
    for (int i = 1; i <= N; i++) {
        int a;
        scanf("%d", &a);
        if (a == B) k = i;
        else if (a > B) A[i] = 1;
        else A[i] = -1;
        A[i] += A[i-1];
    }

    C[SHIFT] = 1;
    for (int i = 1; i < k; i++) {
        C[A[i]+SHIFT]++;
    }
    int64_t ans = 0;
    for (int i = k; i <= N; i++) {
        ans += C[A[i]+SHIFT];
    }

    printf("%lld\n", ans);

    return 0;
}
