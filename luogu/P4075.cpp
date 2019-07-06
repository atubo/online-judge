// https://www.luogu.org/problemnew/show/P4075
// [SDOI2016]模式字符串

#include <bits/stdc++.h>
using namespace std;

const int BASE = 233;
const int MOD = 998244353;
const int MAXN = 1000010;
int N, M;
int64_t HASH1[MAXN], HASH2[MAXN];
int P[MAXN];

class GravityTree {
    struct Edge {
        int next, to;
    };
public:
    GravityTree(int n): n_(n) {
        alloc();
    }

    ~GravityTree() {
        dealloc();
    }

    void solve(int u) {
        dfs1(u, -1);
        if (sz_[u] == 1) {
            cut_[u] = true;
            return;
        }

        tot_ = sz_[u];
        miv_ = INF;
        dfs2(u, -1);
        cut_[rt_] = true;

        G_[0] = F_[0] = 1;
        maxd2_ = 0;
        for (int eidx = head_[rt_]; ~eidx; eidx = E_[eidx].next) {
            int v = E_[eidx].to;
            if (cut_[v]) continue;
            maxd1_ = 0;
            dfs3(v, rt_, s_[rt_], 1);
            int m = min(M-1, maxd1_);
            maxd2_ = max(maxd2_, maxd1_);
            for (int j = 0; j <= m; j++) {
                G_[j] += gx_[j];
                F_[j] += fx_[j];
                fx_[j] = gx_[j] = 0;
            }
        }

        for (int i = 0; i <= maxd2_; i++) G_[i] = F_[i] = 0;

        for (int eidx = head_[rt_]; ~eidx; eidx = E_[eidx].next) {
            int v = E_[eidx].to;
            if (!cut_[v]) solve(v);
        }
    }

    void addEdge(int u, int v) {
        E_[eidx_].to = v;
        E_[eidx_].next = head_[u];
        head_[u] = eidx_++;
        E_[eidx_].to = u;
        E_[eidx_].next = head_[v];
        head_[v] = eidx_++;
    }

    int *s_;
    int64_t ans = 0;
private:
    static const int INF = 0x3F3F3F3F;
    const int n_;
    int *sz_;
    bool *cut_;
    int tot_;
    int miv_;
    int rt_;
    int *fx_, *gx_;
    int *G_, *F_;
    int maxd1_ = 0, maxd2_ = 0;
    Edge *E_;
    int *head_;
    int eidx_ = 0;

    void alloc() {
        sz_ = new int[n_]{};
        cut_ = new bool[n_]{};
        s_ = new int[n_]{};
        fx_ = new int[n_]{};
        gx_ = new int[n_]{};
        G_ = new int[n_]{};
        F_ = new int[n_]{};
        head_ = new int[n_]{};
        memset(head_, -1, n_*sizeof(int));
        E_ = new Edge[2*(n_-1)]{};
    }

    void dealloc() {
        delete[] sz_;
        delete[] cut_;
        delete[] s_;
        delete[] fx_;
        delete[] gx_;
        delete[] G_;
        delete[] F_;
        delete[] head_;
        delete[] E_;
    }

    void dfs1(int u, int f) {
        sz_[u] = 1;
        for (int eidx = head_[u]; ~eidx; eidx = E_[eidx].next) {
            int v = E_[eidx].to;
            if (v != f && !cut_[u]) {
                dfs1(v, u);
                sz_[u] += sz_[v];
            }
        }
    }

    void dfs2(int u, int f) {
        int mav = tot_ - sz_[u];
        for (int eidx = head_[u]; ~eidx; eidx = E_[eidx].next) {
            int v = E_[eidx].to;
            if (v != f && !cut_[v]) {
                dfs2(v, u);
                mav = (sz_[v] > mav ? sz_[v] : mav);
            }
        }
        if (miv_ > mav) {
            miv_ = mav;
            rt_ = u;
        }
    }

    void dfs3(int u, int f, int h, int d) {
        maxd1_ = max(maxd1_, d);
        h = (1LL*s_[u]*P[d] + h) % MOD;
        int t = d % M;
        if (h == HASH1[d]) {
            fx_[t]++;
            ans += G_[M-t-1];
        }
        if (h == HASH2[d]) {
            gx_[t]++;
            ans += F_[M-t-1];
        }

        for (int eidx = head_[u]; ~eidx; eidx = E_[eidx].next) {
            int v = E_[eidx].to;
            if (v != f && !cut_[v]) {
                dfs3(v, u, h, d+1);
            }
        }

    }
};

void hashstr(const string &s, int64_t *h) {
    h[0] = s[0] - 'A';
    for (int i = 1; i < (int)s.length(); i++) {
        int x = s[i] - 'A';
        h[i] = (h[i-1]*BASE + x) % MOD;
    }
}

int64_t solve() {
    scanf("%d%d", &N, &M);
    GravityTree gt(N);
    string s;
    cin >> s;
    for (int i = 0; i < N; i++) {
        gt.s_[i] = s[i] - 'A';
    }
    for (int i = 0; i < N-1; i++) {
        int u, v;
        scanf("%d%d", &u, &v);
        u--; v--;
        gt.addEdge(u, v);
    }

    string pat;
    cin >> pat;
    if (M > N) return 0;
    for (int i = M; i < N; i++) {
        pat.push_back(pat[i-M]);
    }
    hashstr(pat, HASH1);
    pat.erase(pat.begin()+M, pat.end());
    reverse(pat.begin(), pat.end());
    for (int i = M; i < N; i++) {
        pat.push_back(pat[i-M]);
    }
    hashstr(pat, HASH2);
    gt.solve(0);
    return gt.ans;
}


int main() {
    P[0] = 1;
    for (int i = 1; i <= MAXN; i++) {
        P[i] = (1LL * P[i-1] * BASE) % MOD;
    }
    int c;
    scanf("%d", &c);
    while (c--) {
        printf("%ld\n", solve());
    }
    return 0;
}
