// https://www.luogu.org/problemnew/show/P4246
// [SHOI2008]堵塞的交通

#include <bits/stdc++.h>
using namespace std;

// segment tree with single point update and range query
// 0-indexed
class SegmentTreeSPU {
    const int DX[3] = {-1, 0, 1};
    const int DY[3] = {0, 1, 0};

    struct Node {
        bool c[3];
    };

    struct Connection {
        bool v[2], h[2], x[2];
        int l, r;
    };
    static const Connection NULL_VALUE;
public:
    SegmentTreeSPU(int n) {
        n_ = n;
        int sz = 4*n;
        conn_ = new Connection[sz];
        for (int i = 0; i < sz; i++) conn_[i] = NULL_VALUE;
        a_ = new Node[n]{};
        build(1, 0, n-1);
    }

    ~SegmentTreeSPU() {
        delete[] conn_;
        delete[] a_;
    }

    void update(int i, int x) {
        bool vc = a_[x].c[2];

        if (conn_[i].l == conn_[i].r) {
            conn_[i].v[0] = conn_[i].v[1] = conn_[i].x[0] = conn_[i].x[1] = vc;
            conn_[i].h[0] = conn_[i].h[1] = true;
            return;
        }

        int mid = (conn_[i].l + conn_[i].r) / 2;
        if (x <= mid) update(2*i, x);
        else update(2*i+1, x);
        conn_[i] = combine(conn_[2*i], conn_[2*i+1]);
    }

    void change(int r1, int c1, int r2, int c2, bool f) {
        if (r1 > r2) {
            swap(r1, r2);
            swap(c1, c2);
        }
        int dir;
        for (int i = 0; i < 3; i++) {
            if (c1+DX[i] == c2 && r1+DY[i] == r2) {
                dir = i;
                break;
            }
        }
        if (dir == 0) {
            a_[c2].c[r2] = f;
            update(1, c2);
        }
        else if (dir == 1) {
            a_[c2].c[2] = f;
            update(1, c2);
        }
        else {
            a_[c1].c[r1] = f;
            update(1, c1);
        }
    }

    void build(int i, int l, int r) {
        conn_[i].l = l; conn_[i].r = r;
        if (l == r) {
            conn_[i].h[0] = conn_[i].h[1] = true;
            return;
        }
        int mid = (l + r) / 2;
        build(2*i, l, mid);
        build(2*i+1, mid+1, r);
    }

    Connection query(int i, int l, int r) {
        if (l <= conn_[i].l && conn_[i].r <= r) return conn_[i];
        int mid = (conn_[i].l + conn_[i].r) / 2;
        if (r <= mid) return query(2*i, l, r);
        if (l > mid) return query(2*i+1, l, r);
        auto a = query(2*i, l, r), b = query(2*i+1, l, r);
        return combine(a, b);
    }

    bool solve(int r1, int c1, int r2, int c2) {
        if (c1 > c2) {
            swap(c1, c2);
            swap(r1, r2);
        }

        auto pa = query(1, 0, c1);
        auto pb = query(1, c1, c2);
        auto pc = query(1, c2, n_-1);
        if (r1 == r2) {
            if (r1 == 0) {
                return pb.h[0] || (pa.v[1] && pb.x[1]) ||
                    (pb.x[0] && pc.v[0]) || (pa.v[1] && pb.h[1] && pc.v[0]);
            } else {
                return pb.h[1] || (pa.v[1] && pb.x[0]) ||
                    (pb.x[1] && pc.v[0]) || (pa.v[1] && pb.h[0] && pc.v[0]);
            }
        } else {
            if (r1 == 0) {
                return pb.x[0] || (pa.v[1] && pb.h[1]) ||
                    (pc.v[0] && pb.h[0]);
            } else {
                return pb.x[1] || (pa.v[1] && pb.h[0]) ||
                    (pc.v[0] && pb.h[1]);
            }
        }
    }

private:
    Connection *conn_;
    Node *a_;
    int n_;

    Connection combine(const Connection &l, const Connection &r) {
        assert(l.r == r.l-1);
        int mid = l.r;
        Connection ret;
        ret.l = l.l; ret.r = r.r;
        ret.v[0] = l.v[0] ||
            (l.h[0] && a_[mid].c[0] && a_[mid].c[1] && r.v[0] && l.h[1]);
        ret.v[1] = r.v[1] ||
            (r.h[0] && a_[mid].c[0] && a_[mid].c[1] && l.v[1] && r.h[1]);
        ret.h[0] = (l.h[0] && a_[mid].c[0] && r.h[0]) ||
            (l.x[0] && a_[mid].c[1] && r.x[1]);
        ret.h[1] = (l.h[1] && a_[mid].c[1] && r.h[1]) ||
            (l.x[1] && a_[mid].c[0] && r.x[0]);
        ret.x[0] = (l.x[0] && a_[mid].c[1] && r.h[1]) ||
            (l.h[0] && a_[mid].c[0] && r.x[0]);
        ret.x[1] = (l.x[1] && a_[mid].c[0] && r.h[0]) ||
            (l.h[1] && a_[mid].c[1] && r.x[1]);
        return ret;
    }
};

const SegmentTreeSPU::Connection SegmentTreeSPU::NULL_VALUE =
    {false, false, false, false, false, false};

int main() {
    int n;
    scanf("%d", &n);
    SegmentTreeSPU st(n);
    char cmd[10];
    int r1, c1, r2, c2;
    while (true) {
        scanf("%s", cmd);
        if (cmd[0] == 'E') break;
        scanf("%d%d%d%d", &r1, &c1, &r2, &c2);
        r1--; c1--; r2--; c2--;
        if (cmd[0] == 'O') st.change(r1, c1, r2, c2, true);
        else if (cmd[0] == 'C') st.change(r1, c1, r2, c2, false);
        else {
            bool ok = st.solve(r1, c1, r2, c2);
            if (ok) printf("Y\n");
            else printf("N\n");
        }
    }

    return 0;
}
