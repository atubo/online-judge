// https://www.luogu.org/problemnew/show/P3199
// [HNOI2009]最小圈

#include <bits/stdc++.h>
using namespace std;

// Determine if there is any negative weight loop
// Nodes in graph are 0-indexed
// Node N is a virtual node that has 0 weight edge to all nodes
// But we don't have to explicitly add that node
class SpfaDfs {
public:
    struct Edge {
        int next, to;
        double wt;
    };

    SpfaDfs(int n, int m): n_(n) {
        inq_ = new bool[n_]{};
        dist_ = new double[n_];
        vis_ = new bool[n_]{};
        head_ = new int[n_];
        e_total_ = 0;
        for (int i = 0; i < n_; i++) {
            head_[i] = -1;
        }
        e_ = new Edge[m]{};
    }

    ~SpfaDfs() {
        delete[] inq_;
        delete[] dist_;
        delete[] vis_;
        delete[] head_;
        delete[] e_;
    }

    void addEdge(int u, int v, double w) {
        e_[e_total_].to = v;
        e_[e_total_].next = head_[u];
        e_[e_total_].wt = w;
        head_[u] = e_total_++;
    }

    bool check(bool include_zero = false) {
        init();
        for (int i = 0; i < n_; i++) {
            //printf("in check u=%d\n", i+1);
            if (include_zero) memset(vis_, 0, n_*sizeof(bool));
            if (!dfs(i, include_zero)) return false;
        }
        return true;
    }
    Edge *e_;

private:
    int n_;
    bool *inq_;  // if node is in queue
    double *dist_;
    bool *vis_;

    int *head_;
    int e_total_;
    //Edge *e_;

    void init() {
        memset(inq_, 0, n_*sizeof(bool));
        memset(dist_, 0, n_*sizeof(double));
    }

    bool dfs(int u, bool include_zero) {
        //printf("in dfs u=%d inq=%d\n", u+1, inq_[u]);
        if (inq_[u]) return false;
        inq_[u] = 1;
        vis_[u] = true;
        //printf("dist[%d]=%f\n", u+1, dist_[u]);
        for (int eidx = head_[u]; eidx != -1; eidx = e_[eidx].next) {
            int v = e_[eidx].to;
            double w = e_[eidx].wt;
            if (include_zero && dist_[v] == dist_[u] + w && inq_[v]) return false;
            if (dist_[v] > dist_[u] + w ||
                (include_zero && dist_[v] == dist_[u] + w && !vis_[v])) {
                dist_[v] = dist_[u] + w;
                if (!dfs(v, include_zero)) return false;
            }
        }
        inq_[u] = 0;
        return true;
    }
};

const int MAXM = 10010;
int N, M;
double weight[MAXM];

int main() {
    scanf("%d%d", &N, &M);
    SpfaDfs spfa(N, M);
    double lo = INT_MAX, hi = INT_MIN;
    for (int i = 0; i < M; i++) {
        int u, v;
        double w;
        scanf("%d%d%lf", &u, &v, &w);
        u--; v--;
        spfa.addEdge(u, v, w);
        weight[i] = w;
        lo = min(lo, w);
        hi = max(hi, w);
    }

    lo -= 1; hi += 1;
    while (lo < hi - 1e-9) {
        double mid = (lo + hi) / 2;
        for (int i = 0; i < M; i++) {
            spfa.e_[i].wt = weight[i] - mid;
        }
        if (!spfa.check()) hi = mid;
        else lo = mid;
    }
    printf("%.8f", hi);

    return 0;
}
