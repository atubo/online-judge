// https://www.luogu.org/problemnew/show/P2666
// Bessie的秘密牧场

#include <bits/stdc++.h>
using namespace std;

const int MAXN = 10010;
int N;
int cnt[MAXN];

int main() {
    scanf("%d", &N);
    for (int64_t i = 0; i*i <= N; i++) {
        for (int64_t j = 0; j*j <= N; j++) {
            if (i*i + j*j <= N) cnt[i*i+j*j]++;
        }
    }

    int64_t ans = 0;
    for (int i = 0; i <= N; i++) {
        ans += 1LL * cnt[i] * cnt[N-i];
    }
    printf("%ld\n", ans);

    return 0;
}
