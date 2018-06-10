// https://www.luogu.org/problemnew/show/P3338
// [ZJOI2014]力

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
};

const int MAXN = 100010;
int N;
double Q[MAXN];

int main() {
    scanf("%d", &N);
    for (int i = 0; i < N; i++) {
        scanf("%lf", &Q[i]);
    }
    int nn = log2(N) + 2;
    nn = (1 << nn);
    vector<double> Q1(2*nn), B(2*nn);
    for (int i = 0; i < N; i++) {
        Q1[2*i] = Q[i];
        if (i != 0) B[2*i] = 1.0/i/i;
    }

    Fft::four1(Q1, 1);
    Fft::four1(B, 1);
    vector<double> F1(2*nn);
    for (int i = 0; i < nn; i++) {
        double a = Q1[2*i], b = Q1[2*i+1];
        double c = B[2*i], d = B[2*i+1];
        F1[2*i] = a*c - b*d;
        F1[2*i+1] = a*d + b*c;
    }
    Fft::four1(F1, -1);

    vector<double> Q2(2*nn);
    for (int i = 0; i < N; i++) {
        Q2[2*(nn-1-i)] = Q[i];
    }
    Fft::four1(Q2, 1);
    vector<double> F2(2*nn);
    for (int i = 0; i < nn; i++) {
        double a = Q2[2*i], b = Q2[2*i+1];
        double c = B[2*i], d = B[2*i+1];
        F2[2*i] = a*c - b*d;
        F2[2*i+1] = a*d + b*c;
    }
    Fft::four1(F2, -1);

    for (int i = 0; i < N; i++) {
        printf("%.3f\n", (F1[2*i] - F2[2*(nn-1-i)])/nn);
    }

    return 0;
}
