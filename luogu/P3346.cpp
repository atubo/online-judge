// https://www.luogu.org/problemnew/show/P3346
// [ZJOI2015]诸神眷顾的幻想乡

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
class ExtendedSuffixAutomaton {
public:
    static const int CHARSET_SIZE = 10;
    struct Node {
        Node *ch[CHARSET_SIZE], *next;
        int maxlen, posCnt;

        int getMin() {
            return next->maxlen + 1;
        }
    private:
        Node(int maxl = 0, bool newSuffix = false):
            ch(), next(NULL), maxlen(maxl), posCnt(newSuffix) {}
        friend ExtendedSuffixAutomaton;
    };

    int n_, cap_;
    Node *_pool;
    Node *start, *last, *_curr;
    vector<Node*> topo;

    ExtendedSuffixAutomaton(int n): n_(n) {
        cap_ = 2*n_ + 1;
        _pool = new Node[cap_];
        _curr = _pool;
        start = last = alloc(0, false);
    }

    ~ExtendedSuffixAutomaton() {
        delete[] _pool;
    }

    /**
     * split p->ch[c] if necessary
     * @param p: a node whose transition state on c will be splitted if needed
     * @param c: transition character
     * @return: if split happens return the new node, otherwise the old node
     */
    Node* split(Node *p, int c) {
        Node *q = p->ch[c];
        if (q->maxlen == p->maxlen+1) return q;

        Node *nq = alloc(p->maxlen+1, false);
        std::copy(q->ch, q->ch + CHARSET_SIZE, nq->ch);
        nq->next = q->next;
        q->next = nq;
        for (; p && p->ch[c] == q; p = p->next) p->ch[c] = nq;
        return nq;
    }

    /**
     * @param p: current position in this SAM
     * @param c: new character to be inserted
     * @return: new position after insertion
     */
    Node* ins(Node* p, int c) {
        if (p->ch[c]) {
            last = split(p, c);
        } else {
            Node *np = alloc(p->maxlen+1, true);
            last = np;
            for (; p && !p->ch[c]; p = p->next) p->ch[c] = np;
            if (!p) np->next = start;
            else np->next = split(p, c);
        }
        return last;
    }

    void calc() {
        toposort();
        for (int i = topo.size()-1; i > 0; i--) {
            Node *v = topo[i];
            v->next->posCnt += v->posCnt;
        }
    }

private:
    Node *alloc(int maxlen, bool newSuffix) {
        return new (_curr++)Node(maxlen, newSuffix);
    }


    void toposort() {
        vector<int> buc(cap_);
        int maxlen = 0;
        for (Node *p = _pool; p != _curr; p++) {
            maxlen = std::max(maxlen, p->maxlen);
            buc[p->maxlen]++;
        }
        for (int i = 1; i <= maxlen; i++) buc[i] += buc[i-1];
        topo.clear();
        topo.resize(_curr - _pool);
        for (Node *p = _pool; p != _curr; p++) {
            topo[--buc[p->maxlen]] = p;
        }
    }
};

const int MAXN = 100010;
int N;
int C[MAXN], deg[MAXN];

void dfs(int u, int fa, ExtendedSuffixAutomaton &esam,
         const Graph &g,
         ExtendedSuffixAutomaton::Node *p) {
    auto curr = esam.ins(p, C[u]);
    for (int eidx = g.head[u]; ~eidx; eidx = g.E[eidx].next) {
        int v = g.E[eidx].to;
        if (v != fa) {
            dfs(v, u, esam, g, curr);
        }
    }
}

int main() {
    int t;
    scanf("%d%d", &N, &t);
    Graph g(N, 2*(N-1));
    for (int i = 0; i < N; i++) {
        scanf("%d", &C[i]);
    }
    for (int i = 0; i < N-1; i++) {
        int u, v;
        scanf("%d%d", &u, &v);
        u--; v--;
        g.addEdge(u, v);
        g.addEdge(v, u);
        deg[u]++;
        deg[v]++;
    }

    vector<int> leaves;
    for (int i = 0; i < N; i++) {
        if (deg[i] == 1) leaves.push_back(i);
    }

    ExtendedSuffixAutomaton esam(N*20);
    for (int u: leaves) {
        dfs(u, -1, esam, g, esam.start);
    }

    int64_t ans = 0;
    for (auto p = esam.start+1; p != esam._curr; p++) {
        ans += p->maxlen - p->next->maxlen;
    }
    printf("%ld\n", ans);

    return 0;
}
