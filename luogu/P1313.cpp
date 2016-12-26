// https://www.luogu.org/problem/show?pid=1313
// P1313 计算系数

#include <iostream>
using namespace std;

const int MOD = 10007;

int mul(int a, int b) {
    return (a * b) % MOD;
}

int add(int a, int b) {
    return (a + b) % MOD;
}

int pwr(int a, int n) {
    int ret = 1;
    for (int i = 1; i <= n; i++) {
        ret = mul(ret, a);
    }
    return ret;
}

// generate binomial coefficients
// binom[n][k] = n \choose k
namespace Binom {
    const int MAXN = 1005;
    int binom[MAXN][MAXN];

    void generate(int N) {
        binom[0][0] = 1;
        for (int i = 1; i <= N; i++) {
            binom[i][0] = 1;
            for (int j = 1; j <= i; j++) {
                binom[i][j] = add(binom[i-1][j], binom[i-1][j-1]);
            }
        }
    }
}

int main() {
    int a, b, k, n, m;
    cin >> a >> b >> k >> n >> m;
    Binom::generate(1000);

    a = a % MOD;
    b = b % MOD;
    cout << mul(mul(pwr(a, n), pwr(b, m)), Binom::binom[k][n]) << endl;
    return 0;
}
