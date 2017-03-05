// https://www.luogu.org/problem/show?pid=2759
// 奇怪的函数

#include <bits/stdc++.h>
using namespace std;

int solve(int64_t n) {
    if (n == 1) return 1;

    int lo = 1, hi = INT_MAX;
    while (lo < hi - 1) {
        int mid = ((int64_t)lo + hi) / 2;
        if (log10((double)mid) * mid < n-1) lo = mid;
        else hi = mid;
    }
    return hi;
}

int main() {
    int64_t n;
    cin >> n;

    cout << solve(n) << endl;
    return 0;
}
