// https://www.luogu.org/problemnew/show/P4070
// [SDOI2016]生成魔咒

#include <bits/stdc++.h>
using namespace std;

class SuffixAutomatonLargeAlphabet {
public:
    struct Node {
    private:
        map<int, Node*> ch_;
    public: 
        Node *next;
        int maxl, posCnt;

        int getMin() {
            return next->maxl + 1;
        }
        Node* getCh(int c) const {
            auto it = ch_.find(c);
            return (it != ch_.end() ? it->second : NULL);
        }

        void setCh(int c, Node* node) {
            ch_[c] = node;
        }
    private:
        Node(int maxlen = 0, bool newSuffix = false):
            next(NULL), maxl(maxlen), posCnt(newSuffix) {}
        friend SuffixAutomatonLargeAlphabet;
    };

    Node *start;
    vector<Node*> topo;

    SuffixAutomatonLargeAlphabet(int n): n_(n) {
        pool_ = new Node[n_ * 2 + 1];
        curr_ = pool_;
        start = last_ = alloc(0, false);
    }

    ~SuffixAutomatonLargeAlphabet() {
        delete[] pool_;
    }

    void build(const vector<int> &s) {
        for (int c: s) {
            extend(c);
        }
    }

    void calc() {
        toposort();
        for (int i = topo.size()-1; i > 0; i--) {
            Node *v = topo[i];
            v->next->posCnt += v->posCnt;
        }
    }

private:
    int64_t ans_ = 0;
    int n_;
    Node *pool_;
    Node *last_, *curr_;

    Node *alloc(int maxl, bool newSuffix) {
        return new (curr_++)Node(maxl, newSuffix);
    }

    Node *extend(int c) {
        Node *u = alloc(last_->maxl + 1, true), *v = last_;

        for (; v && !v->getCh(c); v = v->next) v->setCh(c, u);

        if (!v) {
            u->next = start;
        } else if (v->getCh(c)->maxl == v->maxl + 1) {
            u->next = v->getCh(c);
        } else {
            Node *n = alloc(v->maxl + 1, false), *o = v->getCh(c);
            n->ch_ = o->ch_;
            n->next = o->next;
            o->next = u->next = n;
            for (; v && v->getCh(c) == o; v = v->next) v->setCh(c, n);
        }
        last_ = u;
        ans_ += u->maxl - u->getMin() + 1;
        printf("%ld\n", ans_);
        return u;
    }

    void toposort() {
        vector<int> buc(2*n_+1);
        int maxl = 0;
        for (Node *p = pool_; p != curr_; p++) {
            maxl = std::max(maxl, p->maxl);
            buc[p->maxl]++;
        }
        for (int i = 1; i <= maxl; i++) buc[i] += buc[i-1];
        topo.clear();
        topo.resize(curr_ - pool_);
        for (Node *p = pool_; p != curr_; p++) {
            topo[--buc[p->maxl]] = p;
        }
    }
};

int N;
int main() {
    scanf("%d", &N);
    vector<int> s(N);
    for (int i = 0; i < N; i++) {
        scanf("%d", &s[i]);
    }
    SuffixAutomatonLargeAlphabet sam(N);
    sam.build(s);
    return 0;
}
