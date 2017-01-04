// http://www.spoj.com/problems/MSKYCODE/
// MSKYCODE - Sky Code

#include <bits/stdc++.h>
using namespace std;

class EulerSieve {
private:
public:
    vector<bool> isPrime;
    vector<int> primes, mu, phi;

    EulerSieve(int N) {
        assert(N > 1);

        isPrime.resize(N+1, true);
        mu.resize(N+1);
        phi.resize(N+1);

        isPrime[0] = isPrime[1] = false;
        mu[1] = 1;
        phi[1] = 1;
        for (int i = 2; i <= N; i++) {
            if (isPrime[i]) {
                primes.push_back(i);
                mu[i] = -1;
                phi[i] = i - 1;
            }

            for (int j = 0; j < (int)primes.size(); j++) {
                int64_t t = (int64_t)i * primes[j];
                if ( t > N) break;
                isPrime[t] = false;
                if (i % primes[j] == 0) {
                    mu[t] = 0;
                    phi[t] = phi[i] * primes[j];
                    break;
                } else {
                    mu[t] = -mu[i];
                    phi[t] = phi[i] * (primes[j] - 1);
                }
            }
        }
    }
};

const int MAXN = 10000;

class Solution {
private:
    EulerSieve *sieve;
    int N;
    vector<int> A;
public:
    Solution() {
        sieve = new EulerSieve(MAXN);
    }

    void solve() {
        while (scanf("%d", &N) != EOF) {
            A.resize(N);
            for (int i = 0; i < N; i++) {
                scanf("%d", &A[i]);
            }

            cout << calc() << endl;
        }
    }

    void collectStat(int x, vector<int>& C) {
        for (int i = 1; i * i <= x; i++) {
            if (x % i == 0) {
                if (i * i == x) {
                    C[i]++;
                } else {
                    C[i]++;
                    C[x/i]++;
                }
            }
        }
    }

    int64_t choose4(int64_t x) {
        return x * (x-1) * (x-2) * (x-3) / 24;
    }

    int64_t calc() {
        vector<int> C(MAXN+1);
        for (int x: A) {
            collectStat(x, C);
        }

        int64_t ans = 0;
        for (int i = 1; i <= MAXN; i++) {
            ans += choose4(C[i]) * sieve->mu[i];
        }
        return ans;
    }
};

int main() {
    Solution solution;
    solution.solve();
    return 0;
}

