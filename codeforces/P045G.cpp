// https://codeforces.com/problemset/problem/45/G
// Prime Problem

#include <bits/stdc++.h>
using namespace std;

class EulerSieve {
 private:
  int n_;
  void alloc() {
    isPrime = new bool[n_+1]{};
    memset(isPrime, 1, (n_+1)*sizeof(bool));
  }

  void dealloc() {
    delete[] isPrime;
  }
 public:
  bool* isPrime;
  vector<int> primes;

  EulerSieve(int N) : n_(N) {
    assert(N > 1);

    alloc();

    isPrime[0] = isPrime[1] = false;
    for (int i = 2; i <= N; i++) {
      if (isPrime[i]) {
        primes.push_back(i);
      }

      for (int j = 0; j < (int)primes.size(); j++) {
        int64_t t = (int64_t)i * primes[j];
        if ( t > N) break;
        isPrime[t] = false;
        if (i % primes[j] == 0) {
          break;
        }
      }
    }
  }

  ~EulerSieve() {
    dealloc();
  }
};

void solve2(const EulerSieve& sieve, int n) {
  int tot = n * (n+1) / 2;
  int p1 = 0;
  for (int p : sieve.primes) {
    if (sieve.isPrime[tot-p]) {
      p1 = p;
      assert(p1 <= n);
      break;
    }
  }
  for (int i = 1; i <= n; i++) {
    printf("%d", (i == p1 ? 2 : 1));
    printf("%c", (i == n ? '\n' : ' '));
  }
}

void solve3(const EulerSieve& sieve, int n) {
  int tot = n * (n+1) / 2;
  bool found = false;
  int p1 = 0, p2 = 0;
  for (int i = 1; i < (int)sieve.primes.size(); i++) {
    for (int j = i+1; j < (int)sieve.primes.size(); j++) {
      if (sieve.isPrime[tot-sieve.primes[i]-sieve.primes[j]]) {
        p1 = sieve.primes[i];
        p2 = sieve.primes[j];
        assert(sieve.primes[i] <= n && sieve.primes[j] <= n);
        found = true;
        break;
      }
    }
    if (found) break;
  }
  for (int i = 1; i <= n; i++) {
    printf("%d", (i == p1 ? 2 : (i == p2 ? 3 : 1)));
    printf("%c", (i == n ? '\n' : ' '));
  }
}

int main() {
  int n;
  scanf("%d", &n);
  if (n == 2) {
    printf("1 1\n");
    return 0;
  }
  int tot = n*(n+1)/2;
  EulerSieve sieve(tot);
  if (tot % 2 == 0) {
    solve2(sieve, n);
  } else if (sieve.isPrime[tot-2]) {
    for (int i = 1; i <= n; i++) {
      printf("%d", (i == 2 ? 2 : 1));
      printf("%c", (i == n ? '\n' : ' '));
    }
  } else {
    solve3(sieve, n);
  }
  return 0;
}
