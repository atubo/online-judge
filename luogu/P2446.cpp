// https://www.luogu.org/problemnew/show/P2446
// [SDOI2010]大陆争霸

#include <bits/stdc++.h>
using namespace std;

// Note graph node is 0-indexed
class Graph {
public:
    struct Edge {
        int next, to, wt;
    };

    vector<int> head;
    int eidx;
    int N, M;

    Edge *E;

    Graph(int N_, int M_):N(N_), M(M_) {
        head.resize(N);
        eidx = 0;

        for (int i = 0; i < N; i++) {
            head[i] = -1;
        }

        E = new Edge[M]{};
    }

    ~Graph() {
        delete[] E;
    }

    // assume 0-indexed and no duplication
    void addEdge(int u, int v, int w) {
        E[eidx].to = v;
        E[eidx].next = head[u];
        E[eidx].wt = w;
        head[u] = eidx++;
    }
};

const int64_t INF = 1e18;

// segment tree with single point update and range query
// 0-indexed
class SegmentTreeSPU {
    static const int64_t NULL_VALUE = 0;
public:
    SegmentTreeSPU(int n) {
        nData_ = 1;
        while (nData_ < n) nData_ = nData_ << 1;
        int sz = 2 * nData_ + 1;
        data = new int64_t[sz];
        for (int i = 0; i < sz; i++) data[i] = INF;
    }

    ~SegmentTreeSPU() {
        delete[] data;
    }

    void update(int i, int64_t value) {
        i += nData_;
        data[i] = value;
        for (; i > 1; i >>= 1) {
            int64_t newVal = combine(data[i], data[i^1]);
            if (data[i>>1] == newVal) break;
            data[i>>1] = newVal;
        }
    }

    int64_t query(int a, int b) const {
        a += nData_;
        b += nData_;
        int64_t res = NULL_VALUE;
        for (; a <= b; a = (a+1) >> 1, b = (b-1) >> 1) {
            if ((a & 1) != 0) {
                res = combine(res, data[a]);
            }
            if ((b & 1) == 0) {
                res = combine(res, data[b]);
            }
        }
        return res;
    }

private:
    int64_t *data;
    int nData_;
    int64_t combine(int64_t a, int64_t b) const {
        return max(a, b);
    }
};

const int MAXN = 3010;
struct Range {
    int l, r;
} ranges[MAXN];

int N, M;
int64_t dist1[MAXN], dist2[MAXN], dist3[MAXN];
bool inq[MAXN];

int64_t spfa(SegmentTreeSPU &st, const Graph &g1, const Graph &g2) {
    queue<int> q;
    q.push(0);
    inq[0] = true;
    while (!q.empty()) {
        int u = q.front();
        int64_t du = dist3[u];
        q.pop();
        inq[u] = false;
        for (int eidx = g1.head[u]; ~eidx; eidx = g1.E[eidx].next) {
            int v = g1.E[eidx].to;
            int w = g1.E[eidx].wt;
            dist1[v] = min(dist1[v], du + w);
            if (dist3[v] > max(dist1[v], dist2[v])) {
                dist3[v] = max(dist1[v], dist2[v]);
                if (!inq[v]) {
                    q.push(v);
                    inq[v] = true;
                }
            }
        }
        for (int eidx = g2.head[u]; ~eidx; eidx = g2.E[eidx].next) {
            int v = g2.E[eidx].to;
            st.update(eidx, dist3[u]);
            int64_t new_value = st.query(ranges[v].l, ranges[v].r-1);
            dist2[v] = min(dist2[v], new_value);
            if (dist3[v] > max(dist1[v], dist2[v])) {
                dist3[v] = max(dist1[v], dist2[v]);
                if (!inq[v]) {
                    q.push(v);
                    inq[v] = true;
                }
            }
        }
    }

    return dist3[N-1];
}

int main() {
    scanf("%d%d", &N, &M);
    Graph g1(N, M);
    for (int i = 0; i < M; i++) {
        int u, v, w;
        scanf("%d%d%d", &u, &v, &w);
        u--; v--;
        g1.addEdge(u, v, w);
    }

    vector<vector<int>> shields(N);
    int tot = 0;
    for (int i = 0; i < N; i++) {
        int l;
        scanf("%d", &l);
        for (int j = 0; j < l; j++) {
            int u;
            scanf("%d", &u);
            u--;
            shields[i].push_back(u);
        }
        tot += l;
    }

    Graph g2(N, tot);
    int curr = 0;
    for (int u = 0; u < N; u++) {
        ranges[u] = {curr, curr + (int)shields[u].size()};
        curr += shields[u].size();
        for (int v: shields[u]) {
            g2.addEdge(v, u, 0);
        }
    }

    SegmentTreeSPU st(tot);

    for (int i = 1; i < N; i++) {
        dist1[i] = dist3[i] = INF;
        dist2[i] = st.query(ranges[i].l, ranges[i].r-1);
    }

    int64_t ans = spfa(st, g1, g2);
    printf("%ld\n", ans);

    return 0;
}
