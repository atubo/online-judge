// https://www.luogu.org/problemnew/show/P3804
// 【模板】后缀自动机

#include <bits/stdc++.h>
using namespace std;

class SuffixAutomaton {
public:
    static const int CHARSET_SIZE = 26;
    static const int MAXN = 1000010;
    struct Node {
        Node *ch[CHARSET_SIZE], *next;
        int max, posCnt;

        Node(int max = 0, bool newSuffix = false):
            ch(), next(NULL), max(max), posCnt(newSuffix) {}

        int getMin() {
            return next->max + 1;
        }
    };

    Node *_pool;
    Node *start, *last, *_curr;
    vector<Node*> topo;

    SuffixAutomaton() {
        _pool = new Node[MAXN * 2 + 1];
        _curr = _pool;
        start = last = new (_curr++)Node;
    }

    ~SuffixAutomaton() {
        delete[] _pool;
    }

    Node *extend(int c) {
        Node *u = new (_curr++)Node(last->max + 1, true), *v = last;

        for (; v && !v->ch[c]; v = v->next) v->ch[c] = u;

        if (!v) {
            u->next = start;
        } else if (v->ch[c]->max == v->max + 1) {
            u->next = v->ch[c];
        } else {
            Node *n = new (_curr++)Node(v->max + 1, false), *o = v->ch[c];
            std::copy(o->ch, o->ch + CHARSET_SIZE, n->ch);
            n->next = o->next;
            o->next = u->next = n;
            for (; v && v->ch[c] == o; v = v->next) v->ch[c] = n;
        }
        last = u;
        return u;
    }

    void toposort() {
        static int buc[MAXN * 2 + 1];
        int max = 0;
        for (Node *p = _pool; p != _curr; p++) {
            max = std::max(max, p->max);
            buc[p->max]++;
        }
        for (int i = 1; i <= max; i++) buc[i] += buc[i-1];
        topo.clear();
        topo.resize(_curr - _pool);
        for (Node *p = _pool; p != _curr; p++) {
            topo[--buc[p->max]] = p;
        }
        std::fill(buc, buc + max + 1, 0);
    }

    void calc() {
        toposort();
        for (int i = topo.size()-1; i > 0; i--) {
            Node *v = topo[i];
            v->next->posCnt += v->posCnt;
        }
    }
};

int main() {
    string s;
    cin >> s;
    SuffixAutomaton sam;
    for (char c: s) {
        sam.extend(c - 'a');
    }
    sam.calc();

    int64_t ans = 0;
    for (auto node: sam.topo) {
        if (node->posCnt > 1) {
            ans = max(ans, (int64_t)node->posCnt * node->max);
        }
    }
    printf("%lld\n", ans);

    return 0;
}
