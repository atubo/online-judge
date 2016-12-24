// https://www.luogu.org/problem/show?pid=1604
// P1604 B进制星球

#include <algorithm>
#include <cassert>
#include <iostream>
#include <sstream>
#include <vector>
using namespace std;

class BigIntStringRepr {
    static const string ALPHA;
public:
    static char chr(int i) {
        return ALPHA[i];
    }

    static int ord(char c) {
        int ret = 0;
        for (; ret < 36; ret++) {
            if (ALPHA[ret] == c) break;
        }
        return ret;
    }

    static string add(const string& A, const string& B, int base) {
        const int N = A.length();
        const int M = B.length();

        const int L = max(N, M);
        string ret(L, char());
        int carry = 0;
        for (int i = 0; i < L; i++) {
            int d = (i < N ? ord(A[N-1-i]) : 0) + (i < M ? ord(B[M-1-i]) : 0) + carry;
            ret[L-1-i] = chr(d % base);
            carry = d/base;
        }

        if (carry) {
            ret.insert(0, 1, chr(carry));
        }

        return ret;
    }
};

const string BigIntStringRepr::ALPHA = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";

int main() {
    int base;
    string a, b;
    cin >> base >> a >> b;
    cout << BigIntStringRepr::add(a, b, base) << endl;
    return 0;
}
