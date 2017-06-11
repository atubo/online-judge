// http://acm.hdu.edu.cn/showproblem.php?pid=3436
// Queue-jumpers

#include <bits/stdc++.h>
using namespace std;

struct Seg {
    Seg(int b_ = 0, int e_ = 0) : b(b_), e(e_) {}
    int b, e;
};


// index starts from 1 (0 is for NULL)
class SplayTree {
public:
    static const int MAXINT = 0x3f3f3f3f;

    SplayTree(int cap) {
        alloc(cap);
    }

    void init(int size, const vector<Seg> &segs) {
        N = size;

        root = build(1, N, 0, segs);
    }


    // build range [i, j]
    int build(int p, int q, int fa, const vector<Seg> &segs) {
        if (p > q) return 0;
        assert(q - p >= 0);

        int mid = (p + q) / 2;
        initNode(mid, fa, segs[mid].b, segs[mid].e);

        t[mid][0] = build(p, mid-1, mid, segs);
        t[mid][1] = build(mid+1, q, mid, segs);

        pushUp(mid);

        return mid;
    }

    int buildSingleNode(int p, int fa, int b, int e) {
        initNode(p, fa, b, e);
        pushUp(p);
        return p;
    }

    void pushUp(int x) {
        assert(x);

        sz[x] = sz[t[x][0]] + sz[t[x][1]] + 1;
        sz2[x] = sz2[t[x][0]] + sz2[t[x][1]] + (end[x] - beg[x]) + 1;
    }

    void updateRev(int x) {
        if (!x) return;

        swap(t[x][0], t[x][1]);
        tag[x] ^= 1;
    }

    void pushDown(int x) {
        if (tag[x]) {
            updateRev(t[x][0]);
            updateRev(t[x][1]);
            tag[x] = 0;
        }
    }

    bool son(int x) const {
        return t[f[x]][0] == x ? 0 : 1;
    }

    void rotate(int x) {
        int y = f[x], z = son(x);

        pushDown(y);
        pushDown(x);

        t[y][z] = t[x][1-z];
        if (t[x][1-z]) f[t[x][1-z]] = y;

        f[x] = f[y];
        if (f[x]) t[f[x]][son(y)] = x;

        f[y] = x; t[x][1-z] = y;
        pushUp(y);
    }

    void splay(int x, int y) {
        pushDown(x);
        while (f[x] != y) {
            if (f[f[x]] != y) {
                if (son(f[x]) == son(x)) rotate(f[x]);
                else rotate(x);
            }
            rotate(x);
        }
        pushUp(x);
        if (!y) root = x;
    }

    // find k-th element (starting from 1)
    int find_by_order(int k) {
        assert(1 <= k && k <= N);
        int x = root;
        while (true) {
            pushDown(x);
            if (sz[t[x][0]] == k-1) return x;
            if (sz[t[x][0]] < k-1) {
                k -= sz[t[x][0]] + 1;
                x = t[x][1];
            } else {
                x = t[x][0];
            }
        }
        assert(false);
        return x;
    }

    int rank(int k) {
        assert(1 <= k && k <= sz2[root]);
        int x = root;
        while (true) {
            pushDown(x);
            if (sz2[t[x][0]] >= k) x = t[x][0];
            else if (k > sz2[x] - sz2[t[x][1]]) {
                k -= sz2[t[x][0]] + (end[x] - beg[x]) + 1;
                x = t[x][1];
            }
            else return beg[x] + k - sz2[t[x][0]] - 1;
        }
        assert(false);
        return x;
    }

    // starting from 1
    int order_of_root() {
        return 1 + sz[t[root][0]];
    }

    // both deletion and insertion must happen on the left child of
    // root's right child
    int del() {
        int y = t[root][1];
        int x = t[y][0];
        t[y][0] = 0;
        pushUp(y);
        pushUp(root);
        f[x] = 0;
        return x;
    }

    void ins(int x) {
        int y = t[root][1];
        t[y][0] = x;
        f[x] = y;
        pushUp(y);
        pushUp(root);
    }

    void print() {
        printf("f: ");
        for (int i = 0; i <= N; i++) {
            printf("%d ", f[i]);
        }
        printf("t: ");
        for (int i = 0; i <= N; i++) {
            printf("(%d %d) ", t[i][0], t[i][1]);
        }
        printf("sz: ");
        for (int i = 0; i <= N; i++) {
            printf("%d ", sz[i]);
        }
        printf("sz2: ");
        for (int i = 0; i <= N; i++) {
            printf("%d ", sz2[i]);
        }
        printf("root: %d", root);
               
        printf("\n");
    }

    int root;
    int N;  // number of elements, 0 (NULL) excluded
    vector<int> f;
    vector<array<int, 2>> t;
    vector<int> sz;
    vector<int> sz2;
    vector<int> tag;
    vector<int> beg;
    vector<int> end;

private:
    void alloc(int cap) {
        f.resize(cap);
        t.resize(cap);
        sz.resize(cap);
        sz2.resize(cap);
        tag.resize(cap);
        beg.resize(cap);
        end.resize(cap);
    }

    void initNode(int p, int fa, int b, int e) {
        f[p] = fa;
        t[p][0] = t[p][1] = 0;
        beg[p] = b;
        end[p] = e;
    }
};

struct Op {
    int type;
    int x;
};

const int MAXN = 200010;

void top(SplayTree &st, int x) {
    st.splay(x, 0);
    x = st.order_of_root();
    int y = st.find_by_order(x-1);
    int z = st.find_by_order(x+1);
    st.splay(y, 0);
    st.splay(z, y);
    x = st.del();

    y = st.find_by_order(1);
    z = st.find_by_order(2);
    st.splay(y, 0);
    st.splay(z, y);
    st.ins(x);
}

void query(SplayTree &st, int x) {
    st.splay(x, 0);
    printf("%d\n", st.sz2[st.t[x][0]]);
}

void calcRank(SplayTree &st, int x) {
    printf("%d\n", st.rank(x)-1);
}

int main() {
    int t;
    scanf("%d", &t);
    SplayTree st(MAXN);
    int nt = 1;
    while (nt <= t) {
        printf("Case %d:\n", nt++);
        int N, Q;
        scanf("%d%d", &N, &Q);
        vector<Op> ops(Q);
        vector<int> persons;
        char cmd[10];
        for (int i = 0; i < Q; i++) {
            int x;
            scanf("%s%d", cmd, &x);
            ops[i].type = cmd[0] == 'T' ? 1 : (cmd[0] == 'Q' ? 2 : 3);
            ops[i].x = x + 1;
            if (ops[i].type != 3) persons.push_back(ops[i].x);
        }
        sort(persons.begin(), persons.end());
        persons.erase(unique(persons.begin(), persons.end()), persons.end());
        vector<Seg> segs(1);
        segs.push_back(Seg(1, 1));
        int prev = 1;
        unordered_map<int, int> idmap;
        for (int x: persons) {
            if (prev < x - 1) segs.push_back(Seg(prev+1, x-1));
            segs.push_back(Seg(x, x));
            prev = x;
            idmap.insert(make_pair(x, segs.size()-1));
        }
        segs.push_back(Seg(prev+1, N+1));
        segs.push_back(Seg(N+2, N+2));

        st.init(segs.size()-1, segs);

        for (const Op &op: ops) {
            int x = op.x;
            switch (op.type) {
                case 1:
                    top(st, idmap.at(x));
                    break;
                case 2:
                    query(st, idmap.at(x));
                    break;
                case 3:
                    calcRank(st, x);
                    break;
                default:
                    assert(0);
                    break;
            }
        }
    }
    return 0;
}
