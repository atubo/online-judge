// https://www.luogu.org/problem/show?pid=1025
// 数的划分

#include <bits/stdc++.h>
using namespace std;

int f[210];
int N, K;

int main() {
    scanf("%d %d", &N, &K);
    f[0] = 1;
    for (int k = 1; k <= K; k++) {
        for (int n = N; n >= 1; n--) {
            f[n] = f[n-1];
            for (int j = 2; j <= n/k; j++) {
                f[n] += f[n-1-(j-1)*k];
            }
        }
        f[0] = 0;
    }
    printf("%d\n", f[N]);
    return 0;
}
