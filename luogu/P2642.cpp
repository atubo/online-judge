// https://www.luogu.org/problem/show?pid=2642
// 双子序列最大和

#include <bits/stdc++.h>
using namespace std;

const int MAXN = 1000010;
int64_t ps[MAXN], min1[MAXN], max1[MAXN], min2[MAXN], max2[MAXN];
int N;

int main() {
    scanf("%d", &N);
    for (int i = 1; i <= N; i++) {
        scanf("%lld", &ps[i]);
        ps[i] += ps[i-1];
    }
    max1[0] = INT64_MIN;
    for (int i = 1; i <= N; i++) {
        max1[i] = max(max1[i-1], ps[i] - min1[i-1]);
        min1[i] = min(ps[i], min1[i-1]);
    }
    max2[N+1] = INT64_MIN;
    for (int i = N; i >= 1; i--) {
        max2[i] = max(max2[i+1], ps[N] - ps[i-1] - min2[i+1]);
        min2[i] = min(ps[N] - ps[i-1], min2[i+1]);
    }

    int64_t ret = INT64_MIN;
    for (int i = 1; i+2 <= N; i++) {
        ret = max(ret, max1[i] + max2[i+2]);
    }
    printf("%lld\n", ret);
    return 0;
}
