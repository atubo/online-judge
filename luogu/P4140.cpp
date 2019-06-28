// https://www.luogu.org/problemnew/show/P4140
// 奇数国

#include <bits/stdc++.h>
using namespace std;

class BIT {
public:
    // 1-indexed
    BIT(int size=100000): N(size) {
        tree = (int*)malloc((size+1) * sizeof(int));
        clear();
    }

    ~BIT() {
        free(tree);
        tree = NULL;
    }

    void clear() {
        memset(tree, 0, (N+1) * sizeof(int));
    }

    // add v to value at x
    void set(int x, int v) {
        while(x <= N) {
            tree[x] += v;
            x += (x & -x);
        }
    }

    // get cumulative sum up to and including x
    int get(int x) const {
        int res = 0;
        while(x) {
            res += tree[x];
            x -= (x & -x);
        }
        return res;
    }

    // get result for [x, y]
    int get(int x, int y) const {
        return get(y) - (x > 1 ? get(x-1) : 0);
    }

private:
    int* tree;
    const int N;
};

class EulerSieve {
private:
public:
    vector<bool> isPrime;
    vector<int> primes, mu, phi, sigma;

    EulerSieve(int N) {
        assert(N > 1);

        isPrime.resize(N+1, true);
        mu.resize(N+1);
        phi.resize(N+1);
        sigma.resize(N+1);

        // local variable to calculate sigma (divisor function)
        // i = pj^k * ..., and pi(i) = (1 + pj + pj^2 + ...)
        vector<int> pi(N+1);

        isPrime[0] = isPrime[1] = false;
        mu[1] = 1;
        phi[1] = 1;
        sigma[1] = 1;
        for (int i = 2; i <= N; i++) {
            if (isPrime[i]) {
                primes.push_back(i);
                mu[i] = -1;
                phi[i] = i - 1;
                sigma[i] = pi[i] = i + 1;
            }

            for (int j = 0; j < (int)primes.size(); j++) {
                int64_t t = (int64_t)i * primes[j];
                if ( t > N) break;
                isPrime[t] = false;
                if (i % primes[j] == 0) {
                    mu[t] = 0;
                    phi[t] = phi[i] * primes[j];
                    pi[t] = pi[i] * primes[j] + 1;
                    sigma[t] = sigma[i]/pi[i] * pi[t];
                    break;
                } else {
                    mu[t] = -mu[i];
                    phi[t] = phi[i] * (primes[j] - 1);
                    pi[t] = primes[j] + 1;
                    sigma[t] = sigma[primes[j]] * sigma[i];
                }
            }
        }
    }
};

const int MOD = 19961993;
const int N = 100000;
int X;
int P[60][N+1];

int qpow(int p, int64_t n) {
    int64_t ret = 1;
    int64_t x = p;
    while (n) {
        if (n & 1) ret = (ret * x) % MOD;
        x = (x * x) % MOD;
        n >>= 1;
    }
    return ret;
}

int phi(int p, int64_t n) {
    if (n == 0) return 1;
    return (1LL * qpow(p, n-1) * (p-1)) % MOD;
}

void query(const vector<int> &primes, const vector<BIT> &fts, int a, int b) {
    int64_t ret = 1;
    for (int i = 0; i < 60; i++) {
        int64_t t = fts[i].get(a, b);
        (ret *= phi(primes[i], t)) %= MOD;
    }
    printf("%ld\n", ret);
}

void update(const vector<int> &primes, vector<BIT> &fts, int a, int b) {
    for (int i = 0; i < 60; i++) {
        int cnt = 0;
        while (b % primes[i] == 0) {
            b /= primes[i];
            cnt++;
        }
        int d = cnt - P[i][a];
        fts[i].set(a, d);
        P[i][a] = cnt;
    }
}

int main() {
    EulerSieve sieve(281);
    vector<BIT> fts(60);
    for (int x = 1; x <= N; x++) {
        fts[1].set(x, 1);
        P[1][x] = 1;
    }
    scanf("%d", &X);
    while (X--) {
        int a, b, c;
        scanf("%d%d%d", &a, &b, &c);
        if (a == 0) {
            query(sieve.primes, fts, b, c);
        } else {
            update(sieve.primes, fts, b, c);
        }
    }
    return 0;
}
