// https://www.luogu.org/problemnew/show/P4199
// 万径人踪灭

#include <bits/stdc++.h>
using namespace std;

class Fft {
public:
    constexpr const static double PI = 3.14159265359;
    static void four1(vector<double> &data, const int isign) {
        int nn = data.size() / 2;
        int n = nn << 1;
        int j = 1;
        for (int i = 1; i < n; i+=2) {
            if (j > i) {
                swap(data[j-1], data[i-1]);
                swap(data[j], data[i]);
            }
            int m = nn;
            while (m >= 2 && j > m) {
                j -= m;
                m >>= 1;
            }
            j += m;
        }

        int mmax = 2;
        while (n > mmax) {
            int istep = mmax << 1;
            double theta = isign * (2 * PI / mmax);
            double wtemp = sin(0.5 * theta);
            double wpr = - 2.0 * wtemp * wtemp;
            double wpi = sin(theta);
            double wr = 1.0;
            double wi = 0.0;
            for (int m = 1; m < mmax; m += 2) {
                for (int i = m; i <= n; i += istep) {
                    j = i + mmax;
                    double tempr = wr * data[j-1] - wi * data[j];
                    double tempi = wr * data[j] + wi * data[j-1];
                    data[j-1] = data[i-1] - tempr;
                    data[j] = data[i] - tempi;
                    data[i-1] += tempr;
                    data[i] += tempi;
                }
                wr = (wtemp=wr)*wpr - wi*wpi + wr;
                wi = wi*wpr + wtemp*wpi + wi;
            }
            mmax = istep;
        }
    }

    static vector<double> innerProduct(const vector<double> &x,
                                       const vector<double> &y) {
        const int n = x.size() / 2;
        vector<double> ret(2*n);
        for (int i = 0; i < n; i++) {
            double a = x[2*i], b = x[2*i+1];
            double c = y[2*i], d = y[2*i+1];
            ret[2*i] = a*c - b*d;
            ret[2*i+1] = a*d + b*c;
        }
        return ret;
    }
};

// see https://www.felix021.com/blog/read.php?2040
struct Manacher {
    const int length_;
    // p[i] stores maximum radius from position i (including i)
    // in the *modified* string (including spaces between letters)
    // note place before the first char is 1, first char is 2
    // second char is 4, etc.
    int *p;
    char *s;
    int *maxlen;

    Manacher(const string &sin):length_(sin.length()) {
        alloc();

        // put special charaters at the begining and between letters
        s[0] = '$';
        s[1] = '#';
        for (int i = 0; i < (int)sin.length(); i++) {
            s[i*2+2] = sin[i];
            s[i*2+3] = '#';
        }

        int mx = 0, id = 0;
        for (int i = 1; s[i] != '\0'; i++) {
            p[i] = mx > i ? min(p[2*id-i], mx-i) : 1;
            while (s[i+p[i]] == s[i-p[i]]) p[i]++;
            if (i + p[i] > mx) {
                mx = i + p[i];
                id = i;
            }
        }
    }

    ~Manacher() {
        dealloc();
    }

    // some utility functions
    // find for each position the maximum length of the palindrom start there
    // note the index starts from 0
    void calcMaxlen() {
        for (int i = 1; s[i] != '\0'; i++) {
            int pos = (i - p[i]) / 2;
            maxlen[pos] = max(maxlen[pos], p[i]-1);
        }
        for (int i = 1; s[i] != '\0'; i++) {
            maxlen[i] = max(maxlen[i-1]-2, maxlen[i]);
        }
    }

private:
    void alloc() {
        p = new int[2*length_+10]{};
        s = new char[2*length_+10]{};
        maxlen = new int[length_+10]{};
    }

    void dealloc() {
        delete[] p;
        delete[] s;
        delete[] maxlen;
    }
};

const int MOD = 1e9+7;
const int MAXN = 100010;
int A[MAXN], ps[MAXN];
int N;

int64_t power(int64_t x, int p) {
    if (p == 0) return 1;
    int64_t y = power(x, p/2);
    y = (y * y) % MOD;
    if (p & 1) y = (y * x) % MOD;
    return y;
}

void solve(const string &s) {
    int nn = log2(N) + 3;
    nn = (1 << nn);
    vector<double> a(nn);
    for (int i = 0; i < N; i++) {
        a[2*i] = A[i];
    }
    Fft::four1(a, 1);
    auto c = Fft::innerProduct(a, a);
    Fft::four1(c, -1);
    vector<int> va(2*N-1);
    for (int i = 0; i < 2*N-1; i++) {
        int x = c[2*i] * 2 / nn + 0.1;
        if (i <= N-1) x = 2*x + i + 1 - 2 * ps[i];
        else x = 2*x - i + 2*(N-1) - 2 * (ps[N-1]-ps[i-N]) + 1;

        va[i] = x;
    }
    vector<int> vb(2*N-1);
    Manacher manacher(s);
    for (int i = 2; i < 2*N+1; i++) {
        vb[i-2] = manacher.p[i];
    }

    int64_t ans = 0;
    for (int i = 0;i < 2*N-1; i++) {
        int x = (va[i]+1) / 2;
        int p1 = (power(2, x) + MOD - 1) % MOD;
        int p2 = vb[i] / 2;
        ans = (ans + p1 + MOD - p2) % MOD;
    }
    printf("%lld", ans);
}

int main() {
    string s;
    cin >> s;
    N = s.length();
    for (int i = 0; i < N; i++) A[i] = s[i] - 'a';
    ps[0] = A[0];
    for (int i = 1; i < N; i++) ps[i] = A[i] + ps[i-1];
    solve(s);
    return 0;
}
