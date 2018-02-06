// https://www.luogu.org/problemnew/show/P1291
// [SHOI2002]百事世界杯之旅

#include <bits/stdc++.h>
using namespace std;

class Fraction {
private:
    int64_t p, q;

    static int64_t gcd(int64_t p, int64_t q) {
        if (q == 0) return p;
        return gcd(q, p%q);
    }

    void canonicalize() {
        int64_t g = gcd(p, q);
        p /= g;
        q /= g;
    }
public:
    Fraction(int64_t p_ = 0, int64_t q_ = 1): p(p_), q(q_) {
        canonicalize();
    }

    Fraction& operator += (const Fraction &other) {
        int64_t p2 = other.p, q2 = other.q;
        p = p * q2 + p2 * q;
        q = q * q2;
        canonicalize();
        return *this;
    }

    friend Fraction operator + (const Fraction &a, const Fraction &b) {
        Fraction ret(a);
        ret += b;
        return ret;
    }

    string toString() const {
        if (q == 1) return to_string(p);
        int nq = to_string(q).length();
        int64_t x = p/q;
        int nx = to_string(x).length();
        string ret = string(nx, ' ') + to_string(p%q) + '\n';
        ret += to_string(x) + string(nq, '-') + '\n';
        ret += string(nx, ' ') + to_string(q);
        return ret;
    }
};

int main() {
    int n;
    scanf("%d", &n);
    Fraction ret;
    for (int m = 1; m <= n; m++) {
        ret += Fraction(n, m);
    }
    cout << ret.toString() << endl;
    return 0;
}
