// https://www.luogu.org/problemnew/show/P3321
// [SDOI2015]序列统计

#include <bits/stdc++.h>
using namespace std;

int M;

class Ntt {
public:
    static int primeRoot(int p) {
        vector<int> factors;
        int x = p - 1;
        for (int i = 2; i * i <= x; i++) {
            if (x % i == 0) {
                factors.push_back((p-1)/i);
                while (x % i == 0) x /= i;
            }
        }
        if (x > 1) factors.push_back((p-1)/x);

        for (int i = 2; ; i++) {
            bool ok = true;
            for (int y: factors) {
                if (pow(i, y, p) == 1) {
                    ok = false;
                    break;
                }
            }
            if (ok) return i;
        }
        return -1;
    }

    static void ntt(vector<int> &a, int op, int p, int g) {
        // length should be power of 2
        const int n = a.size();
        int j = 0;
        for (int i = 0; i < n; i++) {
            if (j > i) {
                swap(a[i], a[j]);
            }
            int m = (n >> 1);
            while (m >= 2 && j >= m) {
                j -= m;
                m >>= 1;
            }
            j += m;
        }

        for (int i = 1; i < n; i<<=1) {
            int64_t wn = pow(g, op==1?(p-1)/(2*i):p-1-(p-1)/(2*i), p), t, w;
            for (j = 0; j < n; j+=i<<1) {
                w = 1;
                for (int k = 0; k < i; k++) {
                    t = w*a[i+j+k]%p; w = w*wn%p;
                    a[i+j+k] = (a[j+k]-t+p)%p;
                    a[j+k] = (a[j+k]+t)%p;
                }
            }
        }

        if (op == -1) {
            int64_t inv = pow(n, p-2, p);
            for (int i = 0; i < n; i++) a[i] = a[i] * inv % p;
        }
    }

    static vector<int> innerProduct(const vector<int> &a, const vector<int>& b,
                                    int p) {
        const int n = a.size();
        vector<int> c(n);
        for (int i = 0; i < n; i++) {
            c[i] = int64_t(a[i]) * b[i] % p;
        }
        return c;
    }

    static vector<int> conv(vector<int> a, vector<int> b,
                            int p, int g) {
        ntt(a, 1, p, g);
        ntt(b, 1, p, g);
        vector<int> c = innerProduct(a, b, p);
        ntt(c, -1, p, g);
        for (int i = M; i < 2*M; i++) {
            c[i-M+1] = (c[i-M+1] + c[i]) % p;
            c[i] = 0;
        }
        return c;
    }
        
    static int pow(int64_t x, int y, int m) {
        int64_t ans = 1;
        while (y) {
            if (y & 1) ans = ans * x % m;
            x = x * x % m;
            y >>= 1;
        }
        return ans;
    }
};

const int P = 1004535809;
int N, X, S;

vector<int> solve(const vector<int> &a, int n, int r) {
    if (n == 1) return a;
    auto x = solve(a, n/2, r);
    x = Ntt::conv(x, x, P, r);
    if (n & 1) x = Ntt::conv(a, x, P, r);
    return x;
}

int main() {
    scanf("%d%d%d%d", &N, &M, &X, &S);
    int g = Ntt::primeRoot(M);
    vector<int> id(M);
    for (int i = 1, x = g; i < M; i++) {
        id[x] = i;
        x = (x*g)%M;
    }

    vector<int> a(8192*2);
    for (int i = 0; i < S; i++) {
        int x;
        scanf("%d", &x);
        if (x != 0) a[id[x]] = 1;
    }
    auto ret = solve(a, N, 3);
    printf("%d\n", ret[id[X]]);

    return 0;
}
