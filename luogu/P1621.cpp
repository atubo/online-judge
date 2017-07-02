// https://www.luogu.org/problem/show?pid=1621
// 集合

#include <bits/stdc++.h>
using namespace std;

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

class UnionFind {
public:
    int ng;
private:
    const int N;
    vector<int> rank;
    vector<int> parent;
    vector<int> size;

    void makeSet(int k) {
        assert(0 <= k && k < N);

        parent[k] = k;
        rank[k] = 0;
        size[k] = 1;
    }

    void link(int u, int v) {
        if (rank[u] > rank[v]) {
            parent[v] = u;
            size[u] += size[v];
        } else {
            parent[u] = v;
            size[v] += size[u];
            if (rank[u] == rank[v]) {
                rank[v]++;
            }
        }
        ng--;
    }

public:
    UnionFind(int n): N(n) {
        rank.resize(N);
        parent.resize(N);
        size.resize(N);

        reset();
        ng = N;
    }

    void reset() {
        for (int i = 0; i < N; i++) {
            makeSet(i);
        }
    }

    int find(int k) {
        if (parent[k] == k) return k;
        int root = find(parent[k]);
        return parent[k] = root;
    }

    void join(int u, int v) {
        link(find(u), find(v));
    }

    int count(int u) {
        return size[find(u)];
    }
};

int main() {
    int A, B, P;
    cin >> A >> B >> P;
    EulerSieve euler(100100);

    UnionFind uf(B-A+1);
    const vector<int>& primes = euler.primes;

    int lo = lower_bound(primes.begin(), primes.end(), P) - primes.begin();
    int hi = upper_bound(primes.begin(), primes.end(), B) - primes.begin();

    for (int i = lo; i < hi; i++) {
        int p = primes[i];
        int start = (A+p-1)/p * p;
        for (int j = start; j <= B; j += p) {
            if (uf.find(j-A) != uf.find(start-A)) uf.join(j-A, start-A);
        }
    }
    cout << uf.ng << endl;

    return 0;
}
