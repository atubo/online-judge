// https://www.luogu.org/problemnew/show/P3118
// [USACO15JAN]电影移动Moovie Mooving

#include <bits/stdc++.h>
using namespace std;

struct Movie {
    int s, e;
    bool operator < (const Movie &other) const {
        if (e != other.e) return e < other.e;
        return s < other.s;
    }
};

int N, L;
vector<vector<Movie>> M;
int dp[1<<20];
int dp2[1<<20];

int main() {
    scanf("%d%d", &N, &L);
    M.resize(N);
    vector<int> sorted{0, L};
    for (int i = 0; i < N; i++) {
        int d, c;
        scanf("%d%d", &d, &c);
        M[i].resize(c);
        for (int j = 0; j < c; j++) {
            int s;
            scanf("%d", &s);
            M[i][j] = {s, s+d};
            sorted.push_back(s);
            sorted.push_back(s+d);
        }
    }

    sort(sorted.begin(), sorted.end());
    sorted.erase(unique(sorted.begin(), sorted.end()), sorted.end());

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < (int)M[i].size(); j++) {
            M[i][j].s = lower_bound(sorted.begin(), sorted.end(),
                                    M[i][j].s) - sorted.begin();
            M[i][j].e = lower_bound(sorted.begin(), sorted.end(),
                                    M[i][j].e) - sorted.begin();
        }
    }
    L = lower_bound(sorted.begin(), sorted.end(), L) - sorted.begin();

    vector<vector<int>> nxt(N);
    for (int i = 0; i < N; i++) {
        nxt[i].resize(sorted.size(), -1);
        sort(M[i].begin(), M[i].end());
        int curr = INT_MAX;
        for (int j = (int)M[i].size()-1; j >= 0; j--) {
            curr = min(M[i][j].e, curr);
            while (curr >= M[i][j].s) {
                nxt[i][curr] = M[i][j].e;
                curr--;
            }
        }
    }

    memset(dp, -1, sizeof(dp));
    dp[0] = 0;

    int ans = INT_MAX;
    for (int s = 1; s < (1<<N); s++) {
        int t = s;
        while (t > 0) {
            int d = __builtin_ctz(t);
            t = t & (t-1);
            int last = dp[s-(1<<d)];
            if (last == -1) continue;
            int nt = nxt[d][last];
            if (nt >= 0) dp[s] = max(dp[s], nt);
        }
        if (dp[s] >= L) {
            ans = min(ans, __builtin_popcount(s));
        }
    }
    printf("%d\n", (ans == INT_MAX ? -1 : ans));
    return 0;
}
