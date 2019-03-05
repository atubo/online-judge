// https://www.luogu.org/problemnew/show/P3121
// [USACO15FEB]审查（黄金）Censoring (Gold)

#include <bits/stdc++.h>
using namespace std;

const int MAXN = 100010;
int dp[MAXN][26];

class AhoCorasick {
    static constexpr const char *ALPHABET = "abcdefghijklmnopqrstuvwxyz";
    static const int ALPHA_SIZE = strlen(ALPHABET);
public:
    const int n_;
    int **to;
    int *out;
    int sz = 1;
    int *link;  // blue link in the wiki
    int *que;
    int keywordIndex;

    // n is total length, total number of nodes is at most n+1
    AhoCorasick(int n): n_(n+1), keywordIndex(0) {
        to = new int*[n_]{};
        for (int i = 0; i < n_; i++) {
            to[i] = new int[ALPHA_SIZE]{};
        }
        out = new int[n_]{};

        link = new int[n_]{};
        que  = new int[n_]{};
    }

    ~AhoCorasick() {
        for (int i = 0; i < n_; i++) {
            delete[] to[i];
        }
        delete[] to;
        delete[] out;

        delete[] link;
        delete[] que;
    }

    void add_str(const string &s) {
        int v = 0;
        for(int i = 0; i < (int)s.length(); i++) {
            int c = s[i] - ALPHABET[0];
            if(!to[v][c]) to[v][c] = sz++;
            v = to[v][c];
        }
        out[v] = s.length();
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
                que[fi++] = u;
            }
        }
    }

    int transition(int q, int c) {
        if (dp[q][c] >= 0) return dp[q][c];
        int &ret = dp[q][c];
        while (q != -1 && to[q][c] == 0) {
            q = link[q];
        }
        if (q != -1) {
            ret = to[q][c];
        } else {
            ret = 0;
        }
        return ret;
    }

    string censor(const string &s) {
        int len = s.length();
        string ret(len+1, '#');
        vector<int> states(len+1);
        int p = 0, q = 0;
        for (int i = 0; i < (int)s.length(); i++) {
            int c = s[i] - ALPHABET[0];
            q = transition(q, c);
            if (out[q]) {
                p -= out[q] - 1;
                q = states[p];
            } else {
                states[++p] = q;
                ret[p] = s[i];
            }
        }

        return ret.substr(1, p);
    }
};

int main() {
    memset(dp, -1, sizeof(dp));
    string s;
    cin >> s;
    int n;
    cin >> n;
    int tot = 0;
    vector<string> words(n);
    for (int i = 0; i < n; i++) {
        cin >> words[i];
        tot += words[i].length();
    }
    AhoCorasick ac(tot);
    for (int i = 0; i < n; i++) {
        ac.add_str(words[i]);
    }
    ac.push_links();
    auto ret = ac.censor(s);
    cout << ret << endl;
    return 0;
}
