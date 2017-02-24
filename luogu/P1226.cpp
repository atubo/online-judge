// https://www.luogu.org/problem/show?pid=1226
// 取余运算||快速幂

#include <bits/stdc++.h>
using namespace std;

int64_t k;

int64_t pwr(int64_t b, int64_t p) {
    b = (b % k);
    if (p == 0) return 1%k;
    if (p == 1) return b;
    int64_t x = pwr(b, p/2);
    int64_t ret = (x * x) % k;
    if (p & 1) ret = (ret * b) % k;
    return ret;
}

int main() {
    int64_t b, p;
    cin >> b >> p >> k;
    cout << b << "^" << p << " mod " << k << "=";
    if (b < 0) {
        cout << (p % 2 == 0 ? pwr(-b, p) : -pwr(-b, p)) << endl;
    } else {
        cout << pwr(b, p) << endl;
    }
    return 0;
}
