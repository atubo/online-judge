// https://www.luogu.org/problem/show?pid=1290
// 欧几里德的游戏
#include <cassert>
#include <inttypes.h>
#include <iostream>
using namespace std;

bool solve(int64_t n, int64_t m) {
    assert(n > 0 && m > 0);
    if (n < m) swap(n, m);
    if (n % m == 0) return true;
    bool g = solve(n % m, m);
    if (!g) return true;
    return (n - n % m == m ? false : true);
}

int main() {
    int C;
    cin >> C;
    while (C--) {
        int64_t n, m;
        cin >> n >> m;
        bool ans = solve(n, m);
        cout << (ans ? "Stan" : "Ollie") << " wins" << endl;
    }
    return 0;
}
