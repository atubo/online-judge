// https://www.luogu.org/problem/CF786B
// Legacy

#include <bits/stdc++.h>
using namespace std;

using PII = pair<int64_t, int>;
const int64_t INF = 0x3f3f3f3f3f3f3f3f;

// note it's 1-indexed
class SegmentTree1 {
    int N;
    int64_t *val, *lazy;
    int *pos;

public:
    SegmentTree1(int N_): N(N_) {
        val = new int64_t[4*N+1]{};
        lazy = new int64_t[4*N+1]{};
        memset(val, 0x3f, (4*N+1)*sizeof(int64_t));
        memset(lazy, 0x3f, (4*N+1)*sizeof(int64_t));
        pos = new int[4*N+1]{};
    }

    ~SegmentTree1() {
        delete[] val;
        delete[] lazy;
        delete[] pos;
    }

    void update(int64_t t, int a, int b) {
        update(1, t, 1, N, a, b);
    }

    void set(int a) {
        set(1, 1, N, a);
    }

    PII query(int a, int b) {
        return query(1, 1, N, a, b);
    }

private:
    void merge(int k) {
        if (val[2*k+1] < val[2*k]) {
            val[k] = val[2*k+1];
            pos[k] = pos[2*k+1];
        } else {
            val[k] = val[2*k];
            pos[k] = pos[2*k];
        }
    }

    void update(int k, int64_t t, int l, int r, int a, int b) {
        if (a > b) return;
        pushDown(k, l, r);
        if (a <= l && r <= b) {
            if (t < val[k]) {
                val[k] = t;
                pos[k] = l;
            }
            lazy[k] = min(lazy[k], t);
            return;
        }
        if (l == r) return;
        int mid = (l + r) / 2;
        if (a <= mid) update(2*k,   t, l, mid, a, b);
        if (mid < b)  update(2*k+1, t, mid+1, r, a, b);
        merge(k);
    }

    void set(int k, int l, int r, int a) {
        pushDown(k, l, r);
        if (l == r) {
            lazy[k] = val[k] = INF;
            pos[k] = l;
            return;
        }

        int mid = (l + r) / 2;
        if (a <= mid) set(2*k, l, mid, a);
        else set(2*k+1, mid+1, r, a);
        merge(k);
    }

    void pushDown(int k, int l, int r) {
        if (l == r) return;
        lazy[2*k] = min(lazy[2*k], lazy[k]);
        lazy[2*k+1] = min(lazy[2*k+1], lazy[k]);
        int mid = (l + r) / 2;
        if (lazy[2*k] < val[2*k]) {
            val[2*k] = lazy[2*k];
            pos[2*k] = l;
        }
        if (lazy[2*k+1] < val[2*k+1]) {
            val[2*k+1] = lazy[2*k+1];
            pos[2*k+1] = mid+1;
        }
        lazy[k] = INF;
    }

    PII query(int k, int l, int r, int a, int b) {
        if (!k) return make_pair(INF, -1);
        if (b < l || a > r) return make_pair(INF, -1);
        pushDown(k, l, r);
        if (a <= l && r <= b) return make_pair(val[k], pos[k]);
        PII ret = make_pair(INF, -1);
        int mid = (l + r) / 2;
        if (a <= mid) {
            auto ret1 = query(2*k, l, mid, a, b);
            if (ret1.first < ret.first) ret = ret1;
        }
        if (mid < b) {
            auto ret2 = query(2*k+1, mid+1, r, a, b);
            if (ret2.first < ret.first) ret = ret2;
        }
        return ret;
    }
};

// note it's 1-indexed
class SegmentTree2 {
    int N;
    set<int>* val_;

public:
    SegmentTree2(int N_): N(N_) {
        val_ = new set<int>[4*N+1]{};
    }

    ~SegmentTree2() {
        delete[] val_;
    }
    // add t to range [a, b]
    void update(int t, int a, int b) {
        update(1, t, 1, N, a, b);
    }

    vector<int> query(int a) {
        vector<int> ret;
        query(1, 1, N, a, ret);
        return ret;
    }

private:
    // add t to range [a, b], current node range is [l, r]
    void update(int k, int t, int l, int r, int a, int b) {
        if (a > b) return;
        if (a <= l && r <= b) {
            val_[k].insert(t);
            return;
        }
        if (l == r) return;
        int mid = (l + r) / 2;
        if (a <= mid) update(2*k,   t, l, mid, a, b);
        if (mid < b)  update(2*k+1, t, mid+1, r, a, b);
    }

    void query(int k, int l, int r, int a, vector<int> &ret) {
        if (!k) return;
        if (a < l || a > r) return;
        for (int x: val_[k]) ret.push_back(x);
        val_[k].clear();
        if (l == r) return;
        int mid = (l + r) / 2;
        if (a <= mid) query(2*k, l, mid, a, ret);
        else query(2*k+1, mid+1, r, a, ret);
    }
};

const int MAXN = 100010;
int N, Q, S;
int64_t D[MAXN];
bool vis[MAXN];
struct Plan {
    int l, r, w;
};
vector<vector<PII>> P1(MAXN);
vector<vector<Plan>> P2(MAXN);
vector<PII> P3;

void dijkstra(SegmentTree2 &st2) {
    memset(D, -1, sizeof(D));
    SegmentTree1 st1(N);
    st1.update(0, S, S);
    while (true) {
        auto ret = st1.query(1, N);
        if (ret.first == INF) break;
        int u = ret.second;
        if (vis[u]) {
            st1.set(u);
            continue;
        }
        D[u] = ret.first;
        vis[u] = true;
        for (int i = 0; i < (int)P1[u].size(); i++) {
            int v = P1[u][i].second;
            int64_t w = P1[u][i].first;
            st1.update(D[u]+w, v, v);
        }

        for (int i = 0; i < (int)P2[u].size(); i++) {
            int l = P2[u][i].l;
            int r = P2[u][i].r;
            int w = P2[u][i].w;
            st1.update(D[u]+w, l, r);
        }

        auto id = st2.query(u);
        for (int i: id) {
            int w = P3[i].first;
            int v = P3[i].second;
            st1.update(D[u]+w, v, v);
        }
        st1.set(u);
    }
    for (int i = 1; i <= N; i++) {
        printf("%I64d ", D[i]);
    }
}

int main() {
    scanf("%d%d%d", &N, &Q, &S);
    SegmentTree2 st2(N);
    int t, u, v, w, l, r;
    for (int i = 0; i < Q; i++) {
        scanf("%d", &t);
        if (t == 1) {
            scanf("%d%d%d", &u, &v, &w);
            P1[u].push_back(make_pair(int64_t(w), v));
        } else if (t == 2) {
            scanf("%d%d%d%d", &u, &l, &r, &w);
            P2[u].push_back({l, r, w});
        } else {
            scanf("%d%d%d%d", &u, &l, &r, &w);
            int id = P3.size();
            P3.push_back(make_pair(int64_t(w), u));
            st2.update(id, l, r);
        }
    }
    dijkstra(st2);
    return 0;
}
