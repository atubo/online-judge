// https://www.luogu.org/problemnew/show/P3048
// [USACO12FEB]牛的IDCow IDs

#include <bits/stdc++.h>
using namespace std;

int N, K;

int64_t binom(int n, int k) {
    int64_t ans = 1;
    for (int i = 1; i <= k; i++) {
        ans = ans * (n-i+1) / i;
    }
    return ans;
}

void solve1(int n, int k, string &s) {
    if (k == 1) {
        for (int i = 0; i < n-1; i++) s.push_back('0');
        s.push_back('1');
        return;
    }
    int m = 0;
    int64_t tot = 0, last = 0;
    while (tot < n) {
        last = tot;
        tot += binom(k-1+m, k-1);
        m++;
    }
    m--;
    solve1(n-last, k-1, s);
    int len = s.length();
    for (int i = 0; i < m-len+k-1; i++) s.push_back('0');
    s.push_back('1');
}

string solve() {
    string ans;
    solve1(N, K, ans);
    reverse(ans.begin(), ans.end());
    return ans;
}

int main() {
    scanf("%d%d", &N, &K);
    auto s = solve();
    printf("%s\n", s.c_str());
    return 0;
}
