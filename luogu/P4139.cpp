// https://www.luogu.org/problemnew/show/P4139
// 上帝与集合的正确用法

#include <bits/stdc++.h>
using namespace std;

const int MAXN = 1e7+10;
int phi[MAXN];
bool isPrime[MAXN];

class EulerSieve {
private:
public:
    vector<int> primes;

    EulerSieve(int N) {
        assert(N > 1);

        isPrime[0] = isPrime[1] = false;
        phi[1] = 1;
        for (int i = 2; i <= N; i++) {
            if (isPrime[i]) {
                primes.push_back(i);
                phi[i] = i - 1;
            }

            for (int j = 0; j < (int)primes.size(); j++) {
                int64_t t = (int64_t)i * primes[j];
                if ( t > N) break;
                isPrime[t] = false;
                if (i % primes[j] == 0) {
                    phi[t] = phi[i] * primes[j];
                    break;
                } else {
                    phi[t] = phi[i] * (primes[j] - 1);
                }
            }
        }
    }
};

int T;

int qpow(int n, int p) {
    int64_t ret = 1;
    int64_t x = 2;
    while (n) {
        if (n & 1) (ret *= x) %= p;
        (x *= x) %= p;
        n >>= 1;
    }
    return ret;
}

int solve(int p) {
    if (p == 1) return 0;
    int f = phi[p];
    int po = solve(f) + f;
    return qpow(po, p);
}

int main() {
    memset(isPrime, 0xFF, sizeof(isPrime));
    EulerSieve sieve(1e7+2);
    scanf("%d", &T);
    while (T--) {
        int p;
        scanf("%d", &p);
        printf("%d\n", solve(p));
    }
    return 0;
}
