// https://www.luogu.org/problemnew/show/P4052
// [JSOI2007]文本生成器

#include <bits/stdc++.h>
using namespace std;

class AhoCorasick {
    static constexpr const char *ALPHABET = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    static const int ALPHA_SIZE = strlen(ALPHABET);
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
            int c = s[i] - ALPHABET[0];
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
            int c = t[i] - ALPHABET[0];
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

    int followDictSuffixLink(int q) const {
        int res = 0;
        while (q != 0) {
            res += out[q].size();
            q = next[q];
        }
        return res;
    }
};

const int MOD = 10007;
int N, M;

int solve(const AhoCorasick &ac) {
    vector<int> dp1(ac.sz), dp2(ac.sz);
    dp1[0] = 1;
    int tot = 1;
    for (int i = 1; i <= M; i++) {
        (tot *= 26) %= MOD;
        for (int j = 0; j < ac.sz; j++) {
            if (dp1[j] > 0) {
                for (int c = 0; c < 26; c++) {
                    int k = j;
                    while (k != -1 && ac.to[k][c] == 0) {
                        k = ac.link[k];
                    }
                    if (k != -1) k = ac.to[k][c];
                    else k = 0;
                    if (!ac.followDictSuffixLink(k)) {
                        (dp2[k] += dp1[j]) %= MOD;
                    }
                }
            }
        }
        swap(dp1, dp2);
        dp2.assign(ac.sz, 0);
    }
    int ans = accumulate(dp1.begin(), dp1.end(), 0) % MOD;
    ans = (tot - ans + MOD) % MOD;

    return ans;
}

int main() {
    scanf("%d%d", &N, &M);
    int tot = 0;
    vector<string> words(N);
    for (int i = 0; i < N; i++) {
        cin >> words[i];
        tot += words[i].length();
    }
    AhoCorasick ac(tot);
    for (int i = 0; i < N; i++) {
        ac.add_str(words[i]);
    }
    ac.push_links();
    printf("%d", solve(ac));
    return 0;
}
