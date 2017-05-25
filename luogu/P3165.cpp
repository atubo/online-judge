// https://www.luogu.org/problem/show?pid=3165
// [CQOI2014]排序机械臂

#include <bits/stdc++.h>
using namespace std;
using PII = pair<int, int>;

class SplayTree {
public:
    struct Node {
        Node(int x, Node *f) {
            pre = f;
            sz = 1;
            val = x;
            tag = 0;

            ch[0] = ch[1] = NULL;
        }

        Node* pre;
        Node* ch[2];

        int sz;
        int val;
        int tag;
    };

    SplayTree(int sz) {
        nodes.resize(sz);
        root = build(0, sz, NULL);
    }

    // build range [i, j)
    Node* build(int p, int q, Node *f) {
        assert(q - p >= 1);

        int mid = (p + q) / 2;
        Node *x = new Node(mid, f);
        if (mid - p >= 1) x->ch[0] = build(p, mid, x);
        if (q - mid >= 2) x->ch[1] = build(mid+1, q, x);

        update(x);

        nodes[mid] = x;
        return x;
    }

    void pushDown(Node *x) {
        if (x->tag) {
            for (int i = 0; i < 2; i++) {
                Node *y = x->ch[i];
                if (y) y->tag ^= x->tag;
            }
            swap(x->ch[0], x->ch[1]);
            x->tag = 0;
        }
    }

    void update(Node *x) {
        int ans = 0;
        for (int i = 0; i < 2; i++) {
            Node *y = x->ch[i];
            if (y) ans += y->sz;
        }
        x->sz = ans + 1;
    }

    void rotate(Node *x, int c) {
        // c = 0: left rotation, c = 1: right rotation
        Node *y = x->pre;
        pushDown(y);
        pushDown(x);
        y->ch[!c] = x->ch[c];
        if (x->ch[c] != NULL) x->ch[c]->pre = y;
        x->pre = y->pre;
        if (y->pre != NULL) {
            if (y->pre->ch[0] == y) y->pre->ch[0] = x;
            else y->pre->ch[1] = x;
        }
        x->ch[c] = y;
        y->pre = x;
        update(y);

        if (y == root) root = x;
    }

    void splay(Node *x, Node *f) {
        for (pushDown(x); x->pre != f;) {
            if (x->pre->pre == f) {
                if (x->pre->ch[0] == x) rotate(x, 1);
                else rotate(x, 0);
            } else {
                Node *y = x->pre, *z = y->pre;
                if (z->ch[0] == y) {
                    if (y->ch[0] == x) {
                        // zig-zig
                        rotate(y, 1);
                        rotate(x, 1);
                    } else {
                        rotate(x, 0);
                        rotate(x, 1);
                    }
                } else {
                    if (y->ch[1] == x) {
                        // zig-zig
                        rotate(y, 0);
                        rotate(x, 0);
                    } else {
                        rotate(x, 1);
                        rotate(x, 0);
                    }
                }
            }
            print(root);
            printf("\n");
        }
        update(x);
    }

    Node* pred(Node *x) {
        if (x->ch[0]) {
            x = x->ch[0];
            while (x->ch[1]) x = x->ch[1];
        } else {
            while (x->pre->ch[0] == x) x = x->pre;
            x = x->pre;
        }
        return x;
    }

    Node* succ(Node *x) {
        if (x->ch[1]) {
            x = x->ch[1];
            while (x->ch[0]) x = x->ch[0];
        } else {
            while (x->pre->ch[1] == x) x = x->pre;
            x = x->pre;
        }
        return x;
    }

    void del(Node *x) {
        assert(!x->ch[0] && !x->ch[1]);
        assert(x->pre->ch[0] == x || x->pre->ch[1] == x);
        if (x->pre->ch[0] == x) x->pre->ch[0] = NULL;
        else x->pre->ch[1] = NULL;
        x->pre = NULL;
    }

    void print(Node *x) {
        printf("[");
        if (x) {
            printf("%d ", x->val);
            print(x->ch[0]);
            print(x->ch[1]);
            assert(x->ch[0] == NULL || x->ch[0]->pre == x);
            assert(x->ch[1] == NULL || x->ch[1]->pre == x);
        }
        printf("]");
    }

    Node* root;
    vector<Node*> nodes;
};

using Node = SplayTree::Node;


int main() {
    int N;
    scanf("%d", &N);
    vector<int> v(N+2);
    v[0] = v[N+1] = INT_MAX;
    for (int i = 1; i <= N; i++) {
        scanf("%d", &v[i]);
    }

    vector<PII> b(N+2);
    for (int i = 0; i <= N+1; i++) {
        b[i] = make_pair(v[i], i);
    }
    sort(b.begin(), b.end());

    SplayTree st(N+2);
    st.print(st.root);
    printf("\n");
    for (int i = 0; i < N; i++) {
        Node *x = st.nodes[b[i].second];
        st.splay(x, NULL);
        printf("%d\n", st.root->ch[0]->sz);
        st.print(st.root);
        printf("\n");
        Node *pred = st.pred(x);
        Node *succ = st.succ(x);
        st.splay(pred, NULL);
        printf("splay pred\n");
        st.print(st.root);
        printf("\n");

        st.splay(succ, pred);
        printf("ready to del\n");
        st.print(st.root);
        printf("\n");
        assert(st.root == pred && st.root->ch[1] == succ);
        assert(succ->pre == pred);
        assert(succ->ch[0] == x);
        assert(x->pre == succ);
        assert(x->ch[0] == NULL && x->ch[1] == NULL);
        st.del(x);
        printf("deleted\n");
        st.print(st.root);
        printf("\n");
    }

    return 0;
}
