// https://www.luogu.org/problem/show?pid=2235
// P2235 [HNOI2002] Kathy函数

#include <cassert>
#include <cstdio>
#include <iostream>
#include <vector>
using namespace std;

class BigIntStringRepr {
    static vector<string> generateDoubles(const string& init, const string& a) {
        // generate init, init*2, init*4, till the first that >= a
        vector<string> dbls;
        dbls.push_back(init);
        while (less(dbls.back(), a)) {
            dbls.push_back(add(dbls.back(), dbls.back()));
        }
        return dbls;
    }

public:
    static void trimLeadingZeros(string& s) {
        int p = 0;
        while (p < (int)s.size()-1 && s[p] == '0') p++;
        if (p != 0) s = s.substr(p);
    }

    static string toBinary(const string& A) {
        // convert a decimal number to binary
        vector<string> dbls = generateDoubles("1", A);

        string ret;
        string a = A;
        for (int i = (int)dbls.size()-1; i >= 0; i--) {
            if (!less(a, dbls[i])) {
                ret.push_back('1');
                a = sub(a, dbls[i]);
            } else {
                ret.push_back('0');
            }
        }

        trimLeadingZeros(ret);
        return ret;
    }

    static bool less(const string& a, const string& b) {
        // check if a < b
        return (a.length() < b.length() ||
                (a.length() == b.length() && a < b));
    }

    static string add(const string& A, const string& B) {
        const int N = A.length();
        const int M = B.length();

        const int L = max(N, M);
        string ret(L, char());
        int carry = 0;
        for (int i = 0; i < L; i++) {
            int d = (i < N ? A[N-1-i] - '0' : 0) + (i < M ? B[M-1-i] - '0' : 0) + carry;
            ret[L-1-i] = '0' + (d%10);
            carry = d/10;
        }

        if (carry) {
            ret.insert(0, 1, '1');
        }

        return ret;
    }

    static string sub(const string& A, const string& B) {
        assert(less(B, A) || A == B);
        const int N = A.length();
        const int M = B.length();

        string ret(N, char());
        int borrow = 0;
        for (int i = 0; i < N; i++) {
            int d = A[N-1-i] - '0' - (i < M ? B[M-1-i] - '0' : 0) - borrow;
            if (d < 0) {
                d += 10;
                borrow = 1;
            } else {
                borrow = 0;
            }
            ret[N-1-i] = d + '0';
        }
        assert(borrow == 0);

        trimLeadingZeros(ret);
        return ret;
    }
};

class Solution {
private:
    int N;
    string binaryStr;
    vector<string> fullCounter; // count of palindromes for 0 - 1111..111 (n 1's)
    vector<string> powerOf2;
public:
    Solution() {
        string s;
        cin >> s;
        binaryStr = BigIntStringRepr::toBinary(s);
        N = binaryStr.length();

        buildPowerOf2();
        buildCounter();
    }

    void buildPowerOf2() {
        powerOf2.resize(N+1, "1");
        for (int i = 1; i <= N; i++) {
            powerOf2[i] = BigIntStringRepr::add(powerOf2[i-1], powerOf2[i-1]);
        }
    }

    void buildCounter() {
        fullCounter.resize(N+1, "0");
        fullCounter[1] = "2";
        for (int i = 2; i <= N; i++) {
            fullCounter[i] = BigIntStringRepr::add(fullCounter[i-1], powerOf2[(i-1)/2]);
        }
    }

    bool equalsZero(const string& a) {
        for (int i = 0; i < (int)a.length(); i++) {
            if (a[i] != '0') return false;
        }
        return true;
    }

    void decrement(string& s) {
        for (int i = (int)s.length()-1; i >= 0; i--) {
            if (s[i] == '1') {
                s[i] = '0';
                break;
            } else {
                s[i] = '1';
            }
        }
    }

    string solve2(const string& s) {
        const int n = s.length();
        if (n == 0) return "1";
        if (n == 1) return (s[0] == '0' ? "1" : "2");

        string b = s.substr(1, n-2);
        if (s[0] == '0') return solve2(b);
        if (s[n-1] == '1') {
            return BigIntStringRepr::add(powerOf2[(n-1)/2], solve2(b));
        }

        if (b.empty() || equalsZero(b)) return powerOf2[(n-1)/2];
        decrement(b);
        return BigIntStringRepr::add(powerOf2[(n-1)/2], solve2(b));
    }

    string solve() {
        assert(binaryStr[0] == '1');
        if (N == 1) return "2";
        string b = binaryStr.substr(1, N-2);
        if (binaryStr[N-1] == '1') {
            return BigIntStringRepr::add(fullCounter[N-1],
                                         solve2(b));
        } else {
            if (b.empty() || equalsZero(b)) return fullCounter[N-1];
            decrement(b);
            return BigIntStringRepr::add(fullCounter[N-1],
                                         solve2(b));
        }
    }
};

int main() {
    Solution solution;
    cout << BigIntStringRepr::sub(solution.solve(), "1") << endl;
    return 0;
}
