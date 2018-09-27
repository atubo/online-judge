// https://www.luogu.org/problemnew/show/P3303
// [SDOI2013]淘金

#include <bits/stdc++.h>
using namespace std;

using Map = unordered_map<int64_t, int64_t>;
Map* dp[20];

Map* solve(const string &s, int d, bool clamp) {
    const int n = s.length();
    if (d == -1) return NULL;
    if (!clamp && dp[d]) return dp[d];
    Map *ret = new Map();
    int maxx = (clamp ? s[n-1-d]-'0' : 9);
    for (int x = 1; x <= maxx; x++) {
        bool nc = (clamp && x == s[n-1-d]-'0');
        Map *nxt = solve(s, d-1, nc);
        if (nxt) {
            for (auto it = nxt->begin(); it != nxt->end(); ++it) {
                (*ret)[1LL*x*it->first] += it->second;
            }
        } else {
            (*ret)[x]++;
        }
    }
    if (!clamp) dp[d] = ret;
    return ret;
}

void merge(Map *m, Map *m2) {
    for (auto it = m2->begin(); it != m2->end(); ++it) {
        (*m)[it->first] += it->second;
    }
}

Map* solve(const string &s) {
    Map *m = solve(s, s.length()-1, true);
    for (int i = s.length()-1; i >= 1; i--) {
        string s2(i, '9');
        merge(m, solve(s2, i-1, true));
    }
    return m;
}

const int MOD = 1000000007;
int add(int64_t a, int64_t b) {
    return (a + b) % MOD;
}

int mul(int64_t a, int64_t b) {
    return (a * b) % MOD;
}

void solve(Map *m, int64_t k) {
    map<int64_t, int> cnt;
    for (auto it = m->begin(); it != m->end(); ++it) {
        cnt[it->second]++;
    }
    const int n = cnt.size();
    vector<int> X(n), Y(n);
    int idx = 0;
    for (auto it = cnt.rbegin(); it != cnt.rend(); ++it, ++idx) {
        X[idx] = it->first;
        Y[idx] = it->second;
    }
    vector<int> prog(n, 0);
    using Pair = pair<int64_t, int>;
    priority_queue<Pair> pq;
    for (int i = 0; i < n; i++) {
        pq.push(make_pair(1LL*X[i]*X[0], i));
    }

    int ans = 0;
    while (k > 0 && !pq.empty()) {
        int64_t r;
        tie(r, idx) = pq.top();
        pq.pop();
        int p = prog[idx];
        int64_t cnt_prod = 1LL * Y[idx] * Y[p];
        if (k > cnt_prod) {
            k -= cnt_prod;
            ans = add(ans, mul(cnt_prod%MOD, r%MOD));
            if (p < n-1) {
                prog[idx] = ++p;
                pq.push(make_pair(1LL*X[idx]*X[p], idx));
            }
        } else {
            ans = add(ans, mul(k%MOD, r%MOD));
            k = 0;
        }
    }
    printf("%d\n", ans);
}

int main() {
    string s;
    int64_t k;
    cin >> s >> k;
    Map *m = solve(s);

    solve(m, k);
    return 0;
}
