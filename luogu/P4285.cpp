// https://www.luogu.org/problemnew/show/P4285
// [SHOI2008]汉诺塔

#include <bits/stdc++.h>
using namespace std;

int g[31][3];
int64_t f[31][3];

int main() {
    int n;
    scanf("%d", &n);
    g[1][0] = g[1][1] = g[1][2] = -1;
    for (int i = 0; i < 6; i++) {
        char s[5];
        scanf("%s", s);
        int a = s[0]-'A', b = s[1]-'A';
        if (g[1][a] == -1) g[1][a] = b;
    }
    f[1][0] = f[1][1] = f[1][2] = 1;
    for (int j = 2; j <= n; j++) {
        for (int i = 0; i < 3; i++) {
            int a = g[j-1][i], b = 3-i-a;
            if (g[j-1][a] == b) {
                f[j][i] = f[j-1][i] + 1 + f[j-1][a];
                g[j][i] = b;
            } else {
                f[j][i] = 2LL * (f[j-1][i] + 1) + f[j-1][a];
                g[j][i] = a;
            }
        }
    }

    printf("%ld\n", f[n][0]);

    return 0;
}
