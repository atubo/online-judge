// https://www.luogu.org/problemnew/show/P1754
// 球迷购票问题

#include <bits/stdc++.h>
using namespace std;

int64_t C[41][41];

void init() {
    C[0][0] = 1;
    for (int i = 1; i <= 40; i++) {
        C[i][0] = C[i-1][0];
        for (int j = 1; j <= i; j++) {
            C[i][j] = C[i-1][j] + C[i-1][j-1];
        }
    }
}

int main() {
    init();
    int n;
    cin >> n;
    printf("%ld", C[2*n][n]-C[2*n][n+1]);
    return 0;
}
