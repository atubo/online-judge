// https://www.luogu.org/problemnew/show/P4551
// 最长异或路径

#include <bits/stdc++.h>
using namespace std;


class BinaryTrie {
public:
    class Node {
    public:
        Node():children(2, NULL) {}

        ~Node() {
            for (Node* child: children) {
                delete child;
            }
        }

        vector<Node*> children;
    };

    int N;
    Node* root;

    BinaryTrie(int N_): N(N_) {
        root = new Node();
    }

    ~BinaryTrie() {
        delete root;
    }

    void insert(int x) {
        Node* node = root;
        for (int i = N-1; i >= 0; i--) {
            int d = (x >> i) & 1;
            if (node->children[d] == NULL) {
                node->children[d] = new Node();
            }
            node = node->children[d];
        }
    }
};

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

const int MAXN = 100010;
int N;
int dist[MAXN];

void dfs(const Graph &g, int u, int fa, int d) {
    dist[u] = d;
    for (int eidx = g.head[u]; ~eidx; eidx = g.E[eidx].next) {
        int v = g.E[eidx].to;
        int w = g.E[eidx].wt;
        if (v != fa) {
            dfs(g, v, u, d^w);
        }
    }
}

int solve(const BinaryTrie &trie, int x) {
    int ans = 0;
    BinaryTrie::Node *node = trie.root;
    for (int i = 30; i >= 0; i--) {
        if ((x >> i) & 1) {
            if (node->children[0]) {
                ans |= (1<<i);
                node = node->children[0];
            } else {
                node = node->children[1];
            }
        } else {
            if (node->children[1]) {
                ans |= (1<<i);
                node = node->children[1];
            } else {
                node = node->children[0];
            }
        }
    }
    return ans;
}

int main() {
    scanf("%d", &N);
    Graph g(N, 2*(N-1));
    for (int i = 0; i < N-1; i++) {
        int u, v, w;
        scanf("%d%d%d", &u, &v, &w);
        u--; v--;
        g.addEdge(u, v, w);
        g.addEdge(v, u, w);
    }
    dfs(g, 0, -1, 0);

    BinaryTrie trie(31);
    trie.insert(dist[0]);
    int ans = 0;
    for (int i = 1; i < N; i++) {
        ans = max(ans, solve(trie, dist[i]));
        trie.insert(dist[i]);
    }
    printf("%d\n", ans);
    return 0;
}
