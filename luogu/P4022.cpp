// https://www.luogu.org/problemnew/show/P4022
// [CTSC2012]熟悉的文章

#include <bits/stdc++.h>
using namespace std;

class ExtendedSuffixAutomaton {
public:
    static const int CHARSET_SIZE = 2;
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

const int MAXN = 1100010;
int A[MAXN];
int dp[MAXN];
int N, M;
using Node = ExtendedSuffixAutomaton::Node;

void init(int n) {
    memset(A, 0, n*sizeof(int));
}

bool check(int n, int len) {
    memset(dp, 0, n*sizeof(int));
    deque<int> dq;
    for (int i = 1; i <= n; i++) {
        dp[i] = dp[i-1];
        if (A[i] >= len) {
            dp[i] = max(dp[i], A[i] + dp[i-A[i]]);
            while (!dq.empty() && dq.front() < i-A[i]) dq.pop_front();
            if (!dq.empty()) {
                int j = dq.front();
                dp[i] = max(dp[i], dp[j]-j+i);
            }
        }
        if (i-len+1 >= 0) {
            int j = i - len + 1;
            while (!dq.empty() && dp[dq.back()]-dq.back() <= dp[j]-j) {
                dq.pop_back();
            }
            dq.push_back(j);
        }
    }
    return double(dp[n])/n >= 0.9;
}


void solve(const string &s, const ExtendedSuffixAutomaton &esam) {
    const int n = s.length();
    init(n);
    Node *node = esam.start;
    int len = 0;
    for (int i = 0; i < n; i++) {
        const int c = s[i] - '0';
        Node *next = node->ch[c];
        if (next) {
            node = next;
            len++;
        } else {
            A[i] = len;
            while (node && !node->ch[c]) {
                node = node->next;
            }
            if (!node) {
                node = esam.start;
                len = 0;
            } else {
                len = node->maxlen + 1;
                node = node->ch[c];
            }
        }
    }
    A[n] = min(len, node->maxlen);

    for (int i = n-1; i >= 1; i--) {
        A[i] = max(A[i], A[i+1]-1);
    }

    int lo = 0, hi = n+1;
    while (lo < hi-1) {
        int mid = (lo + hi) / 2;
        if (check(n, mid)) lo = mid;
        else hi = mid;
    }
    printf("%d\n", lo);
}

int main() {
    scanf("%d%d", &N, &M);
    ExtendedSuffixAutomaton esam(MAXN);
    for (int i = 0; i < M; i++) {
        string s;
        cin >> s;
        Node *node = esam.start;
        for (char c: s) {
            node = esam.ins(node, c-'0');
        }
    }

    for (int i = 0; i < N; i++) {
        string s;
        cin >> s;
        solve(s, esam);
    }

    return 0;
}
