// https://www.luogu.org/problemnew/show/P4173
// 残缺的字符串

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

const int MAXN = 300010;
int M, N;
int A[MAXN], B[MAXN];

vector<double> solve(int nn) {
    vector<double> a(nn), b(nn);
    for (int i = 0; i < N; i++) {
        a[2*i] = A[N-1-i]*A[N-1-i]*A[N-1-i];
        b[2*i] = B[i];
    }
    Fft::four1(a, 1);
    Fft::four1(b, 1);
    auto c1 = Fft::innerProduct(a, b);

    for (int i = 0; i < N; i++) {
        a[2*i] = A[N-1-i]*A[N-1-i];
        b[2*i] = B[i]*B[i];
        a[2*i+1] = b[2*i+1] = 0;
    }
    for (int i = 2*N; i < nn; i++) {
        a[i] = b[i] = 0;
    }
    Fft::four1(a, 1);
    Fft::four1(b, 1);
    auto c2 = Fft::innerProduct(a, b);

    for (int i = 0; i < N; i++) {
        a[2*i] = A[N-1-i];
        b[2*i] = B[i]*B[i]*B[i];
        a[2*i+1] = b[2*i+1] = 0;
    }
    for (int i = 2*N; i < nn; i++) {
        a[i] = b[i] = 0;
    }
    Fft::four1(a, 1);
    Fft::four1(b, 1);
    auto c3 = Fft::innerProduct(a, b);

    vector<double> c(nn);
    for (int i = 0; i < nn; i++) {
        c[i] = c1[i] - 2*c2[i] + c3[i];
    }

    Fft::four1(c, -1);
    vector<double> ret(nn/2);
    for (int i = 0; i < nn/2; i++) {
        ret[i] = c[i*2] * 2/nn;
    }
    return ret;
}

int main() {
    scanf("%d%d", &M, &N);
    string sa, sb;
    cin >> sa >> sb;
    for (int i = 0; i < M; i++) {
        if (sa[i] == '*') A[i] = 0;
        else A[i] = sa[i] - 'a' + 1;
    }
    for (int i = 0; i < N; i++) {
        if (sb[i] == '*') B[i] = 0;
        else B[i] = sb[i] - 'a' + 1;
    }

    int nn = log2(N) + 3;
    nn = (1 << nn);

    auto t = solve(nn);
    vector<int> ans;
    for (int i = N-1; i <= 2*N-M-1; i++) {
        if (fabs(t[i]) < 0.5) ans.push_back(i-N+2);
    }
    printf("%d\n", ans.size());
    for (int x: ans) {
        printf("%d ", x);
    }

    return 0;
}
