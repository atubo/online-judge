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
    TarjanOLCA(const vector<Node>& tree, int root, const set<PII>& query):
        m_tree(tree), m_root(root), m_size(tree.size()), m_rank(m_size, -1),
        m_parent(m_size, -1), m_color(m_size, WHITE)
    {
        // reformat query for easier access later
        for (set<PII>::const_iterator it = query.begin();
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

        for (map<int, set<int> >::const_iterator it = m_query.begin();
             it != m_query.end(); ++it) {
            cout << it->first << ": ";
            for (set<int>::const_iterator it2 = it->second.begin();
                 it2 != it->second.end(); ++it2) {
                cout << *it2 << " ";
            }
            cout << endl;
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
        cout << "entering lca: u = " << u << endl;
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
        cout << "leaving lca: u = " << u << endl;
    }

    void solve() {
        lca(m_root);
    }
};

int main()
{
    vector<Node> tree(5);
    tree[0].ancestor = 2;
    tree[2].ancestor = 2;
    tree[2].children.push_back(1);
    tree[2].children.push_back(0);
    tree[1].ancestor = 2;
    tree[1].children.push_back(3);
    tree[1].children.push_back(4);
    tree[3].ancestor = 1;
    tree[4].ancestor = 1;

    set<pair<int, int> > query;
    query.insert(make_pair(0, 3));
    query.insert(make_pair(0, 4));
    query.insert(make_pair(1, 2));
    query.insert(make_pair(0, 1));
    query.insert(make_pair(3, 4));
    TarjanOLCA olca(tree, 2, query);
    map<pair<int, int>, int> result = olca.getLCA();
    for (map<pair<int, int>, int>::const_iterator it = result.begin();
         it != result.end(); ++it) {
        printf("%d %d: %d\n", it->first.first, it->first.second, it->second);
    }
    return 0;
}
