// https://www.luogu.org/problemnew/show/P1943
// LocalMaxima_NOI导刊2009提高（1）

#include <bits/stdc++.h>
using namespace std;

double harmonics(int n) {
    double ans = 0;
    if (n < 1e7) {
        for (int i = 1; i <= n; i++) {
            ans += 1.0/i;
        }
    } else {
        ans = 0.5772156649 + log(n+0.5);
    }
    return ans;
}

int main() {
    int n;
    scanf("%d", &n);
    printf("%.8lf", harmonics(n));
    return 0;
}
