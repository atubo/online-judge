// https://www.luogu.org/problemnew/show/P2322
// [HNOI2006]最短母串问题

#include <bits/stdc++.h>
using namespace std;

int N;
int dist[15][15];
int dp[1<<12][13][13];

bool contains(const string &s, const string &t) {
    const int l1 = s.length();
    const int l2 = t.length();
    for (int i = 0; i <= l1-l2; i++) {
        if (s.substr(i, l2) == t) return true;
    }
    return false;
}

int overlap(const string &s, const string &t) {
    const int l1 = s.length();
    const int l2 = t.length();
    int l = min(l1, l2);
    int ret = 0;
    for (int i = 1; i <= l; i++) {
        if (s.substr(l1-i, i) == t.substr(0, i)) {
            ret = i;
        }
    }
    return ret;
}

void build(const vector<string> &str) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            if (i == j) continue;
            dist[i][j] = str[j].length() - overlap(str[i], str[j]);
        }
    }
}

int solve(const vector<string> &str, int b, int e, int s) {
    if (dp[s][b][e] >= 0) return dp[s][b][e];
    int &ret = dp[s][b][e] = INT_MAX;
    int s2 = (s & (~(1<<b)));
    if (s2 == (1<<e)) {
        ret = str[b].length() + dist[b][e];
    } else {
        int s2t = s2;
        while (s2t > 0) {
            int k = __builtin_ctz(s2t);
            s2t &= (~(1<<k));
            if (k == e) continue;
            int d = (str[b].length() - str[k].length() + dist[b][k])
                + solve(str, k, e, s2);
            ret = min(ret, d);
        }
    }
    return ret;
}

int minlen(const vector<string> &str, int k, int s) {
    if (__builtin_popcount(s) == 1) {
        int u = __builtin_ctz(s);
        return str[u].length();
    }
    int ans = INT_MAX;
    for (int e = 0; e < N; e++) {
        if (e == k || ((s >> e) & 1) == 0) continue;
        ans = min(ans, dp[s][k][e]);
    }
    return ans;
}

string cut(const vector<string> &str, int i, int j) {
    int d = dist[i][j];
    return str[j].substr(str[j].length()-d, d);
}

void dfs(const vector<string> &str,
         int d, int x, int s, int target, vector<int> &ret) {
    ret.push_back(x);
    if (d == N-1) {
        return;
    }

    s &= (~(1<<x));
    int kb = -1;
    string sb;
    for (int k = 0; k < N; k++) {
        if (k == x || ((s>>k) & 1) == 0) continue;
        if (minlen(str, k, s) ==
            target - (int)str[x].length() + (int)str[k].length() - dist[x][k]) {
            string sc = cut(str, x, k);
            if (kb == -1 || sc < sb) {
                kb = k;
                sb = sc;
            }
        }
    }

    dfs(str, d+1, kb, s,
        target-str[x].length()+str[kb].length()-dist[x][kb],
        ret);
}

int main() {
    scanf("%d", &N);
    vector<string> str(N);
    for (int i = 0; i < N; i++) {
        cin >> str[i];
    }
    sort(str.begin(), str.end());
    str.erase(unique(str.begin(), str.end()), str.end());
    sort(str.begin(), str.end(),
         [](const string &s1, const string &s2) -> bool {
         return s1.length() < s2.length();
         });

    N = str.size();

    vector<string> tmp;
    vector<bool> mark(N, false);
    for (int i = 0; i < N; i++) {
        for (int j = i+1; j < N; j++) {
            if (contains(str[j], str[i])) {
                mark[i] = true;
                break;
            }
        }
        if (!mark[i]) tmp.push_back(str[i]);
    }
    str.swap(tmp);

    N = str.size();
    if (N == 1) {
        printf("%s\n", str[0].c_str());
        return 0;
    }

    sort(str.begin(), str.end());

    build(str);

    const int ALL = (1<<N) - 1;
    int ans = 1000;
    memset(dp, -1, sizeof(dp));

    for (int u = 0; u < N; u++) {
        for (int v = 0; v < N; v++) {
            if (v == u) continue;
            int d = solve(str, u, v, ALL);
            ans = min(ans, d);
        }
    }

    vector<int> path;
    for (int i = 0; i < N; i++) {
        if (minlen(str, i, ALL) == ans) {
            dfs(str, 0, i, ALL, ans, path);
            break;
        }
    }

    string ms;
    ms += str[path[0]];
    for (int i = 1; i < N; i++) {
        int u = path[i-1];
        int v = path[i];
        int o = str[v].length() - dist[u][v];
        ms += str[v].substr(o, dist[u][v]);
    }
    cout << ms << endl;

    return 0;
}
