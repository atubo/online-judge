// https://www.luogu.org/problem/show?pid=2142
// 高精度减法

#include <algorithm>
#include <cassert>
#include <iostream>
#include <sstream>
#include <vector>
using namespace std;

class BigInt {
    // split every 9 digits
    // LSD in the first split, and so on
    static const int SPLIT_LEN = 9;
    static const int SPLIT_OVERFLOW = 1000000000;
private:
    vector<int> splits;

    static BigInt mul(const BigInt& a, const BigInt& b) {
        // should be called with b <= a (for efficiency)
        vector<BigInt> dblOfOne, dblOfA;
        dblOfOne.push_back(BigInt("1"));
        dblOfA.push_back(a);
        while (dblOfOne.back() < b) {
            dblOfOne.push_back(dblOfOne.back() + dblOfOne.back());
            dblOfA.push_back(dblOfA.back() + dblOfA.back());
        }

        BigInt ret;
        BigInt remain = b;
        for (int i = (int)dblOfOne.size()-1; i >= 0; i--) {
            if (remain < dblOfOne[i]) continue;
            remain = remain - dblOfOne[i];
            ret = ret + dblOfA[i];
        }
        return ret;
    }

public:
    BigInt() {
        splits.resize(1, 0);
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

    friend BigInt operator + (const BigInt& a, const BigInt& b) {
        const int N = a.splits.size();
        const int M = b.splits.size();

        const int L = max(N, M);

        BigInt ret;
        ret.splits.resize(L);

        int carry = 0;
        for (int i = 0; i < L; i++) {
            int d = (i < N ? a.splits[i] : 0) + (i < M ? b.splits[i] : 0) + carry;
            ret.splits[i] = d % SPLIT_OVERFLOW;
            carry = (d >= SPLIT_OVERFLOW);
        }

        if (carry) {
            ret.splits.push_back(1);
        }

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

        for (int i = N-1; i > 0; i--) {
            if (ret.splits[i] == 0) ret.splits.pop_back();
            else break;
        }

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

int main() {
    string sa, sb;
    cin >> sa >> sb;
    BigInt a(sa), b(sb);
    if (a < b) {
        cout << "-" << (b - a).toString() << endl;
    } else {
        cout << (a - b).toString() << endl;
    }
    return 0;
}
