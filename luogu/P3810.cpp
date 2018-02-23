// https://www.luogu.org/problemnew/show/P3810
// 【模板】三维偏序（陌上花开）

#include <bits/stdc++.h>
using namespace std;

// 1-indexed
class SegmentTreeInSegmentTree {
private:
    static const int NULL_ELEM = 0;
    struct Node {
        Node(): left(0), right(0), total(NULL_ELEM) {}
        int left, right, total;
    };

    const int N, M;
    Node *nodes;
    int  *roots;
    int nodeCnt;
public:
    // N, and M need to be ceiled to the next power of 2
    SegmentTreeInSegmentTree(int N_, int M_): N(N_), M(M_) {
        //nodes = new Node[2*N*2*M]{};
        nodes = new Node[30000000];
        roots = new int[2*N]{};
        nodeCnt = 1;
    }

    ~SegmentTreeInSegmentTree() {
        delete[] roots;
        delete[] nodes;
    }

    // put val to (x, y)
    void put(int val, int x, int y) {
        put(1, val, x, 1, N, y);
    }

    int query(int x1, int x2, int y1, int y2) {
        if (x1 > x2 || y1 > y2) return NULL_ELEM;
        return query(1, x1, x2, 1, N, y1, y2);
    }

private:
    // put val to (x, y), currently at root[k]
    // x range for the tree at this root is [lx, rx]
    void put(int k, int val,
             int x, int lx, int rx,
             int y) {
        if (x < lx || rx < x) return;
        update(roots[k], val, y, 1, M);
        if (lx == rx) return;
        int mid = (lx + rx) / 2;
        if (x <= mid) put(2*k,   val, x, lx,    mid, y);
        else          put(2*k+1, val, x, mid+1, rx,  y);
    }

    // put val to position y, current node range is [l, r]
    void update(int &now, int val, int y, int l, int r) {
        if (y < l || r < y) return;
        if (!now) now = nodeCnt++;
        if (l == r) {
            nodes[now].total += val;
            return;
        }
        int mid = (l + r) / 2;
        if (y <= mid) update(nodes[now].left,  val, y, l, mid);
        else          update(nodes[now].right, val, y, mid+1, r);
        nodes[now].total = nodes[nodes[now].left].total +
            nodes[nodes[now].right].total;
    }

    int query(int k, int x1, int x2, int lx, int rx, int y1, int y2) {
        assert(x1 <= x2);
        if (x2 < lx || rx < x1) return NULL_ELEM;
        if (lx >= x1 && rx <= x2) return query(roots[k], y1, y2, 1, M);
        int mid = (lx + rx) / 2;
        int ret = NULL_ELEM;
        if (x1 <= mid) ret = query(2*k, x1, x2, lx, mid, y1, y2);
        if (mid < x2)  ret += query(2*k+1, x1, x2, mid+1, rx, y1, y2);
        return ret;
    }

    int query(int node, int y1, int y2, int l, int r) {
        assert(y1 <= y2);
        if (y2 < l || r < y1) return NULL_ELEM;
        if (l >= y1 && r <= y2) return nodes[node].total;
        int mid = (l + r) / 2;
        int ret = NULL_ELEM;
        if (y1 <= mid) ret = query(nodes[node].left, y1, y2, l, mid);
        if (mid < y2)  ret += query(nodes[node].right, y1, y2, mid+1, r);
        return ret;
    }
};

const int MAXN = 100010;
int N, K;
struct Item {
    int a, b, c;
    bool operator < (const Item &other) const {
        if (c < other.c) return true;
        if (c > other.c) return false;
        if (b < other.b) return true;
        if (b > other.b) return false;
        return (a < other.a);
    }
    bool operator == (const Item &other) const {
        return (a == other.a) && (b == other.b) && (c == other.c);
    }
} item[MAXN];

int A[MAXN], B[MAXN], C[MAXN];
int *ea, *eb, *ec;
int result[MAXN];

int main() {
    scanf("%d%d", &N, &K);
    for (int i = 0; i < N; i++) {
        int a, b, c;
        scanf("%d%d%d", &a, &b, &c);
        A[i] = a; B[i] = b; C[i] = c;
        item[i] = {a, b, c};
    }
    sort(A, A+N);
    ea = unique(A, A+N);
    sort(B, B+N);
    eb = unique(B, B+N);
    sort(C, C+N);
    ec = unique(C, C+N);
    for (int i = 0; i < N; i++) {
        item[i].a = lower_bound(A, ea, item[i].a) - A + 1;
        item[i].b = lower_bound(B, eb, item[i].b) - B + 1;
        item[i].c = lower_bound(C, ec, item[i].c) - C + 1;
    }
    sort(item, item+N);

    SegmentTreeInSegmentTree st(131072, 131072);
    for (int i = 0; i < N; i++) {
        int cnt = 1;
        while (i < N-1 && item[i] == item[i+1]) {
            i++;
            cnt++;
        }
        st.put(cnt-1, item[i].a, item[i].b);
        int f = st.query(1, item[i].a, 1, item[i].b);
        result[f] += cnt;
        st.put(1, item[i].a, item[i].b);
    }
        
    for (int i = 0; i < N; i++) {
        printf("%d\n", result[i]);
    }
    return 0;
}
