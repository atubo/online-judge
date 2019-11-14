// https://www.luogu.org/problem/P2257
// YY的GCD

#include <bits/stdc++.h>
using namespace std;

class EulerSieve {
private:
public:
    vector<int> primes;
    bool* isPrime;
    int* mu;
    int* g;
    int64_t* sum;

    EulerSieve(int N) {
        assert(N > 1);

        isPrime = new bool[N+1]{};
        memset(isPrime, 1, (N+1)*sizeof(bool));
        mu = new int[N+1]{};
        g = new int[N+1]{};
        sum = new int64_t[N+1]{};

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

        for (int j = 0; j < (int)primes.size(); j++) {
          for (int i = 1; i*primes[j] <= N; i++) {
            g[i*primes[j]] += mu[i];
          }
        }
        for (int i = 1; i <= N; i++) sum[i] = sum[i-1] + int64_t(g[i]);
    }

    ~EulerSieve() {
      delete[] isPrime;
      delete[] mu;
      delete[] g;
      delete[] sum;
    }
};

const int MAXN = 10000000;

int T;
int N, M;

int main() {
  EulerSieve sieve(MAXN);
  scanf("%d", &T);
  while (T--) {
    scanf("%d%d", &N, &M);
    if (N > M) swap(N, M);
    int64_t ans = 0;
    for (int l = 1, r; l <= N; l = r+1) {
      r = min(N/(N/l), M/(M/l));
      ans += 1LL*(N/l)*(M/l)*(sieve.sum[r]-sieve.sum[l-1]);
    }
    printf("%ld\n", ans);
  }
  return 0;
}
