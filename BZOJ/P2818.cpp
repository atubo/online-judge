// http://www.lydsy.com/JudgeOnline/problem.php?id=2818
// 2818: Gcd
// see: http://97littleleaf11.xyz/tag/莫比乌斯反演

#include <inttypes.h>

#include <cassert>
#include <iostream>
#include <numeric>
#include <vector>

using namespace std;

vector<int> g;
vector<int> ps;

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
        g.resize(N+1);

        isPrime[0] = isPrime[1] = false;
        miu[1] = 1;
        phi[1] = 1;
        for (int i = 2; i <= N; i++) {
            if (isPrime[i]) {
                primes.push_back(i);
                miu[i] = -1;
                phi[i] = i - 1;
                g[i] = 1;
            }

            for (int j = 0; j < (int)primes.size(); j++) {
                int64_t t = (int64_t)i * primes[j];
                if ( t > N) break;
                isPrime[t] = false;
                if (i % primes[j] == 0) {
                    miu[t] = 0;
                    phi[t] = phi[i] * primes[j];
                    g[t] = miu[i];
                    break;
                } else {
                    miu[t] = -miu[i];
                    phi[t] = phi[i] * (primes[j] - 1);
                    g[t] = miu[i] - g[i];
                }
            }
        }
    }
};

int64_t solve(int n) {
    int64_t ans = 0;
    for (int l = 1, r; l <= n; l = r+1) {
        r = n/(n/l);
        ans += (int64_t)(n/l) * (n/l) * (ps[r] - ps[l-1]);
    }
    return ans;
}

int main() {
    int N;
    cin >> N;
    EulerSieve sieve(N);
    ps.resize(N+1);
    partial_sum(g.begin(), g.end(), ps.begin());
    cout << solve(N) << endl;
    return 0;
}
