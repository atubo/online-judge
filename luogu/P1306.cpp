// https://www.luogu.org/problem/show?pid=1306
// 斐波那契公约数

#include <bits/stdc++.h>
using namespace std;

int gcd(int a, int b) {
    if (b == 0) return a;
    return gcd(b, a%b);
}

struct Matrix {
    int64_t a, b, c, d;

    Matrix& operator *= (const Matrix &other) {
        int64_t a1 = a, b1 = b, c1 = c, d1 = d;
        int64_t a2 = other.a, b2 = other.b, c2 = other.c, d2 = other.d;

        int64_t MOD = 100000000;
        a = (a1*a2 + b1*c2) % MOD;
        b = (a1*b2 + b1*d2) % MOD;
        c = (c1*a2 + d1*c2) % MOD;
        d = (c1*b2 + d1*d2) % MOD;

        return *this;
    }
};

Matrix power(const Matrix &m, int n) {
    if (n == 1) return m;
    Matrix ret = power(m, n/2);
    ret *= ret;
    if (n & 1) ret *= m;
    return ret;
}

int fibo(int n) {
    Matrix m;
    m.a = m.b = m.c = 1;
    m.d = 0;

    m = power(m, n);
    return m.c;
}

int main() {
    int n, m;
    scanf("%d%d", &n, &m);
    printf("%d\n", fibo(gcd(n, m)));
    return 0;
}
