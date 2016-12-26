// https://www.luogu.org/problem/show?pid=1865
// P1865 A % B Problem

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
                int t = i * primes[j];
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
    int N, M;
    cin >> N >> M;
    EulerSieve sieve(M);
    vector<int> ps(M+1);
    ps[0] = 0;
    for (int i = 1; i <= M; i++) {
        ps[i] = ps[i-1] + sieve.isPrime[i];
    }

    for (int i = 0; i < N; i++) {
        int l, r;
        cin >> l >> r;
        if (!(1 <= l && l <= M) || !(1 <= r && r <= M)) {
            cout << "Crossing the line" << endl;
            continue;
        }
        cout << ps[r] - ps[l-1] << endl;
    }

    return 0;
}
