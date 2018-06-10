// https://www.luogu.org/problemnew/show/P1919
// 【模板】A*B Problem升级版（FFT快速傅里叶）

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

const int MAXN = 60010;
int N;

int main() {
    scanf("%d", &N);
    string sa, sb;
    cin >> sa >> sb;
    int nn = log2(N) + 2;
    nn = (1 << nn);
    vector<double> A(2*nn), B(2*nn);
    for (int i = 0; i < N; i++) {
        int x = sa[N-1-i] - '0';
        A[2*i] = x;
        x = sb[N-1-i] - '0';
        B[2*i] = x;
    }
    Fft::four1(A, 1);
    Fft::four1(B, 1);
    vector<double> C = Fft::innerProduct(A, B);

    Fft::four1(C, -1);
    vector<int> D(nn);
    for (int i = 0; i < nn; i++) {
        D[i] = C[2*i]/nn + 0.1;
    }
    string ret;
    for (int i = 0; i < nn-1; i++) {
        int x = D[i];
        ret.push_back('0' + x % 10);
        D[i+1] += x / 10;
    }
    ret.push_back(D[nn-1] + '0');

    for (int i = ret.length()-1; i > 0; i--) {
        if (ret[i] != '0') break;
        ret.pop_back();
    }
    reverse(ret.begin(), ret.end());
    cout << ret;
    
    return 0;
}
