// https://www.luogu.org/problemnew/show/P3311
// [SDOI2014]数数

#include <bits/stdc++.h>
using namespace std;

class AhoCorasick {
    static const int ALPHA_SIZE = 10;
public:
    const int n_;
    int **to;
    vector<set<int> > out;
    int sz = 1;
    int *link;  // blue link in the wiki
    int *next;  // green link in the wiki
    int *que;
    int keywordIndex;

    // n is total length, total number of nodes is at most n+1
    AhoCorasick(int n): n_(n+1), out(n_), keywordIndex(0) {
        to = new int*[n_]{};
        for (int i = 0; i < n_; i++) {
            to[i] = new int[ALPHA_SIZE]{};
        }

        link = new int[n_]{};
        next = new int[n_]{};
        que  = new int[n_]{};
    }

    ~AhoCorasick() {
        for (int i = 0; i < n_; i++) {
            delete[] to[i];
        }
        delete[] to;

        delete[] link;
        delete[] next;
        delete[] que;
    }

    void add_str(const string &s) {
        int v = 0;
        for(int i = 0; i < (int)s.length(); i++) {
            // TODO: deal with offset
            int c = s[i] - '0';
            if(!to[v][c]) to[v][c] = sz++;
            v = to[v][c];
        }
        out[v].insert(keywordIndex++);
    }

    void push_links() {
        link[0] = -1;
        int st = 0, fi = 1;
        que[0] = 0;
        while (st < fi) {
            int v = que[st++];
            for (int c = 0; c < ALPHA_SIZE; c++) {
                int u = to[v][c];
                if (u == 0) continue;
                int j = link[v];
                while(j != -1 && !to[j][c]) j = link[j];
                if(j != -1) link[u] = to[j][c];
                if (out[link[u]].empty()) {
                    next[u] = next[link[u]];
                } else {
                    next[u] = link[u];
                }
                que[fi++] = u;
            }
        }
    }

    int countTotalMatches(const string &t) {
        int result = 0;
        int q = 0;
        for (int i = 0; i < (int)t.length(); i++) {
            // TODO: dealing with offset
            int c = t[i] - '0';
            while (q != -1 && to[q][c] == 0) {
                q = link[q];
            }
            if (q != -1) {
                q = to[q][c];
                result += followDictSuffixLink(q);
            } else {
                q = 0;
            }
        }
        return result;
    }

private:
    int followDictSuffixLink(int q) {
        int res = 0;
        while (q != 0) {
            res += out[q].size();
            q = next[q];
        }
        return res;
    }
};

const int MOD = 1000000007;
string N;
int M;
vector<string> S;
int dp[1510][1210], dp2[1510][1210];
bool term[1510];

int add(int64_t a, int64_t b) {
    return (a + b) % MOD;
}

int solve(int k, int d, bool clamp, const AhoCorasick &ac) {
    if (d == (int)N.length()) return 1;

    if (!clamp && dp[k][d] >= 0) return dp[k][d];
    int ret = 0;

    int xmax = (clamp ? N[d]-'0' : 9);
    for (int x = 0; x <= xmax; x++) {
        int q = k;
        while (q != -1 && ac.to[q][x] == 0) {
            q = ac.link[q];
        }
        if (q != -1) q = ac.to[q][x];
        else q = 0;
        if (term[q]) continue;
        ret = add(ret, solve(q, d+1, clamp && x==xmax, ac));
    }
    if (!clamp) dp[k][d] = ret;
    return ret;
}

int solve(const AhoCorasick &ac) {
    int ret = 0;
    int xmax = N[0] - '0';
    for (int x = 1; x <= xmax; x++) {
        int k = ac.to[0][x];
        if (term[k]) continue;
        ret = add(ret, solve(k, 1, x==xmax, ac));
    }
    return ret;
}

int solve(const AhoCorasick &ac, int len) {
    int ret = 0;
    dp2[0][0] = 1;
    for (int d = 1; d <= len; d++) {
        for (int k = 0; k < ac.sz; k++) {
            if (dp2[k][d-1] == 0) continue;
            for (int x = (d==1? 1: 0); x <= 9; x++) {
                int q = k;
                while (q != -1 && ac.to[q][x] == 0) q = ac.link[q];
                if (q != -1) q = ac.to[q][x];
                else q = 0;
                if (term[q]) {
                    continue;
                }
                dp2[q][d] = add(dp2[q][d], dp2[k][d-1]);
            }
        }
        for (int k = 0; k < ac.sz; k++) {
            ret = add(ret, dp2[k][d]);
        }
    }
    return ret;
}


int main() {
    memset(dp, -1, sizeof(dp));
    cin >> N;
    cin >> M;
    S.resize(M);
    int tot = 0;
    for (int i = 0; i < M; i++) {
        cin >> S[i];
        tot += S[i].length();
    }

    AhoCorasick ac(tot);
    for (int i = 0; i < M; i++) {
        ac.add_str(S[i]);
    }
    ac.push_links();

    for (int i = 0; i < ac.sz; i++) {
        if (!ac.out[i].empty()) term[i] = true;
    }

    int ans = solve(ac);

    ans = add(ans, solve(ac, N.length()-1));
    printf("%d\n", ans);

    return 0;
}
