// https://www.luogu.org/problem/show?pid=1115
// 最大子段和
#include <algorithm>
#include <cstdio>
#include <limits.h>
using namespace std;

int main() {
    int N;
    scanf("%d", &N);
    int minps = 0, ps = 0;
    int ans= INT_MIN;
    int a;
    for (int i = 0; i < N; i++) {
        scanf("%d", &a);
        ps += a;
        ans = max(ans, ps - minps);
        minps = min(minps, ps);
    }
    printf("%d\n", ans);
    return 0;
}
