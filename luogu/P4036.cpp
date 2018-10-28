// https://www.luogu.org/problemnew/show/P4036
// [JSOI2008]火星人

#include <bits/stdc++.h>
using namespace std;

const int MAXN = 100010;
uint64_t PW[MAXN];

// 1-indexed, 0 means null
class ImplicitTreap2 {
    struct Node {
        int prior, size;
        int val;  // value stored in the array
        uint64_t hash;
        int l, r;
    };
public:
    ImplicitTreap2(int cap): cap_(cap) {
        alloc();
    }

    ~ImplicitTreap2() {
        dealloc();
    }

    /**
     * Note a should also be 1-indexed
     * @param a: the array based on which the treap is built
     * @return: root index
     */
    int build(const vector<int>& a) {
        root_ = build(a, 1, a.size());
        return root_;
    }

    uint64_t rangeQuery(int l, int r) { // [l,r]
        int t = root_;
        int L, mid, R;
        split(t, L, mid, l-1);
        split(mid, t, R, r-l+1);
        uint64_t ans = nodes_[t].hash;
        merge(mid, L, t);
        merge(root_, mid, R);
        return ans;
    }

    void update(int pos, int val) {
        int t = root_;
        int L, mid, R;
        split(t, L, mid, pos-1);
        split(mid, t, R, 1);
        nodes_[t].val = val;
        merge(mid, L, t);
        merge(root_, mid, R);
    }

    int operator[](int n) const {
        assert(1 <= n && n <= sz(root_));
        int t = root_;
        while (true) {
            int left_cnt = sz(nodes_[t].l);
            if (left_cnt == n-1) return nodes_[t].val;
            else if (left_cnt < n-1) {
                t = nodes_[t].r;
                n -= left_cnt + 1;
            } else {
                t = nodes_[t].l;
            }
        }
        assert(false);
        return -1;
    }

    /**
     * insert val after position pos, if pos = 0, insert at the begining
     * @param pos: position
     * @param val: value
     */
    void insert(int pos, int val) {
        assert(0 <= pos && pos <= sz(root_));
        int newnode = allocNode(val);
        if (pos == 0) {
            merge(root_, newnode, root_);
        } else if (pos == sz(root_)) {
            merge(root_, root_, newnode);
        } else {
            int t = root_;
            int L, R;
            split(t, L, R, pos);
            merge(t, L, newnode);
            merge(root_, t, R);
        }
    }

    void solve(int x, int y) {
        int ans = 0;
        if (x > y) swap(x, y);
        for (int i = 17; i >= 0; i--) {
            int d = (1<<i);
            if (y + d > curr_) continue;
            uint64_t hx = rangeQuery(x, x+d-1);
            uint64_t hy = rangeQuery(y, y+d-1);
            if (hx == hy) {
                ans += d;
                x += d;
                y += d;
            }
        }
        printf("%d\n", ans);
    }

private:
    int cap_;
    int curr_ = 1;
    int root_;
    Node *nodes_;

    void alloc() {
        nodes_ = new Node[cap_+1]{};
    }

    void dealloc() {
        delete[] nodes_;
    }

    int sz(int t) const {
        return t ? nodes_[t].size : 0;
    }

    void reset(int t) {
        if (t) nodes_[t].hash = nodes_[t].val;
    }

    // combining two ranges of segtree
    void combine(int t, int l, int r) {
        // TODO: can we remove this check?
#if 0
        if (!l || !r) {
            t = (l ? l : r);
            return;
        }
#endif
        int rsz = nodes_[r].size;
        nodes_[t].hash = nodes_[l].hash * PW[rsz+1] + nodes_[t].val * PW[rsz]
            + nodes_[r].hash;
    }

    void pushUp(int t) {
        if (!t) return;
        Node &node = nodes_[t];
        int lsz = nodes_[node.l].size;
        int rsz = nodes_[node.r].size;
        node.size = lsz + 1 + rsz;
        // reset the value of current node assuming it now represents
        // a single element of the array
        reset(t);
        //combine(t, node.l, node.r);
        nodes_[t].hash = nodes_[node.l].hash * PW[rsz+1]
            + nodes_[t].val * PW[rsz]
            + nodes_[node.r].hash;
    }

    // l -> leftarray, r->rightarray
    void merge(int& t, int l, int r) {
        Node &nl = nodes_[l];
        Node &nr = nodes_[r];
        if (!l || !r) t = l ? l : r;
        else if (nl.prior > nr.prior) merge(nl.r, nl.r, r), t=l;
        else merge(nr.l, l, nr.l), t=r;
        pushUp(t);
    }

    // [1, pos] goes to the left tree, remaining goes to the right
    void split(int t, int& l, int& r, int pos, int add=0) {
        if (!t) {l = r = 0; return;}
        Node &node = nodes_[t];
        int curr_pos = add + sz(node.l);
        if (curr_pos < pos) { // element at pos goes to left subtree
            split(node.r, node.r, r, pos, curr_pos+1);
            l = t;
        } else {
            split(node.l, l, node.l, pos, add);
            r = t;
        }
        pushUp(t);
    }

    /**
     * create a node from the memory pool
     * @param val: value of the node
     * @return: node index
     */
    int allocNode(int val) {
        Node& node = nodes_[curr_];
        node.prior = rand();
        node.size = 1;
        node.val = val;
        node.l = node.r = 0;
        return curr_++;
    }

    int build(const vector<int>& a, int i, int j) {
        // [i, j)
        if (i == j-1) {
            return allocNode(a[i]);
        }
        int mid = (i+j)/2;
        int left = build(a, i, mid);
        int right = build(a, mid, j);
        int ret;
        merge(ret, left, right);
        return ret;
    }
};

void init() {
    PW[0] = 1;
    for (int i = 1; i < MAXN; i++) {
        PW[i] = PW[i-1] * 131;
    }
}

int M;

int main() {
    init();
    ImplicitTreap2 treap(MAXN);
    string s;
    cin >> s;
    vector<int> a(s.length()+1);
    for (int i = 1; i <= (int)s.length(); i++) {
        a[i] = s[i-1] - 'a';
    }
    treap.build(a);

    scanf("%d", &M);
    char cmd[5], op[5];
    int x, y;
    for (int i = 0; i < M; i++) {
        scanf("%s", cmd);
        if (cmd[0] == 'Q') {
            scanf("%d%d", &x, &y);
            treap.solve(x, y);
        } else if (cmd[0] == 'R') {
            scanf("%d%s", &x, op);
            treap.update(x, op[0]-'a');
        } else {
            scanf("%d%s", &x, op);
            treap.insert(x, op[0]-'a');
        }
    }

    return 0;
}
