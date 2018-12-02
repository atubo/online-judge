// https://www.luogu.org/problemnew/show/P4148
// 简单题

#include <bits/stdc++.h>
using namespace std;

// 2-d implementation
// Note points are 1-indexed
class KdTree {
    struct Point {
        int x[2], w;
    };

    struct Node {
        int ls, rs, sum, sz;
        int mi[2], mx[2];   // min and max
        Point tp;
    };

    struct PointComp {
        PointComp(int _wd): wd(_wd) {}
        bool operator ()(const Point &a, const Point &b) const {
            return a.x[wd] < b.x[wd];
        }
        int wd;
    };
public:
    KdTree(int n): n_(n) {
        alloc();
    }

    ~KdTree() {
        dealloc();
    }

    void insert(int x, int y, int w) {
        Point t{x, y, w};
        insert(root_, t, 0);
    }

    int query(int x1, int y1, int x2, int y2) {
        return query(root_, x1, y1, x2, y2);
    }

private:
    const int n_;
    Point *pts_;
    Node *tree_;
    int *garbage_;
    int gbg_top_ = 0;
    int curr_ = 0;
    int root_ = 0;

    void alloc() {
        pts_ = new Point[n_+1]{};
        tree_ = new Node[n_+1]{};
        garbage_ = new int[n_+1]{};
    }

    void dealloc() {
        delete[] pts_;
        delete[] tree_;
        delete[] garbage_;
    }

    /**
     * create a new node
     * @return: index of the new node
     */
    int newnode() {
        if (gbg_top_) return garbage_[gbg_top_--];
        else return ++curr_;
    }

    /**
     * Collect subtree statistics such as size, weight sum
     * @param k: index of subtree root
     */
    void pushUp(int k) {
        int l = tree_[k].ls, r = tree_[k].rs;
        for (int i = 0; i < 2; i++) {
            tree_[k].mi[i] = tree_[k].mx[i] = tree_[k].tp.x[i];
            if (l) tree_[k].mi[i] = min(tree_[k].mi[i], tree_[l].mi[i]);
            if (r) tree_[k].mi[i] = min(tree_[k].mi[i], tree_[r].mi[i]);
            if (l) tree_[k].mx[i] = max(tree_[k].mx[i], tree_[l].mx[i]);
            if (r) tree_[k].mx[i] = max(tree_[k].mx[i], tree_[r].mx[i]);
        }
        tree_[k].sum = tree_[l].sum + tree_[r].sum + tree_[k].tp.w;
        tree_[k].sz = tree_[l].sz + tree_[r].sz + 1;
    }

    /**
     * build subtree for range [l, r]
     * @param l: left boundary
     * @param r: right boundary
     * @param wd: direction
     * @return: root index
     */
    int build(int l, int r, int wd) {
        if (l > r) return 0;
        int mid = (l + r) / 2;
        int k = newnode();
        nth_element(pts_+l, pts_+mid, pts_+r+1, PointComp(wd));
        tree_[k].tp = pts_[mid];
        tree_[k].ls = build(l, mid-1, wd^1);
        tree_[k].rs = build(mid+1, r, wd^1);
        pushUp(k);
        return k;
    }

    /**
     * flatten a tree to the point array
     * @param k: index of subtree root
     * @param num: position of array to flatten to
     */
    void flatten(int k, int num) {
        if (tree_[k].ls) flatten(tree_[k].ls, num);
        pts_[tree_[tree_[k].ls].sz+num] = tree_[k].tp;
        garbage_[++gbg_top_] = k;
        if (tree_[k].rs) flatten(tree_[k].rs, num+tree_[tree_[k].ls].sz+1);
    }

    /**
     * check and if necessary do rebalance
     * @param k: index of subtree root
     * @param wd: direction
     */
    void rebalance(int &k, int wd) {
        if (tree_[k].sz * 0.75 < tree_[tree_[k].ls].sz ||
            tree_[k].sz * 0.75 < tree_[tree_[k].rs].sz) {
            flatten(k, 1);
            k = build(1, tree_[k].sz, wd);
        }
    }

    void insert(int &k, const Point &tmp_pt, int wd) {
        if (!k) {
            k = newnode();
            tree_[k].ls = tree_[k].rs = 0;
            tree_[k].tp = tmp_pt;
            pushUp(k);
            return;
        }
        if (tmp_pt.x[wd] <= tree_[k].tp.x[wd]) {
            insert(tree_[k].ls, tmp_pt, wd^1);
        } else {
            insert(tree_[k].rs, tmp_pt, wd^1);
        }
        pushUp(k);
        rebalance(k, wd);
    }

    bool in(int x1, int y1, int x2, int y2, int X1, int Y1, int X2, int Y2) {
        return (X1>=x1&&X2<=x2&&Y1>=y1&&Y2<=y2);
    }

    bool out(int x1,int y1,int x2,int y2,int X1,int Y1,int X2,int Y2) {
        return (x1>X2||x2<X1||y1>Y2||y2<Y1);
    }

    int query(int k, int x1, int y1, int x2, int y2) {
        if (!k) return 0;
        int ret = 0;
        const int X1 = tree_[k].mi[0], Y1 = tree_[k].mi[1];
        const int X2 = tree_[k].mx[0], Y2 = tree_[k].mx[1];
        const int xc = tree_[k].tp.x[0], yc = tree_[k].tp.x[1];

        if (in(x1, y1, x2, y2, X1, Y1, X2, Y2)) return tree_[k].sum;
        if (out(x1, y1, x2, y2, X1, Y1, X2, Y2)) return 0;
        if (in(x1, y1, x2, y2, xc, yc, xc, yc)) ret += tree_[k].tp.w;
        ret += query(tree_[k].ls, x1, y1, x2, y2) +
            query(tree_[k].rs, x1, y1, x2, y2);
        return ret;
    }
};

const int MAXP = 200010;
int N;

int main() {
    scanf("%d", &N);
    KdTree kd(MAXP);
    int lastans = 0;
    while (true) {
        int cmd, x1, y1, x2, y2, a;
        scanf("%d", &cmd);
        if (cmd == 3) break;
        if (cmd == 1) {
            scanf("%d%d%d", &x1, &y1, &a);
            kd.insert(x1^lastans, y1^lastans, a^lastans);
        } else {
            scanf("%d%d%d%d", &x1, &y1, &x2, &y2);
            lastans = kd.query(x1^lastans, y1^lastans,
                               x2^lastans, y2^lastans);
            printf("%d\n", lastans);
        }
    }

    return 0;
}
