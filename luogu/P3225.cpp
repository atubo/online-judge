// https://www.luogu.org/problemnew/show/P3225
// [HNOI2012]矿场搭建

#include <bits/stdc++.h>
using namespace std;

const int MAXN = 1010;
const int MAXM = 1010;

// Note graph node is 0-indexed
class Graph {
public:
    struct Edge {
        int next, to;
    } E[MAXM];

    int head[MAXN];
    int eidx;

    Graph() {
        reset(MAXN);
    }

    void reset(int n) {
        eidx = 0;
        for (int i = 0; i < n; i++) {
            head[i] = -1;
        }
    }

    // assume 0-indexed and no duplication
    void addEdge(int u, int v) {
        E[eidx].to = v;
        E[eidx].next = head[u];
        head[u] = eidx++;
    }
};

class TarjanArticulationPoint {
public:
    // m is the number of undirected edges
    TarjanArticulationPoint() {
        alloc();
    }

    ~TarjanArticulationPoint() {
        dealloc();
    }

    void solve(const Graph &g) {
        for (int i = 0; i < n_; i++) {
            if (!vis_[i]) {
                root_ = i;
                dfs(i, g);
            }
        }
    }

    void reset(int n) {
        n_ = n;
        tmpdfn_ = 0;
        memset(dfn_, 0, n*sizeof(int));
        memset(low_, 0, n*sizeof(int));
        memset(vis_, 0, n*sizeof(bool));
        memset(art_, 0, n*sizeof(bool));
    }

    bool *art_; // whether a node is articulation point
private:

    int n_;
    int *dfn_;
    int *low_;
    bool *vis_;
    int tmpdfn_ = 0;
    int root_ = 0;

    void alloc() {
        dfn_ = new int[MAXN]{};
        low_ = new int[MAXN]{};
        vis_ = new bool[MAXN]{};
        art_ = new bool[MAXN]{};
    }

    void dealloc() {
        delete[] dfn_;
        delete[] low_;
        delete[] vis_;
        delete[] art_;
    }

    void dfs(int u, const Graph &g) {
        dfn_[u] = low_[u] = tmpdfn_++;
        vis_[u] = true;
        int son = 0;
        for (int eidx = g.head[u]; ~eidx; eidx = g.E[eidx].next) {
            int v = g.E[eidx].to;
            if (!vis_[v]) {
                son++;
                dfs(v, g);
                low_[u] = min(low_[u], low_[v]);
                if (low_[v] >= dfn_[u]) {
                    if (u != root_) art_[u] = true;
                }
            } else {
                low_[u] = min(low_[u], dfn_[v]);
            }
        }
        if (u == root_ && son > 1) art_[u] = true;
    }
};

struct Tunnel {
    int u, v;
} tunnels[MAXM];

int visited[MAXN];

int M;

void dfs(const Graph &g, const TarjanArticulationPoint &ap,
         int u, int gid, int &cnt, int &cut) {
    visited[u] = gid;
    cnt++;
    for (int eidx = g.head[u]; ~eidx; eidx = g.E[eidx].next) {
        int v = g.E[eidx].to;
        if (visited[v] != gid && ap.art_[v]) {
            cut++;
            visited[v] = gid;
        }
        if (!visited[v] && !ap.art_[v]) {
            dfs(g, ap, v, gid, cnt, cut);
        }
    }
}

void dfs1(const Graph &g, int u, vector<int> &sb) {
    visited[u] = true;
    sb.push_back(u);
    for (int eidx = g.head[u]; ~eidx; eidx = g.E[eidx].next) {
        int v = g.E[eidx].to;
        if (!visited[v]) {
            dfs1(g, v, sb);
        }
    }
}

pair<int, int64_t> solveSubgraph(const Graph &g,
                                 const TarjanArticulationPoint &ap,
                                 const vector<int> &sg) {
    int first = 0;
    int64_t second = 1;
    int gid = 0;
    for (int i: sg) {
        if (!ap.art_[i] && !visited[i]) {
            gid++;
            int cnt = 0;
            int cut = 0;
            dfs(g, ap, i, gid, cnt, cut);
            if (cut == 0) {
                first += 2;
                second *= cnt*(cnt-1)/2;
            } else if (cut == 1) {
                first++;
                second *= cnt;
            }
        }
    }
    return make_pair(first, second);
}

pair<int, int64_t> solve(const Graph &g, const TarjanArticulationPoint &ap,
                         int n) {
    vector<vector<int>> subgraphs;
    memset(visited, 0, n*sizeof(int));
    for (int i = 0; i < n; i++) {
        if (!visited[i]) {
            subgraphs.push_back(vector<int>());
            dfs1(g, i, subgraphs.back());
        }
    }
    memset(visited, 0, n*sizeof(int));
    pair<int, int64_t> ret(0, 1);
    for (const auto &sg: subgraphs) {
        auto curr = solveSubgraph(g, ap, sg);
        ret.first += curr.first;
        ret.second *= curr.second;
    }
    return ret;
}


int main() {
    Graph g;
    TarjanArticulationPoint ap;
    int case_num = 0;
    while (scanf("%d", &M) && M) {
        case_num++;
        vector<int> nodes;
        for (int i = 0; i < M; i++) {
            int u, v;
            scanf("%d%d", &u, &v);
            tunnels[i] = {u, v};
            nodes.push_back(u);
            nodes.push_back(v);
        }
        sort(nodes.begin(), nodes.end());
        nodes.erase(unique(nodes.begin(), nodes.end()), nodes.end());
        int n = nodes.size();
        g.reset(n);
        for (int i = 0; i < M; i++) {
            int u = lower_bound(nodes.begin(), nodes.end(), tunnels[i].u)
                - nodes.begin();
            int v = lower_bound(nodes.begin(), nodes.end(), tunnels[i].v)
                - nodes.begin();
            g.addEdge(u, v);
            g.addEdge(v, u);
        }
        ap.reset(n);
        ap.solve(g);

        auto ret = solve(g, ap, n);
        printf("Case %d: %d %ld\n", case_num, ret.first, ret.second);
    }

    return 0;
}
