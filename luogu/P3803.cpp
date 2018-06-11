// https://www.luogu.org/problemnew/show/P3803
// 【模板】多项式乘法（FFT）

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

int N, M;

void solve(const vector<int> &A, const vector<int> &B) {
    int nn = log2(N) + 2;
    nn = (1 << nn);
    vector<double> x(2*nn), y(2*nn);
    for (int i = 0; i <= N; i++) {
        x[2*i] = A[i];
        if (i <= M) y[2*i] = B[i];
    }
    Fft::four1(x, 1);
    Fft::four1(y, 1);
    vector<double> z = Fft::innerProduct(x, y);
    Fft::four1(z, -1);
    for (int i = 0; i <= N+M; i++) {
        printf("%lld ", int64_t(z[2*i]/nn + 0.1));
    }
    printf("\n");
}

int main() {
    scanf("%d%d", &N, &M);
    vector<int> A(N+1), B(M+1);
    for (int i = 0; i <= N; i++) {
        scanf("%d", &A[i]);
    }
    for (int i = 0; i <= M; i++) {
        scanf("%d", &B[i]);
    }
    if (N < M) {
        swap(N, M);
        swap(A, B);
    }
    solve(A, B);
    return 0;
}
