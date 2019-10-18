// https://www.luogu.org/problem/P3294
// [SCOI2016]背单词

#include <bits/stdc++.h>
using namespace std;

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

class Trie {
public:
    struct Node {
        int id;
        Node* ch[26];
        Node(): id(0) {
            for (int i = 0; i < 26; i++) ch[i] = NULL;
        }

        ~Node() {
            for (int i = 0; i < 26; i++) {
                delete ch[i];
            }
        }
    };

    Trie() {
        root_ = new Node();
    }

    ~Trie() {
        delete root_;
    }

    void insert(const string& s, int id) {
        Node* node = root_;
        for (int i = (int)s.length()-1; i >= 0; i--) {
            char c = s[i];
            if (!node->ch[c-'a']) {
                node->ch[c-'a'] = new Node();
            }
            node = node->ch[c-'a'];
        }
        node->id = id;
    }

    Node* root_;
};

void buildGraph(const Trie::Node* node, Graph& g, int last) {
    if (!node) return;
    if (node->id > 0) {
        g.addEdge(last, node->id);
        last = node->id;
    }
    for (int i = 0; i < 26; i++) {
        buildGraph(node->ch[i], g, last);
    }
}

int N;

pair<int, int64_t> dfs(const Graph& g, int u) {
    int sz = 1;
    int64_t cost = 0;
    vector<int> csz;
    for (int eidx = g.head[u]; ~eidx; eidx = g.E[eidx].next) {
        int v = g.E[eidx].to;
        auto p = dfs(g, v);
        sz += p.first;
        csz.push_back(p.first);
        cost += p.second;
    }
    sort(csz.begin(), csz.end());
    int n = csz.size();
    cost += n;
    for (int i = 0; i < n-1; i++) {
        cost += 1LL * (n-i-1) * csz[i];
    }

    return make_pair(sz, cost);
}

int main() {
    scanf("%d", &N);
    Trie trie;
    for (int i = 1; i <= N; i++) {
        string s;
        cin >> s;
        trie.insert(s, i);
    }

    Graph g(N+1, N);
    buildGraph(trie.root_, g, 0);

    auto p = dfs(g, 0);
    printf("%ld\n", p.second);

    return 0;
}
