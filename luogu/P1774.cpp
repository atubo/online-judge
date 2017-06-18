// https://www.luogu.org/problem/show?pid=1774
// 最接近神的人_NOI导刊2010提高（02）

#include <bits/stdc++.h>
using namespace std;

const int MAXN = 500010;
int N;
int A[MAXN], B[MAXN];

int64_t merge(int p, int r) {
    if (r - p <= 1) return 0;
    int q = (p + r) / 2;
    int64_t ret = merge(p, q);
    ret += merge(q, r);

    int x = p, y = q, z = p;
    while (x < q && y < r) {
        if (A[x] <= A[y]) {
            B[z++] = A[x++];
        } else {
            ret += q - x;
            B[z++] = A[y++];
        }
    }
    while (x < q) {
        B[z++] = A[x++];
    }
    while (y < r) {
        B[z++] = A[y++];
    }

    for (int i = p; i < r; i++) {
        A[i] = B[i];
    }
    return ret;
}



int main() {
    scanf("%d", &N);
    for (int i = 0; i < N; i++) {
        scanf("%d", &A[i]);
    }

    int64_t ret = merge(0, N);
    printf("%lld\n", ret);
    return 0;
}
