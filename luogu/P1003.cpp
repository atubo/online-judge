// https://www.luogu.org/problemnew/show/P1003
// 铺地毯

#include <bits/stdc++.h>
using namespace std;

const int MAXN = 10010;
int N;
struct Carpet {
    int a, b, g, k;
} C[MAXN];

int main() {
    scanf("%d", &N);
    for (int i = 1; i <= N; i++) {
        int a, b, g, k;
        scanf("%d%d%d%d", &a, &b, &g, &k);
        C[i] = {a, b, g, k};
    }
    int x, y;
    scanf("%d%d", &x, &y);
    int ans = -1;
    for (int i = 1; i <= N; i++) {
        int a = C[i].a, b = C[i].b, g = C[i].g, k = C[i].k;
        if (a <= x && x <= a+g && b <= y && y <= b+k) ans = i;
    }
    printf("%d\n", ans);

    return 0;
}
