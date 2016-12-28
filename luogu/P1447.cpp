// https://www.luogu.org/problem/show?pid=1447
// P1447 能量采集

#include <cassert>
#include <inttypes.h>
#include <iostream>
#include <vector>
using namespace std;

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

int64_t solve(int n, int m, const EulerSieve& sieve) {
    if (n > m) swap(n, m);
    int64_t ans = 0;
    for (int t = 1; t <= n; t++) {
        ans += (int64_t)(n/t) * (m/t) * sieve.phi[t];
    }
    return ans;
}

int main() {
    int64_t N, M;
    cin >> N >> M;
    EulerSieve sieve(100000);

    int64_t ans = solve(N, M, sieve);
    cout << 2*ans - N*M << endl;
    return 0;
}
