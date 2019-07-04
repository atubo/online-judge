// https://www.luogu.org/problemnew/show/P2568
// GCD

#include <bits/stdc++.h>
using namespace std;

class EulerSieve {
private:
    void alloc(int n) {
        phi = new int[n+1]{};
        ps = new int64_t[n+1]{};
        isPrime = new bool[n+1]{};
        memset(isPrime, 1, (n+1)*sizeof(bool));
    }

    void dealloc() {
        delete[] phi;
        delete[] ps;
        delete[] isPrime;
    }
public:
    int *phi;
    int64_t *ps;
    bool *isPrime;
    vector<int> primes;

    EulerSieve(int N) {
        assert(N > 1);

        alloc(N);


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
        for (int i = 2; i <= N; i++) {
            ps[i] = ps[i-1] + phi[i];
        }
    }

    ~EulerSieve() {
        dealloc();
    }
};

int N;

int main() {
    scanf("%d", &N);
    EulerSieve sieve(N);
    int64_t ans = 0;
    for (int p: sieve.primes) {
        int x = N/p;
        ans += 2LL * sieve.ps[x];
    }
    ans += sieve.primes.size();
    printf("%ld\n", ans);
    return 0;
}
