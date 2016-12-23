// https://www.luogu.org/problem/show?pid=1991
// 无线通讯网

#include <algorithm>
#include <cassert>
#include <cmath>
#include <cstdio>
#include <vector>

using namespace std;

class UnionFind {
private:
    const int N;
    vector<int> rank;
    vector<int> parent;
    vector<int> size;

    void makeSet(int k) {
        assert(0 <= k && k < N);

        parent[k] = k;
        rank[k] = 0;
        size[k] = 1;
    }

    void link(int u, int v) {
        if (rank[u] > rank[v]) {
            parent[v] = u;
            size[u] += size[v];
        } else {
            parent[u] = v;
            size[v] += size[u];
            if (rank[u] == rank[v]) {
                rank[v]++;
            }
        }
    }

public:
    UnionFind(int n): N(n) {
        rank.resize(N);
        parent.resize(N);
        size.resize(N);

        for (int i = 0; i < N; i++) {
            makeSet(i);
        }
    }

    int find(int k) {
        if (parent[k] == k) return k;
        int root = find(parent[k]);
        return parent[k] = root;
    }

    void join(int u, int v) {
        link(find(u), find(v));
    }

    int count(int u) {
        return size[find(u)];
    }
};

typedef pair<int, int> PII;
typedef pair<double, pair<int, int> > Edge; // (weight, (u, v))

class Solution {
private:
    int S, P;
    vector<PII> pos;
    vector<Edge> edges;

public:
    Solution() {
        scanf("%d %d", &S, &P);
        pos.resize(P);
        for (int i = 0; i < P; i++) {
            scanf("%d %d", &pos[i].first, &pos[i].second);
        }

        for (int i = 0; i < P-1; i++) {
            for (int j = i+1; j < P; j++) {
                edges.push_back(make_pair(calcDist(i, j), make_pair(i, j)));
            }
        }

        sort(edges.begin(), edges.end());
    }

    double calcDist(int i, int j) {
        double dx = pos[i].first - pos[j].first;
        double dy = pos[i].second - pos[j].second;
        return sqrt(dx*dx + dy*dy);
    }

    void solve() {
        double lo = 0;
        double hi = 20000;
        while (lo < hi - 0.0001) {
            double mid = (lo + hi) / 2;
            if (kruskal(mid) <= S) {
                hi = mid;
            } else {
                lo = mid;
            }
        }
        printf("%.2f\n", hi);
    }

    // return number of connected components
    int kruskal(double d) {
        int ans = P;
        UnionFind uf(P);
        for (int i = 0; i < (int)edges.size(); i++) {
            Edge edge = edges[i];
            double w = edge.first;
            int u = edge.second.first;
            int v = edge.second.second;
            if (w > d) break;
            if (uf.find(u) == uf.find(v)) continue;
            ans--;
            uf.join(u, v);
        }

        return ans;
    }
};

int main() {
    Solution solution;
    solution.solve();
    return 0;
}
