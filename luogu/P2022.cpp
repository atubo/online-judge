// https://www.luogu.org/problem/show?pid=2022
// 有趣的数

#include <bits/stdc++.h>
using namespace std;

int main() {
    int K, M;
    cin >> K >> M;
    int64_t d = 1;
    while (K >= 10 * d) d *= 10;
    int64_t cnt = 0;
    for (int i = d, j = 1; i > 0; i /= 10) {
        cnt += K/j - i + 1;
        j *= 10;
    }

    if (cnt > M - 1) {
        cout << 0 << endl;
        return 0;
    }
    int64_t k = K;
    while (true) {
        k *= 10;
        d *= 10;
        if (cnt + k - d > M - 1) break;
        cnt += k - d;
    }
    cout << d + M - cnt - 1 << endl;
    return 0;
}
