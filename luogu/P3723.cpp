// https://www.luogu.org/problemnew/show/P3723
// [AH2017/HNOI2017]礼物

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

vector<int64_t> rotateProduct(const vector<int>& x, const vector<int> &y) {
    const int n = x.size();
    int nn = log2(n) + 3;
    nn = (1 << nn);
    vector<double> a(2*nn), b(2*nn);
    for (int i = 0; i < 2*n; i += 2) {
        a[i] = x[i/2];
        b[i] = b[i+2*n] = y[n-1-i/2];
    }
    Fft::four1(a, 1);
    Fft::four1(b, 1);
    vector<double> c = Fft::innerProduct(a, b);
    Fft::four1(c, -1);
    vector<int64_t> ret(n);
    for (int i = 0; i < n; i++) {
        ret[i] = c[2*(i+n-1)]/nn  + 0.1;
    }
    return ret;
}

int64_t ans = 1e12;
int N, M;

void solve(int c, const vector<int> &x, vector<int> y) {
    int64_t totsq = 0;
    for (int i = 0; i < N; i++) {
        y[i] += c;
        totsq += y[i]*y[i] + x[i]*x[i];
    }

    vector<int64_t> z = rotateProduct(x, y);

    int64_t maxp = *max_element(z.begin(), z.end());
    ans = min(ans, totsq - 2*maxp);
}

int main() {
    scanf("%d%d", &N, &M);
    vector<int> x(N), y(N);
    int totx = 0, toty = 0;
    for (int i = 0; i < N; i++) {
        scanf("%d", &x[i]);
        totx += x[i];
    }
    for (int i = 0; i < N; i++) {
        scanf("%d", &y[i]);
        toty += y[i];
    }
    if (totx < toty) {
        swap(totx, toty);
        swap(x, y);
    }
    vector<int> cz;
    cz.push_back((totx-toty)/N);
    if ((totx-toty) % N != 0) {
        cz.push_back(cz[0]+1);
    }

    for (int c: cz) {
        solve(c, x, y);
    }
    printf("%lld\n", ans);
    return 0;
}
