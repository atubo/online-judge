// https://www.luogu.org/problemnew/show/P3988
// [SHOI2013]发牌

#include <bits/stdc++.h>
using namespace std;

// 1-indexed, 0 means null
class ImplicitTreap {
    struct Node {
        int prior, size;
        int val;  // value stored in the array
        int l, r;
    };
public:
    ImplicitTreap(int cap): cap_(cap) {
        alloc();
    }

    ~ImplicitTreap() {
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

    int operator[](int n) const {
        int t = root_;
        while (true) {
            int left_cnt = nodes_[nodes_[t].l].size;
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

    void rotate(int pos) {
        int l, r;
        split(root_, l, r, pos);
        merge(root_, r, l);
    }

    void pop_front() {
        int p = root_, q = nodes_[p].l;
        if (q == 0) {
            root_ = nodes_[root_].r;
            return;
        }
        while (nodes_[q].l) {
            nodes_[p].size--;
            p = q;
            q = nodes_[p].l;
        }
        nodes_[p].size--;
        nodes_[p].l = nodes_[q].r;
    }

    int front() const {
        int p = root_;
        while (nodes_[p].l) p = nodes_[p].l;
        return nodes_[p].val;
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

    // l -> leftarray, r->rightarray
    void merge(int& t, int l, int r) {
        Node &nl = nodes_[l];
        Node &nr = nodes_[r];
        if (!l || !r) t = l ? l : r;
        else if (nl.prior > nr.prior) merge(nl.r, nl.r, r), t=l;
        else merge(nr.l, l, nr.l), t=r;
        if (t) {
            Node &node = nodes_[t];
            node.size = nodes_[node.l].size + 1 + nodes_[node.r].size;
        }
    }

    // [1, pos] goes to the left tree, remaining goes to the right
    void split(int t, int& l, int& r, int pos, int add=0) {
        if (!t) {l = r = 0; return;}
        Node &node = nodes_[t];
        int &nl = node.l;
        int &nr = node.r;
        int curr_pos = add + nodes_[nl].size;
        if (curr_pos < pos) { // element at pos goes to left subtree
            split(nr, nr, r, pos, curr_pos+1);
            l = t;
        } else {
            split(nl, l, nl, pos, add);
            r = t;
        }
        node.size = nodes_[nl].size + 1 + nodes_[nr].size;
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

int N;

int main() {
    srand(19260817);
    scanf("%d", &N);
    vector<int> a(N+1);
    iota(a.begin(), a.end(), 0);
    ImplicitTreap treap(N);
    treap.build(a);

    int n = N;
    for (int i = 0; i < N; i++) {
        int r;
        scanf("%d", &r);
        r = r % n;
        if (r > 0) {
            treap.rotate(r);
        }
        int x = treap.front();
        printf("%d\n", x);
        treap.pop_front();
        n--;
    }

    return 0;
}
