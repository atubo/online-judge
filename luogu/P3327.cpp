// https://www.luogu.org/problemnew/show/P3327
// [SDOI2015]约数个数和

#include <bits/stdc++.h>
using namespace std;

class EulerSieve {
private:
public:
    vector<bool> isPrime;
    vector<int> primes, mu, ps;

    EulerSieve(int N) {
        assert(N > 1);

        isPrime.resize(N+1, true);
        mu.resize(N+1);
        ps.resize(N+1);

        isPrime[0] = isPrime[1] = false;
        mu[1] = 1;
        for (int i = 2; i <= N; i++) {
            if (isPrime[i]) {
                primes.push_back(i);
                mu[i] = -1;
            }

            for (int j = 0; j < (int)primes.size(); j++) {
                int64_t t = (int64_t)i * primes[j];
                if ( t > N) break;
                isPrime[t] = false;
                if (i % primes[j] == 0) {
                    mu[t] = 0;
                    break;
                } else {
                    mu[t] = -mu[i];
                }
            }
        }

        for (int i = 1; i <= N; i++) {
            ps[i] = ps[i-1] + mu[i];
        }
    }
};

const int MAXN = 50010;
int S[MAXN];

void build() {
    for (int x = 1; x < MAXN; x++) {
        int last = 0;
        for (int i = 1, j; i <= x; i=j+1) {
            j = x/(x/i);
            S[x] += (x/i)*(j-last);
            last = j;
        }
    }
}

void solve(const EulerSieve &sieve) {
    int n, m;
    scanf("%d%d", &n, &m);
    if (n > m) swap(n, m);
    int64_t ans = 0;
    int last = 0;
    for (int i=1, j; i <= n; i=j+1) {
        j = min(n/(n/i), m/(m/i));
        ans += 1LL*(sieve.ps[j]-sieve.ps[last])*S[n/i]*S[m/i];
        last = j;
    }
    printf("%ld\n", ans);
}

int main() {
    EulerSieve sieve(50000);
    build();
    int t;
    scanf("%d", &t);
    while (t--) {
        solve(sieve);
    }
    return 0;
}
