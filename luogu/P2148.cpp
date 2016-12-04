// https://www.luogu.org/problem/show?pid=2148
#include <inttypes.h>
#include <cassert>
#include <cstdio>
#include <iostream>
#include <vector>
using namespace std;

int grundy(int64_t i, int64_t j) {
    for (int k = 1; k < 33; k++) {
        int64_t n = (1LL << k);
        if ((i-1) % n < n/2 && (j-1) % n < n/2) return k-1;
    }
    assert(0);
    return 32;
}

int solve() {
    int N;
    scanf("%d", &N);
    int ret = 0;
    int a, b;
    for (int i = 0; i < N/2; i++) {
        scanf("%d %d", &a, &b);
        ret ^= grundy(a, b);
    }
    cout << (ret != 0 ? "YES" : "NO") << endl;
}

int main() {
    int T;
    scanf("%d", &T);
    while (T--) {
        solve();
    }
    return 0;
}
