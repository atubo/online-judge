// https://www.luogu.org/problem/show?pid=2158
// P2158 [SDOI2008]仪仗队

#include <inttypes.h>

#include <cassert>
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

int main() {
    int N;
    cin >> N;
    if (N == 1) {
        cout << 0 << endl;
        return 0;
    }
    EulerSieve sieve(N);
    int ans = 0;
    for (int i = 1; i < N; i++) {
        ans += sieve.phi[i];
    }
    ans = 2 * ans + 1;
    cout << ans << endl;
    return 0;
}
