// http://www.lydsy.com/JudgeOnline/problem.php?id=2301
// 2301: [HAOI2011]Problem b
// see: https://oi.men.ci/haoi2011-problemb/

#include <inttypes.h>

#include <cassert>
#include <cstdio>
#include <vector>
using namespace std;

const int MAXN = 50000;

class EulerSieve {
private:
public:
    vector<bool> isPrime;
    vector<int> primes, miu, phi;

    EulerSieve(int N) {
        assert(N > 1);

        isPrime.resize(N+1, true);
        miu.resize(N+1);
        phi.resize(N+1);

        isPrime[0] = isPrime[1] = false;
        miu[1] = 1;
        phi[1] = 1;
        for (int i = 2; i <= N; i++) {
            if (isPrime[i]) {
                primes.push_back(i);
                miu[i] = -1;
                phi[i] = i - 1;
            }

            for (int j = 0; j < (int)primes.size(); j++) {
                int64_t t = (int64_t)i * primes[j];
                if ( t > N) break;
                isPrime[t] = false;
                if (i % primes[j] == 0) {
                    miu[t] = 0;
                    phi[t] = phi[i] * primes[j];
                    break;
                } else {
                    miu[t] = -miu[i];
                    phi[t] = phi[i] * (primes[j] - 1);
                }
            }
        }
    }
};

vector<int> ps(MAXN+1);

int solve(int n, int m, int k) {
    if (n > m) swap(n, m);
    n /= k;
    m /= k;
    int ans = 0;
    for (int l = 1, r; l <= n; l = r+1) {
        r = min(n/(n/l), m/(m/l));
        ans += (n/l) * (m/l) * (ps[r] - ps[l-1]);
    }
    return ans;
}

int main() {
    int N;
    scanf("%d", &N);
    EulerSieve sieve(MAXN);
    for (int i = 1; i <= MAXN; i++) {
        ps[i] = ps[i-1] + sieve.miu[i];
    }

    int a, b, c, d, k;
    for (int i = 0; i < N; i++) {
        scanf("%d %d %d %d %d", &a, &b, &c, &d, &k);
        printf("%d\n", solve(b, d, k) - solve(b, c-1, k) - solve(a-1, d, k) + solve(a-1, c-1, k));
    }

    return 0;
}
