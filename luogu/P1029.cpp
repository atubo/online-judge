// https://www.luogu.org/problem/show?pid=1029
// 最大公约数和最小公倍数问题

#include <bits/stdc++.h>
using namespace std;

int main() {
    int x0, y0;
    cin >> x0 >> y0;
    if (y0 % x0 != 0) {
        cout << 0 << endl;
        return 0;
    }
    int x = y0/x0;
    int ans = 0;
    for (int i = 2; i * i <= x; i++) {
        if (x % i == 0) {
            ans++;
            while (x % i == 0) {
                x /= i;
            }
        }
    }
    if (x > 1) ans++;
    cout << (1 << ans) << endl;
    return 0;
}
