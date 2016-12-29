// http://www.spoj.com/problems/VLATTICE/
// VLATTICE - Visible Lattice Points

#include <inttypes.h>

#include <cassert>
#include <iostream>
#include <vector>

using namespace std;

const int MAXN = 1000000;
vector<int> ps(MAXN+1);

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


int64_t solve(int64_t n) {
    int64_t ans = 0;

    for (int l = 1, r; l <= n; l = r + 1) {
        r = n / (n/l);
        ans += ((n/l) * (n/l) * (n/l) + (n/l) * (n/l) * 3) * (ps[r] - ps[l-1]);
    }
    return ans;
}

int main() {
    EulerSieve sieve(MAXN);
    for (int i = 1; i <= MAXN; i++) {
        ps[i] = ps[i-1] + sieve.miu[i];
    }

    int T;
    cin >> T;
    for (int i = 0; i < T; i++) {
        int N;
        cin >> N;
        cout << solve(N) + 3 << endl;
    }
    return 0;
}
