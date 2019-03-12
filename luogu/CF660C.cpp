// https://www.luogu.org/problemnew/show/CF660C
// CF660C Hard Process

#include <bits/stdc++.h>
using namespace std;

const int MAXN = 3e5+10;
int N, K;
int A[MAXN];

int main() {
    scanf("%d%d", &N, &K);
    for (int i = 0; i < N; i++) {
        scanf("%d", &A[i]);
    }
    int cnt = 0;
    int p = 0, q = 0;
    int left = N, right = N;
    int ans = 0;
    while (p < N) {
        while (q < N && cnt + (A[q] == 0) <= K) {
            cnt += (A[q] == 0);
            q++;
        }
        if (ans < q - p) {
            ans = q - p;
            left = p;
            right = q;
        }
        if (q == N) break;
        cnt += (A[q] == 0);
        while (cnt > K) {
            cnt -= (A[p] == 0);
            p++;
        }
        q++;
    }
    printf("%d\n", ans);

    for (int i = 0; i < left; i++) {
        printf("%d ", A[i]);
    }
    for (int i = left; i < right; i++) {
        printf("1 ");
    }
    for (int i = right; i < N; i++) {
        printf("%d ", A[i]);
    }

    return 0;
}
