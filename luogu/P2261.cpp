// https://www.luogu.org/problem/show?pid=2261
// [CQOI2007]余数求和

#include <bits/stdc++.h>
using namespace std;

int64_t f(int64_t a, int64_t k, int64_t m) {
    return m*a + k*m*(m-1)/2;
}

int main() {
    int64_t N, K;
    cin >> N >> K;
    int64_t ans = 0;
    int r = 0;
    for (int i = 1; i * i < K; i++) {
        if (N < K/(i+1) + 1) continue;
        ans += f(K%i, i, K/i - K/(i+1));
        if (N <= K/i) {
            ans -= f(K%i, i, K/i-N);
        }
        r = i;
    }
    for (int i = 1; i <= K/(r+1); i++) {
        ans += K % i;
    }
    ans += max(N-K, (int64_t)0) * K;
    cout << ans << endl;
    return 0;
}
