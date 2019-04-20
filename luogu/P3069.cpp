// https://www.luogu.org/problemnew/show/P3069
// [USACO13JAN]牛的阵容Cow Lineup

#include <bits/stdc++.h>
using namespace std;

const int MAXN = 100010;
int N, K;
int A[MAXN], B[MAXN], C[MAXN];

int main() {
    scanf("%d%d", &N, &K);
    for (int i = 0; i < N; i++) {
        scanf("%d", &A[i]);
        B[i] = A[i];
    }
    sort(B, B+N);
    const int m = unique(B, B+N) - B;
    for (int i = 0; i < N; i++) {
        A[i] = lower_bound(B, B+m, A[i]) - B;
    }

    memset(B, 0, m*sizeof(int));
    int breed_cnt = 0;
    int p = 0, q = 0, ans = 0;
    while (true) {
        while (p < N && breed_cnt <= K+1) {
            int x = A[p++];
            B[x]++;
            if (B[x] == 1) breed_cnt++;
            ans = max(ans, B[x]);
        }
        if (p == N) break;
        while (breed_cnt > K+1) {
            int x = A[q++];
            B[x]--;
            if (B[x] == 0) breed_cnt--;
        }
    }
    printf("%d\n", ans);

    return 0;
}
