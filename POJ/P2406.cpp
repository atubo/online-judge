// http://poj.org/problem?id=2406
// Power Strings

#include <algorithm>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <string>
#include <vector>
using namespace std;

const int MAXN = 1e6+10;
char s[MAXN];
int z[MAXN];

void z_function(int n) {
    for (int i = 1, l = 0, r = 0; i < n; ++i) {
        if (i <= r)
            z[i] = min (r - i + 1, z[i - l]);
        while (i + z[i] < n && s[z[i]] == s[i + z[i]])
            ++z[i];
        if (i + z[i] - 1 > r)
            l = i, r = i + z[i] - 1;
    }
}

int main() {
    while (true) {
        scanf("%s", s);
        const int n = strlen(s);
        memset(z, 0, n*sizeof(int));
        if (n == 1 && s[0] == '.') break;
        z_function(n);
        for (int k = 1; k <= n; k++) {
            if (n % k != 0) continue;
            const int m = n / k;
            bool ok = true;
            for (int j = 1; j < m; j++) {
                if (z[j*k] < k) {
                    ok = false;
                    break;
                }
            }
            if (ok) {
                printf("%d\n", m);
                break;
            }
        }
    }
    return 0;
}
