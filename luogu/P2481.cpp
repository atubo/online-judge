// https://www.luogu.org/problemnew/show/P2481
// [SDOI2010]代码拍卖会

#include <bits/stdc++.h>
using namespace std;

class ModularUtils {
public:
    // return (a * b) mod n, dealing with possible overflow
    static int64_t mul_long(int64_t x, int64_t y, int64_t mod) {
        if (y < 0) {
            x = -x;
            y = -y;
        }
        int64_t s = 0, n = y, t = x;
        while (n) {
            if (n & 1) (s += t) %= mod;
            (t += t) %= mod;
            n >>= 1;
        }
        return s;
    }


    // (g, x, y) that a*x + b*y = g
    static void ext_gcd(int64_t a, int64_t b,
                        int64_t &g, int64_t &x, int64_t &y) {
        if (b == 0) {
            g = a; x = 1; y = 0;
            return;
        }
        int64_t dp, xp, yp;
        ext_gcd(b, a % b, dp, xp, yp);
        g = dp;
        x = yp;
        y = xp - a / b * yp;
    }

    // find x that a*x = b mod n
    static int64_t mod_solve(int64_t a, int64_t b, int64_t n) {
        int64_t d, xp, yp;
        ext_gcd(a, n, d, xp, yp);
        if (b % d == 0) {
            int64_t x0 = (mul_long(xp, b/d, n) + n) % n;
            return x0;
        } else {
            abort();
        }
    }
};

const int64_t MOD = 999911659;
int64_t N;
int P;
int64_t dp[510][510][10];
int64_t INV[10];
int64_t C[510][10];
int ALLONES;

struct Data {
    int r;
    int64_t cnt;
};
vector<Data> D;

void cycle(const vector<int> &r, int x) {
    vector<int64_t> cnt(P);
    int i = 0;
    for (; i < (int)r.size(); i++) {
        if (r[i] == x) break;
        cnt[r[i]] = 1;
    }
    int l = r.size() - i;
    for (; i < (int)r.size(); i++) {
        int64_t k = (N-1-i)/l + 1;
        cnt[r[i]] = k;
        if ((N-1-i) % l == 0) ALLONES = r[i];
    }

    for (i = 0; i < P; i++) {
        if (cnt[i] > 0) D.push_back({i, cnt[i]});
    }
}

void noCycle(const vector<int> &r) {
    for (int i = 0; i < N; i++) {
        D.push_back({r[i], 1});
    }
    ALLONES = r[N-1];
}

void build() {
    vector<bool> vis(P);
    vector<int> r;
    vector<int64_t> cnt(P);
    int x = 1 % P;
    while (!vis[x]) {
        vis[x] = true;
        r.push_back(x);
        x = (10*x + 1) % P;
    }
    if ((int)r.size() <= N) cycle(r, x);
    else noCycle(r);

    for (int i = 1; i < 10; i++) {
        INV[i] = ModularUtils::mod_solve(i, 1, MOD);
    }
    for (int i = 0; i < (int)D.size(); i++) {
        C[i][0] = 1;
        int64_t c = D[i].cnt;
        for (int j = 1; j < 10; j++) {
            C[i][j] = (C[i][j-1] * ((c+j-1)%MOD)) % MOD;
            C[i][j] = (C[i][j] * INV[j]) % MOD;
        }
    }
}

int main() {
    cin >> N >> P;
    vector<int> pos(P+1);
    build();
    dp[0][0][0] = 1;
    for (int i = 1; i <= (int)D.size(); i++) {
        int r = D[i-1].r;
        for (int j = 0; j < P; j++) {
            for (int k = 0; k < 9; k++) {
                for (int l = 0; l <= k; l++) {
                    dp[i][j][k] +=
                        (dp[i-1][(P+j-r*l%P)%P][k-l] * C[i-1][l]) % MOD;
                    dp[i][j][k] %= MOD;
                }
            }
        }
    }
    int64_t ans = 0;
    for (int i = 0; i < 9; i++) {
        (ans += dp[D.size()][(P-ALLONES)%P][i]) %= MOD;
    }
    cout << ans << endl;

    return 0;
}
