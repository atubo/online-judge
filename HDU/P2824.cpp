// http://acm.hdu.edu.cn/showproblem.php?pid=2824
// The Euler function
#include <bits/stdc++.h>
using namespace std;

class EulerSieve {
private:
public:
    vector<bool> isPrime;
    vector<int> primes, phi;

    EulerSieve(int N) {
        assert(N > 1);

        isPrime.resize(N+1, true);
        phi.resize(N+1);

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

const int MAXN = 3000000;

int main() {
    EulerSieve sieve(MAXN);
    int a, b;

    while (cin >> a >> b) {
        int64_t ans = 0;
        for (int i = a; i <= b; i++) {
            ans += sieve.phi[i];
        }
        cout << ans << endl;
    }

    return 0;
}
