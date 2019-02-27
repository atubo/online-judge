// https://www.luogu.org/problemnew/show/P1446
// [HNOI2008]Cards

#include <bits/stdc++.h>

using namespace std;

// (g, x, y) that a*x + b*y = g
void ext_gcd(int64_t a, int64_t b, int64_t &g, int64_t &x, int64_t &y) {
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
int64_t mod_solve(int64_t a, int64_t b, int n) {
    int64_t d, xp, yp;
    ext_gcd(a, n, d, xp, yp);
    if (b % d == 0) {
        int64_t x0 = (xp * (b / d) % n + n) % n;
        return x0;
    } else {
        abort();
    }
}

const int MAXN = 65;
int Sr, Sb, Sg, M, P;
int N;
int permutation[MAXN], vis[MAXN];
int dp[22][22][22];

int add(int a, int b) {
    return (a + b) % P;
}

int solve(int pos, int r, int b, int g, const vector<int> &partition) {
    if (pos == (int)partition.size()) return 1;
    if (dp[r][b][g] != -1) return dp[r][b][g];
    int &ret = dp[r][b][g] = 0;
    if (r >= partition[pos]) {
        ret = add(ret, solve(pos+1, r-partition[pos], b, g, partition));
    }
    if (b >= partition[pos]) {
        ret = add(ret, solve(pos+1, r, b-partition[pos], g, partition));
    }
    if (g >= partition[pos]) {
        ret = add(ret, solve(pos+1, r, b, g-partition[pos], partition));
    }
    return ret;
}

vector<int> getPartition() {
    memset(vis, 0, sizeof(vis));
    vector<int> ret;
    for (int i = 0; i < N; i++) {
        if (!vis[i]) {
            int cnt = 0;
            int x = i;
            while (!vis[x]) {
                vis[x] = true;
                cnt++;
                x = permutation[x] - 1;
            }
            ret.push_back(cnt);
        }
    }
    return ret;
}

int main() {
   scanf("%d%d%d%d%d", &Sr, &Sb, &Sg, &M, &P);
   N = Sr + Sb + Sg;
   int ans = 0;
   for (int i = 0; i < M; i++) {
       for (int j = 0; j < N; j++) {
           scanf("%d", &permutation[j]);
       }
       vector<int> partition = getPartition();
       memset(dp, -1, sizeof(dp));
       ans = (ans + solve(0, Sr, Sb, Sg, partition)) % P;
   }
   vector<int> iden(N, 1);
   memset(dp, -1, sizeof(dp));
   ans = (ans + solve(0, Sr, Sb, Sg, iden)) % P;
   int64_t inv = mod_solve(M+1, 1, P);
   inv = (inv % P + P) % P;
   assert(ans >= 0);
   assert(inv >= 0);
   ans = (ans * inv) % P;
   printf("%d\n", ans);

   return 0;
} 
