// https://www.luogu.org/problemnew/show/P4552
// [Poetize6] IncDec Sequence

#include <bits/stdc++.h>
using namespace std;

const int MAXN = 100010;
int N;
int64_t A[MAXN];
int64_t buf[MAXN];

int sign(int a, int b) {
    if (a == b) return 0;
    return (a < b ? -1 : 1);
}

int main() {
    scanf("%d", &N);
    for (int i = 0; i < N; i++) {
        scanf("%ld", &A[i]);
    }
    int64_t ans = 0;
    int p = 0, q = 0;
    buf[q++] = A[0];
    for (int i = 1; i < N; i++) {
        if (A[i] == buf[q-1]) continue;
        if (q-p == 1 || sign(buf[p], buf[p+1]) == sign(buf[q-1], A[i])) {
            buf[q++] = A[i];
            ans += abs(buf[q-1] - buf[q-2]);
            continue;
        }
        int64_t old = buf[q-1];
        while (q-p > 1 && sign(buf[p], buf[p+1]) != sign(buf[q-1], A[i])) q--;
        if (buf[q-1] != A[i]) {
            buf[q++] = A[i];
            if (q-p == 2 && sign(buf[p], old) != sign(buf[p], A[i])) {
                ans += abs(buf[q-1] - buf[q-2]);
            }
        }
    }
    printf("%ld\n", ans);
    printf("%ld", abs(buf[q-1] - buf[p]) + 1);

    return 0;
}
