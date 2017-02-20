// https://www.luogu.org/problem/show?pid=1057
// 传球游戏
#include <bits/stdc++.h>
using namespace std;

int64_t choose(int m, int x) {
    int64_t ans = 1;
    for (int i = 1; i <= x; i++) {
        ans = ans * (m - x + i) / i;
    }
    return ans;
}

int main() {
    int n, m;
    cin >> n >> m;
    int64_t ans = 0;
    for (int k = -m/n; k <= m/n; k++) {
        if ((m + k*n) & 1) continue;
        int x = (m + k*n)/2;
        ans += choose(m, x);
    }
    cout << ans << endl;
    return 0;
}
