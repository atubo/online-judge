// https://www.luogu.org/problem/P3472
// [POI2008]MAF-Mafia

#include <bits/stdc++.h>
using namespace std;

const int MAXN = 1000010;
int N;
int FA[MAXN], DEG[MAXN];

// Note graph node is 0-indexed
class Graph {
public:
    struct Edge {
        int next, to;
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
    void addEdge(int u, int v) {
        E[eidx].to = v;
        E[eidx].next = head[u];
        head[u] = eidx++;
    }
};

class Solution {
public:
    Solution(int n): n_(n) {
        alloc();
    }

    ~Solution() {
        dealloc();
    }

    int solve1(const Graph &g) {
        int ans = 0;
        for (int i = 0; i < n_; i++) {
            if (vis_[i]) continue;
            int s = findMergePoint(i);
            ans += baseDp(g, s);
        }
        return ans;
    }

    int solve2(const Graph &g) {
        memset(vis_, 0, n_*sizeof(bool));
        int ans = 0;
        for (int i = 0; i < n_; i++) {
            if (vis_[i]) continue;
            int s = findMergePoint(i);
            vector<int> ring;
            ring.push_back(s);
            int u = FA[s];
            while (u != s) {
                ring.push_back(u);
                u = FA[u];
            }
            int ret = 0;
            for (int v: ring) {
                ret += dfs(g, v);
            }
            if (ret == 0) ret = (ring.size() > 1);
            ans += ret;
        }
        return ans;
    }

    int findMergePoint(int s) {
        int fast = FA[FA[s]], slow = FA[s];
        while (fast != slow) {
            fast = FA[FA[fast]];
            slow = FA[slow];
        }
        return fast;
    }

    int baseDp(const Graph &g, int s) {
        inring_[s] = true;
        int u = FA[s];
        while (u != s) {
            inring_[u] = true;
            u = FA[u];
        }
        vector<pair<int, int>> ring;
        ring.push_back(treeDp(g, s));
        u = FA[s];
        while (u != s) {
            ring.push_back(treeDp(g, u));
            u = FA[u];
        }
        int n = ring.size();
        vector<pair<int, int>> dp(n);
        dp[0] = ring[0];
        for (int i = 1; i < n; i++) {
            dp[i].first = max(dp[i-1].first, dp[i-1].second) + ring[i].first;
            dp[i].second = dp[i-1].first + ring[i].second;
        }
        int ans = dp[n-1].first;
        dp[0] = make_pair(ring[0].first, 0);
        for (int i = 1; i < n; i++) {
            dp[i].first = max(dp[i-1].first, dp[i-1].second) + ring[i].first;
            dp[i].second = dp[i-1].first + ring[i].second;
        }
        ans = max(ans, max(dp[n-1].first, dp[n-1].second));
        return ans;
    }

private:
    int n_;
    bool *vis_, *inring_;

    void alloc() {
        vis_ = new bool[n_]{};
        inring_ = new bool[n_]{};
    }

    void dealloc() {
        delete[] vis_;
        delete[] inring_;
    }

    pair<int, int> treeDp(const Graph &g, int u) {
        vis_[u] = true;
        pair<int, int> ret = make_pair(0, 1);
        for (int eidx = g.head[u]; ~eidx; eidx = g.E[eidx].next) {
            int v = g.E[eidx].to;
            if (inring_[v]) continue;
            auto r = treeDp(g, v);
            ret.first += max(r.first, r.second);
            ret.second += r.first;
        }
        return ret;
    }

    int dfs(const Graph &g, int u) {
        vis_[u] = true;
        if (g.head[u] == -1) return 1;
        int ret = 0;
        for (int eidx = g.head[u]; ~eidx; eidx = g.E[eidx].next) {
            int v = g.E[eidx].to;
            if (inring_[v]) continue;
            ret += dfs(g, v);
        }
        return ret;
    }
};

int main() {
    scanf("%d", &N);
    Graph g(N, N);
    for (int i = 0; i < N; i++) {
        scanf("%d", &FA[i]);
        FA[i]--;
        g.addEdge(FA[i], i);
    }

    Solution solution(N);
    int ans1 = solution.solve1(g);
    int ans2 = solution.solve2(g);
    printf("%d %d", N-ans1, N-ans2);

    return 0;
}
