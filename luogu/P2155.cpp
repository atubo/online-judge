// https://www.luogu.org/problemnew/show/P2155
// [SDOI2008]沙拉公主的困惑

#include <bits/stdc++.h>
using namespace std;

class EulerSieve {
private:
public:
    bool *isPrime;
    vector<int> primes;

    EulerSieve(int N): n_(N) {
        assert(N > 1);
        alloc();

        isPrime[0] = isPrime[1] = false;
        for (int i = 2; i <= N; i++) {
            if (isPrime[i]) {
                primes.push_back(i);
            }

            for (int j = 0; j < (int)primes.size(); j++) {
                int64_t t = (int64_t)i * primes[j];
                if ( t > N) break;
                isPrime[t] = false;
                if (i % primes[j] == 0) {
                    break;
                }
            }
        }
    }
private:
    int n_;
    void alloc() {
        isPrime = new bool[n_]{};
        memset(isPrime, 1, n_*sizeof(bool));

    }

    void dealloc() {
        delete[] isPrime;
    }
};

const int MAXN = 10000010;
const int NUMP = 670000;
int T, R;
int N, M;
int upper[NUMP], lower[NUMP], inv[MAXN];
int fac[MAXN], fac2[MAXN];

int mul(int64_t a, int64_t b) {
    return (a * b) % R;
}

void init(const EulerSieve &sieve) {
    inv[1] = 1;
    for (int i = 2; i < R && i <= 1e7; i++) {
        inv[i] = 1ll * (R-R/i) * inv[R%i] % R;
    }
    upper[0] = 1;
    if (R == 2) lower[0] = 1;
    else lower[0] = inv[2];
    for (int i = 1; i < (int)sieve.primes.size(); i++) {
        int p = sieve.primes[i];
        upper[i] = mul(upper[i-1], p-1);
        if (p != R) {
            lower[i] = mul(lower[i-1], inv[p%R]);
        } else {
            lower[i] = lower[i-1];
        }
    }
    fac[1] = fac2[1] = 1;
    for (int i = 2; i < MAXN; i++) {
        fac[i] = mul(fac[i-1], i);
        if (i == R) fac2[i] = fac2[i-1];
        else fac2[i] = mul(fac2[i-1], i);
    }
}

int main() {
    scanf("%d%d", &T, &R);
    EulerSieve sieve(MAXN);
    init(sieve);
    while (T--) {
        scanf("%d%d", &N, &M);
        if (M == 1) {
            if (N >= R) printf("0\n");
            else printf("%d\n", fac[N]);
            continue;
        }
        auto it = upper_bound(sieve.primes.begin(), sieve.primes.end(), M);
        int k = it - sieve.primes.begin() - 1;
        int ans = mul(upper[k], lower[k]);
        if (M >= R) {
            ans = mul(ans, fac2[N]);
        } else {
            ans = mul(ans, fac[N]);
        }
        printf("%d\n", ans);
    }
                      
    return 0;
}
