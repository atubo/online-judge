#include <vector>
#include <map>
#include <set>
#include <utility>
#include <cassert>
#include <iostream>
using namespace std;

struct Node {
    int ancestor;
    vector<int> children;
};

class TarjanOLCA {
    typedef pair<int, int> PII;
    enum Color {
        WHITE = 0,
        BLACK = 1,
    };

public:
    TarjanOLCA(const vector<Node>& tree, int root, const vector<PII>& query):
        m_tree(tree), m_root(root), m_size(tree.size()), m_rank(m_size, -1),
        m_parent(m_size, -1), m_color(m_size, WHITE)
    {
        // reformat query for easier access later
        for (vector<PII>::const_iterator it = query.begin();
             it != query.end(); ++it) {
            int u = it->first;
            int v = it->second;
            if (m_query.count(u) == 0) {
                m_query[u] = set<int>();
            }
            if (m_query.count(v) == 0) {
                m_query[v] = set<int>();
            }
            m_query[u].insert(v);
            m_query[v].insert(u);
        }

        solve();
    }

    const map<PII, int> getLCA() const {
        return m_lca;
    }

private:
    vector<Node>        m_tree;
    int                 m_root;
    map<int, set<int> > m_query;
    map<PII, int>       m_lca;

    const int   m_size;
    vector<int> m_rank;
    vector<int> m_parent;
    vector<Color> m_color;

    void makeSet(int k) {
        assert(0 <= k && k < m_size);

        m_color[k]  = WHITE;
        m_parent[k] = k;
        m_rank[k]   = 0;
    }

    int find(int k) {
        if (m_parent[k] != k) {
            m_parent[k] = find(m_parent[k]);
        }
        return m_parent[k];
    }

    void link(int u, int v) {
        if (m_rank[u] > m_rank[v]) {
            m_parent[v] = u;
        }
        else {
            m_parent[u] = v;
            if (m_rank[u] == m_rank[v]) {
                m_rank[v]++;
            }
        }
    }

    void join(int u, int v) {
        link(find(u), find(v));
    }

    void lca(int u) {
        makeSet(u);
        m_tree[u].ancestor = u;
        for (int i = 0; i < (int)m_tree[u].children.size(); i++) {
            int v = m_tree[u].children[i];
            lca(v);
            join(u, v);
            m_tree[find(u)].ancestor = u;
        }
        m_color[u] = BLACK;
        if (m_query.count(u) > 0) {
            for (set<int>::const_iterator it = m_query[u].begin();
                 it != m_query[u].end(); ++it) {
                int v = *it;
                if (m_color[v] == BLACK) {
                    m_lca[make_pair(v, u)] = m_lca[make_pair(u, v)] 
                                           = m_tree[find(v)].ancestor;
                }
            }
        }
    }

    void solve() {
        lca(m_root);
    }
};

#include <inttypes.h>
#include <algorithm>
struct Fence {
    int r;
    int x;
    int y;

    Fence(int r_, int x_, int y_): r(r_), x(x_), y(y_) {}

    bool operator < (const Fence& other) const {
        if      (r < other.r) return true;
        else if (r > other.r) return false;
        else if (x < other.x) return true;
        else if (x > other.x) return false;
        else                  return y < other.y;
    }
};

struct CP {
    int x;
    int y;

    CP(int x_, int y_): x(x_), y(y_) {}
};

class Solution {
    typedef pair<int, int> PII;
public:
    Solution() {
        int n, k;
        cin >> n >> m >> k;
        for (int i = 0; i < n; i++) {
            int kx, ky;
            cin >> kx >> ky;
            cp.push_back(CP(kx, ky));
        }

        for (int i = 0; i < m; i++) {
            int r, cx, cy;
            cin >> r >> cx >> cy;
            fence.push_back(Fence(r, cx, cy));
        }
        sort(fence.begin(), fence.end());

        for (int i = 0; i < k; i++) {
            int a, b;
            cin >> a >> b;
            query.push_back(make_pair(a-1, b-1));
        }

        makeTree();

        height.resize(m+1);
        buildHeight(m, 0);

        cpPos.resize(n);
        buildCpPos();

        transformQuery();
        processQuery();
    }
private:
    int m;
    vector<CP> cp;
    vector<Fence> fence;
    vector<Node> tree;
    vector<PII> query;
    vector<int> height;
    vector<int> cpPos;

    // check if cp i is inside fence j
    bool pointInside(int i, int j) const {
        int64_t xi = cp[i].x;
        int64_t yi = cp[i].y;
        int64_t xj = fence[j].x;
        int64_t yj = fence[j].y;
        int64_t rj = fence[j].r;
 
        return rj * rj > (xi-xj)*(xi-xj) + (yi-yj)*(yi-yj);
    }

    // check if fence i is inside fence j
    bool fenceInside(int i, int j) const {
        int64_t xi = fence[i].x;
        int64_t yi = fence[i].y;
        int64_t ri = fence[i].r;
        int64_t xj = fence[j].x;
        int64_t yj = fence[j].y;
        int64_t rj = fence[j].r;

        return (rj-ri)*(rj-ri) > (xi-xj)*(xi-xj) + (yi-yj)*(yi-yj);
    }

    void makeTree() {
        tree.resize(m+1);

        // initialize
        for (int i = 0; i <= m; i++) {
            tree[i].ancestor = i;
        }

        // construct the forest
        for (int i = 0; i < m-1; i++) {
            for (int j = i+1; j < m; j++) {
                if (fenceInside(i, j)) {
                    tree[i].ancestor = j;
                    tree[j].children.push_back(i);
                    break;
                }
            }
        }

        // connect forest into a common root
        for (int i = 0; i < m; i++) {
            if (tree[i].ancestor == i) {
                tree[i].ancestor = m;
                tree[m].children.push_back(i);
            }
        }
    }

    void buildHeight(int u, int h) {
        height[u] = h;
        for (int i = 0; i < (int)tree[u].children.size(); i++) {
            int v = tree[u].children[i];
            buildHeight(v, h+1);
        }
    }

    void buildCpPos() {
        for (int i = 0; i < (int)cp.size(); i++) {
            int j = 0;
            for (; j < m; j++) {
                if (pointInside(i, j)) {
                    break;
                }
            }
            cpPos[i] = j;
        }
    }

    // transform query from control points to fence indices
    void transformQuery() {
        for (int i = 0; i < (int)query.size(); i++) {
            int a = query[i].first;
            int b = query[i].second;
            int u = cpPos[a];
            int v = cpPos[b];
            query[i] = make_pair(u, v);
        }
    }

    void processQuery() {
        TarjanOLCA olca(tree, m, query);
        map<pair<int, int>, int> result = olca.getLCA();
        for (int i = 0; i < (int)query.size(); i++) {
            int u = query[i].first;
            int v = query[i].second;
            assert(result.count(make_pair(u, v)) > 0);
            int w = result[make_pair(u, v)];
            cout << height[u] + height[v] - 2*height[w] << endl;
        }
    }

};

int main()
{
    Solution s;
    return 0;
}
