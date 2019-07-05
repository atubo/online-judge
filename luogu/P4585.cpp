// https://www.luogu.org/problemnew/show/P4585
// [FJOI2015]火星商店问题

#include <bits/stdc++.h>
using namespace std;

struct Query {
    int id, l, r, x;
};

struct Node {
    int t, p, v;
    bool operator < (const Node& other) const {
        if (p != other.p) return p < other.p;
        if (t != other.t) return t < other.t;
        return v < other.v;
    }
};

const int MAXN = 100010;
const int LOG = 17;
int ch[MAXN*LOG*2][2];
vector<Query> Q[MAXN*4];
vector<Node> ND[MAXN*4];

class SegmentTreeDivideConquer {
public:

    SegmentTreeDivideConquer(int m): m_(m) {
        alloc();
    }

    ~SegmentTreeDivideConquer() {
        dealloc();
    }

    void addQuery(int a, int b, const Query &q) {
        if (a > b) return;
        addQuery(1, 1, m_, a, b, q);
    }

    void insert(int pos, int v) {
        rt_[pos] = 0;
        insert(rt_[pos], rt_[pos-1], v);
    }

    void solve(int x, int l, int r) {
        if (ND[x].size() == 0) return;
        tmp_[0] = totp_ = 0;
        tmp_[++tmp_[0]] = 0;
        rt_[1] = 0;
        int mid = (l + r) / 2;
        for (int i = 0; i < (int)(ND[x].size()); i++) {
            tmp_[++tmp_[0]] = ND[x][i].p;
            rt_[tmp_[0]] = 0;
            insert(rt_[tmp_[0]], rt_[tmp_[0]-1], ND[x][i].v);
            if (l == r) continue;
            if (ND[x][i].t <= mid) ND[2*x].push_back(ND[x][i]);
            else ND[2*x+1].push_back(ND[x][i]);
        }

        for (int i = 0; i < (int)Q[x].size(); i++) {
            int L = upper_bound(tmp_+1, tmp_+tmp_[0]+1, Q[x][i].l-1)
                - tmp_ - 1;
            int R = upper_bound(tmp_+1, tmp_+tmp_[0]+1, Q[x][i].r)
                - tmp_ - 1;
            ans_[Q[x][i].id] = max(ans_[Q[x][i].id],
                                          query(rt_[L], rt_[R],
                                                Q[x][i].x));
        }
        if (l == r) return;
        solve(2*x, l, mid);
        solve(2*x+1, mid+1, r);
    }

    int query(int lc, int rc, int v) {
        int ans = 0;
        for (int i = LOG-1; i >= 0; i--) {
            ans <<= 1;
            int t = (v >> i) & 1;
            if (sum_[ch[rc][t^1]] - sum_[ch[lc][t^1]] > 0) {
                lc = ch[lc][t^1];
                rc = ch[rc][t^1];
                ans ^= 1;
            } else {
                lc = ch[lc][t];
                rc = ch[rc][t];
            }
        }
        return ans;
    }

    const int m_;
    int *ans_;
    int *rt_;
private:
    int *sum_;
    int totp_ = 0;
    int *tmp_;

    void alloc() {
        sum_ = new int[4*MAXN*LOG]{};
        tmp_ = new int[MAXN]{};
        rt_ = new int[MAXN]{};
        ans_ = new int[MAXN]{};
    }

    void dealloc() {
        delete[] sum_;
        delete[] tmp_;
        delete[] rt_;
        delete[] ans_;
    }

    void insert(int &x, int pre, int v) {
        int now = x = ++totp_;
        for (int i = LOG-1; i >= 0; i--) {
            int t = (v >> i) & 1;
            ch[now][t] = ++totp_;
            ch[now][t^1] = ch[pre][t^1];
            sum_[now] = sum_[pre] + 1;
            now = ch[now][t];
            pre = ch[pre][t];
        }
        sum_[now] = sum_[pre] + 1;
    }

    void addQuery(int x, int l, int r, int a, int b, const Query &q) {
        if (b < l || a > r) return;
        if (a <= l && r <= b) {
            Q[x].push_back(q);
            return;
        }
        int mid = (l + r) / 2;
        if (a <= mid) addQuery(2*x, l, mid, a, b, q);
        if (b >= mid+1) addQuery(2*x+1, mid+1, r, a, b, q);
    }
};

int N, M;

int main() {
    int tott = 0, totq = 0;
    scanf("%d%d", &N, &M);
    SegmentTreeDivideConquer st(M);
    for (int i = 1; i <= N; i++) {
        int a;
        scanf("%d", &a);
        st.insert(i, a);
    }
    int op, L, R, x, d, s, v;
    for (int i = 0; i < M; i++) {
        scanf("%d", &op);
        if (op == 0) {
            scanf("%d%d", &s, &v);
            tott++;
            ND[1].push_back({tott, s, v});
        } else {
            scanf("%d%d%d%d", &L, &R, &x, &d);
            ++totq;
            st.addQuery(tott-d+1, tott, {totq, L, R, x});
            st.ans_[totq] = st.query(st.rt_[L-1], st.rt_[R], x);
        }
    }
    sort(ND[1].begin(), ND[1].end());

    st.solve(1, 1, M);
    for (int i = 1; i <= totq; i++) {
        printf("%d\n", st.ans_[i]);
    }

    return 0;
}
