// https://www.luogu.org/problemnew/show/P2468
// [SDOI2010]粟粟的书架

#include <bits/stdc++.h>
using namespace std;

class PersistentSegmentTree {
public:
    struct Node {
        // L and R are indices of its children
        // real left and right boundaries are not kept in the node
        // to save memory
        int L, R;
        int cnt, sum;

        Node(): L(0), R(0), cnt(0), sum(0) {}
    };

    int N; // number of positions, index is 1-based
    int M; // number of weights, index is 0-based
    int *root;
    Node *T;
    int T_cnt = 1;

    PersistentSegmentTree(int N_, int M_): N(N_), M(M_) {
        root = new int[N+1]{};
        T = new Node[(N+1) * int(log2(M)+2)]{};
    }

    ~PersistentSegmentTree() {
        delete[] root;
        delete[] T;
    }

    // for user's convenience
    void insert(int currRootIndex, int prevRootIndex, int x, int t) {
        root[currRootIndex] = root[prevRootIndex];
        insert(root[currRootIndex], x, t, 0, M-1);
    }

    // query in range [start, end]
    int query(int rootIndex, int start, int end) {
        return query(root[rootIndex], start, end, 0, M-1);
    }

    int query2(int y1, int y2, int h) {
        return query2(root[y1], root[y2], h, 0, M-1);
    }

    int query2(int node1, int node2, int h, int l, int r) {
        if (l == r) {
            int x = T[node2].sum/T[node2].cnt;
            return (h + x - 1) / x;
        }
        int mid = (l + r) / 2;
        int rightSum = T[T[node2].R].sum - T[T[node1].R].sum;
        int rightCnt = T[T[node2].R].cnt - T[T[node1].R].cnt;
        if (rightSum >= h) {
            return query2(T[node1].R, T[node2].R, h, mid+1, r);
        } else {
            int ret = query2(T[node1].L, T[node2].L, h-rightSum, l, mid);
            return ret + rightCnt;
        }
    }


private:
    // insert a new weight node x with value t
    // current range is [l, r]
    void insert(int &now, int x, int t, int l, int r) {
        T[T_cnt++] = T[now];
        now = T_cnt-1;
        T[now].sum += t;
        T[now].cnt += 1;
        if (l == r) return;
        int mid = (l + r) / 2;
        if (x <= mid) insert(T[now].L, x, t, l, mid);
        else          insert(T[now].R, x, t, mid+1, r);
    }

    int query(int node, int start, int end, int l, int r) {
        if (l > r) return 0;
        if (start <= l && r <= end) return T[node].sum;
        int mid = (l + r) / 2;
        int ret = 0;
        if (start <= mid) ret += query(T[node].L, start, end, l, mid);
        if (mid+1 <= end) ret += query(T[node].R, start, end, mid+1, r);
        return ret;
    }
};

int R, C, M;
int H1[500010], Htmp[500010];
int H2[210][210];

void solve1d() {
    for (int i = 0; i < C; i++) {
        scanf("%d", &H1[i]);
        Htmp[i] = H1[i];
    }
    sort(Htmp, Htmp + C);
    int *endp = unique(Htmp, Htmp+C);
    /*
    for (int i = 0; i < C; i++) {
        printf("%d %d\n", H1[i], lower_bound(Htmp, endp, H1[i]) - Htmp);
    }
    */
    const int wmax = endp - Htmp;
    PersistentSegmentTree pst(C, wmax);
    for (int i = 1; i <= C; i++) {
        int x = lower_bound(Htmp, endp, H1[i-1]) - Htmp;
        pst.insert(i, i-1, x, H1[i-1]);
    }

    for (int i = 0; i < M; i++) {
        int x1, y1, x2, y2, h;
        scanf("%d%d%d%d%d", &x1, &y1, &x2, &y2, &h);
        if (pst.query(y2, 0, wmax-1) - pst.query(y1-1, 0, wmax-1) < h) {
            printf("Poor QLW\n");
            continue;
        } else {
            printf("%d\n", pst.query2(y1-1, y2, h));
        }
    }
}

// note all indices are 1-based
class Fenwick3D {
public:
    const int Nx, Ny, Nz;
    int ***root;

    Fenwick3D(int Nx_, int Ny_, int Nz_): Nx(Nx_), Ny(Ny_), Nz(Nz_) {
        alloc();
    }

    ~Fenwick3D() {
        dealloc();
    }

    void add(int x, int y, int z, int t) {
        for (int i = x; i <= Nx; i += lowbit(i)) {
            addx(i, y, z, t);
        }
    }

    int query(int x1, int y1, int z1, int x2, int y2, int z2) const {
        if (x1 > x2 || y1 > y2 || z1 > z2) return 0;
        int res2 = query(x2, y2, z2) - query(x1-1, y2, z2) -
            query(x2, y1-1, z2) + query(x1-1, y1-1, z2);
        int res1 = query(x2, y2, z1-1) - query(x1-1, y2, z1-1) -
            query(x2, y1-1, z1-1) + query(x1-1, y1-1, z1-1);
        return res2 - res1;
    }

    // query range (1, 1) -> (x, y, z) inclusive
    int query(int x, int y, int z) const {
        int res = 0;
        while (x) {
            res += queryx(x, y, z);
            x -= lowbit(x);
        }
        return res;
    }

private:
    void alloc() {
        root = new int**[Nx+1];
        for (int i = 0; i <= Nx; i++) {
            root[i] = new int*[Ny+1];
            for (int j = 0; j <= Ny; j++) {
                root[i][j] = new int[Nz+1]{};
            }
        }
    }

    void dealloc() {
        for (int i = 0; i <= Nx; i++) {
            for (int j = 0; j <= Ny; j++) {
                delete[] root[i][j];
            }
            delete[] root[i];
        }
        delete[] root;
    }

    int lowbit(int x) const {return x & -x;}

    void addx(int x, int y, int z, int t) {
        for (int i = y; i <= Ny; i += lowbit(i)) {
            addy(x, i, z, t);
        }
    }

    void addy(int x, int y, int z, int t) {
        for (int i = z; i <= Nz; i+= lowbit(i)) {
            root[x][y][i] += t;
        }
    }

    int queryx(int x, int y, int z) const {
        int res = 0;
        while (y) {
            res += queryy(x, y, z);
            y -= lowbit(y);
        }
        return res;
    }

    int queryy(int x, int y, int z) const {
        int res = 0;
        while (z) {
            res += root[x][y][z];
            z -= lowbit(z);
        }
        return res;
    }
};

void solve2d() {
    Fenwick3D ftsum(R, C, 1000);
    Fenwick3D ftcnt(R, C, 1000);
    for (int i = 0, idx = 0; i < R; i++) {
        for (int j = 0; j < C; j++) {
           scanf("%d", &H2[i][j]);
           Htmp[idx++] = H2[i][j];
        }
    }
    sort(Htmp, Htmp + R*C, greater<int>());
    int *endp = unique(Htmp, Htmp + R*C);
    const int wmax = endp - Htmp;
    for (int i = 0; i < R; i++) {
        for (int j = 0; j < C; j++) {
            int x = lower_bound(Htmp, endp, H2[i][j], greater<int>()) - Htmp;
            ftsum.add(i+1, j+1, x+1, H2[i][j]);
            ftcnt.add(i+1, j+1, x+1, 1);
        }
    }

    for (int i = 0; i < M; i++) {
        int x1, y1, x2, y2, h;
        scanf("%d%d%d%d%d", &x1, &y1, &x2, &y2, &h);
        if (ftsum.query(x1, y1, 1, x2, y2, wmax) < h) {
            printf("Poor QLW\n");
            continue;
        } else {
            int lo = 0, hi = wmax;
            while (lo < hi - 1) {
                int mid = (lo + hi) / 2;
                int ht = ftsum.query(x1, y1, 1, x2, y2, mid);
                //printf("mid=%d ht=%d\n", mid, ht);
                if (ht < h) lo = mid;
                else hi = mid;
            }
            int cntlo = ftcnt.query(x1, y1, 1, x2, y2, lo);
            int sumlo = ftsum.query(x1, y1, 1, x2, y2, lo);
            int hlast = Htmp[hi-1];
            //printf("hi=%d lo=%d cntlo=%d sumlo=%d hlast=%d\n",
            //       hi, lo, cntlo, sumlo, hlast);
            int ans = cntlo + (h - sumlo + hlast - 1) / hlast;
            printf("%d\n", ans);
        }
    }
}

int main() {
    scanf("%d%d%d", &R, &C, &M);
    if (R == 1) solve1d();
    else solve2d();
    return 0;
}
