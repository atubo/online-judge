// https://www.luogu.org/problemnew/show/P4170
// [CQOI2007]涂色

#include <bits/stdc++.h>
using namespace std;

string S;

int dp[52][52];

int solve(int p, int q) {
    if (q < p) return 0;
    if (q == p) return 1;
    if (dp[p][q] > 0) return dp[p][q];
    int &ret = dp[p][q];
    ret = 1 + solve(p+1, q);
    for (int x = q; x > p; x--) {
        if (S[x] == S[p]) {
            ret = min(ret, 1 + solve(p+1, x-1) + solve(x+1, q));
            for (int y = x-1; y > p; y--) {
                if (S[y] == S[p]) {
                    ret = min(ret, solve(p, y) + solve(y+1, x-1) + solve(x+1, q));
                }
            }
        }
    }
    return ret;
}

void dedup(string &s) {
    string ret;
    ret.push_back(s[0]);
    for (int i = 1; i < (int)s.length(); i++) {
        if (s[i] != ret.back()) ret.push_back(s[i]);
    }
    swap(s, ret);
}

int main() {
    cin >> S;
    dedup(S);
    const int n = S.length();
    int ans = solve(0, n-1);
    printf("%d", ans);
    return 0;
}
