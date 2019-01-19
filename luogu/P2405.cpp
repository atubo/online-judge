// https://www.luogu.org/problemnew/show/P2405
// non天平

#include <bits/stdc++.h>
using namespace std;

class BigInt {
    // split every 9 digits
    // LSD in the first split, and so on
    static const int SPLIT_LEN = 9;
    static const int SPLIT_OVERFLOW = 1000000000;
private:
    vector<int> splits;

    static BigInt mul(const BigInt& a, const BigInt& b) {
        const int n = a.splits.size();
        const int m = b.splits.size();
        vector<int64_t> h(n+m+10);
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                h[i+j] += 1LL * a.splits[i] * b.splits[j];
                h[i+j+1] +=  h[i+j] / SPLIT_OVERFLOW;
                h[i+j] %= SPLIT_OVERFLOW;
            }
        }
        for (int i = 0; i < n+m+9; i++) {
            h[i+1] += h[i]/SPLIT_OVERFLOW;
            h[i] %= SPLIT_OVERFLOW;
        }

        BigInt c;
        c.splits.resize(n+m+10);
        for (int i = 0; i < n+m+10; i++) {
            c.splits[i] = h[i];
        }
        c.canonicalize();
        return c;
    }

    void canonicalize() {
        const int N = splits.size();
        for (int i = N-1; i > 0; i--) {
            if (splits[i] == 0) splits.pop_back();
            else break;
        }
    }

public:
    BigInt() {
        splits.resize(1, 0);
    }

    // x should be less than SPLIT_OVERFLOW
    BigInt(int x) {
        splits.push_back(x);
    }

    BigInt(const string& s) {
        const int n = s.length();
        int imax = (n + SPLIT_LEN - 1) / SPLIT_LEN;
        splits.resize(imax);
        for (int i = 0; i < imax; i++) {
            int start = max(0, n - (i+1)*SPLIT_LEN);
            int end   = n - i*SPLIT_LEN;
            splits[i] = 0;
            for (int j = start; j < end; j++) {
                splits[i] = splits[i] * 10 + s[j] - '0';
            }
        }
        canonicalize();
    }

    void swap(BigInt& other) {
        splits.swap(other.splits);
    }

    string toString() const {
        stringstream ss;
        ss << splits.back();
        for (int i = (int)splits.size()-2; i >= 0; i--) {
            ss.width(SPLIT_LEN);
            ss.fill('0');
            ss << splits[i];
        }
        string ret = ss.str();
        return ret;
    }

    friend BigInt operator * (const BigInt& a, const BigInt& b) {
        if (a < b) return BigInt::mul(b, a);
        else return BigInt::mul(a, b);
    }


    friend BigInt operator % (const BigInt& a, const BigInt& b) {
        vector<BigInt> dbls;
        dbls.push_back(b);
        while (dbls.back() < a) {
            dbls.push_back(dbls.back() + dbls.back());
        }

        BigInt ret = a;
        for (int i = (int)dbls.size()-1; i >= 0; i--) {
            if (ret < dbls[i]) continue;
            ret = ret - dbls[i];
        }
        return ret;
    }

    friend int operator % (const BigInt &a, int d) {
        const int N = a.splits.size();

        int ret = 0;
        for (int i = N-1; i >= 0; i--) {
            ret = (1LL * ret * SPLIT_OVERFLOW + a.splits[i]) % d;
        }
        return ret;
    }

    friend BigInt operator / (const BigInt &a, int d) {
        const int N = a.splits.size();

        BigInt ret;
        ret.splits.resize(N);

        int64_t carry = 0;
        for (int i = N-1; i >= 0; i--) {
            int64_t x = carry * SPLIT_OVERFLOW + a.splits[i];
            ret.splits[i] = x / d;
            carry = x % d;
        }
        ret.canonicalize();
        return ret;
    }

    BigInt& operator += (const BigInt &b) {
        const int N = splits.size();
        const int M = b.splits.size();

        const int L = max(N, M);

        splits.resize(L);

        int carry = 0;
        for (int i = 0; i < L; i++) {
            int d = (i < N ? splits[i] : 0) + (i < M ? b.splits[i] : 0) + carry;
            splits[i] = d % SPLIT_OVERFLOW;
            carry = (d >= SPLIT_OVERFLOW);
        }

        if (carry) {
            splits.push_back(1);
        }

        return *this;
    }

    friend BigInt operator + (const BigInt& a, const BigInt& b) {
        BigInt ret = a;
        ret += b;
        return ret;
    }

    friend BigInt operator - (const BigInt& a, const BigInt& b) {
        // precondition: a >= b
        assert(b <= a);

        const int N = a.splits.size();
        const int M = b.splits.size();

        BigInt ret;
        ret.splits.resize(N);
        int borrow = 0;
        for (int i = 0; i < N; i++) {
            int d = a.splits[i] - (i < M ? b.splits[i] : 0) - borrow;
            if (d < 0) {
                d += SPLIT_OVERFLOW;
                borrow = 1;
            } else {
                borrow = 0;
            }
            ret.splits[i] = d;
        }
        assert(borrow == 0);

        ret.canonicalize();
        return ret;
    }

    friend bool operator <= (const BigInt& a, const BigInt& b) {
        return (a < b || a == b);
    }

    friend bool operator < (const BigInt& a, const BigInt& b) {
        if (a.splits.size() < b.splits.size()) return true;
        if (a.splits.size() > b.splits.size()) return false;

        for (int i = (int)a.splits.size()-1; i >= 0; i--) {
            if (a.splits[i] < b.splits[i]) return true;
            if (a.splits[i] > b.splits[i]) return false;
        }

        return false;
    }

    friend bool operator == (const BigInt& a, const BigInt& b) {
        return a.splits == b.splits;
    }
};

int N;

int main() {
    string s;
    cin >> s >> N;
    if (N == 1) {
        cout << s << endl;
        return 0;
    }
    BigInt a(s);
    vector<int> r;
    while (!(a == BigInt(0))) {
        r.push_back(a % N);
        a = a / N;
    }
    r.push_back(0);
    for (int i = 0; i < (int)r.size()-1; i++) {
        if (2*r[i] >= N+1 || (2*r[i] == N && r[i+1] >= N/2)) {
            r[i] = N - r[i];
            r[i+1]++;
        }
    }
    int ans = accumulate(r.begin(), r.end(), 0);
    printf("%d\n", ans);
    return 0;
}
