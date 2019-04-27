// https://www.luogu.org/problemnew/show/P4514
// 上帝造题的七分钟

#include <bits/stdc++.h>
using namespace std;

// note row and col are 1-indexed here
class FenwickInFenwick {
public:
    const int N, M;
    int **root;

    FenwickInFenwick(int N_, int M_): N(N_), M(M_) {
        alloc();
    }

    ~FenwickInFenwick() {
        dealloc();
    }

    // add value t to (x, y)
    void add(int x, int y, int t) {
        if (x == 0 || y == 0) return;
        for (int i = x; i <= N; i += lowbit(i)) {
            addRow(i, y, t);
        }
    }

    // weight sum in region (x1, y1) -> (x2, y2), inclusive
    int64_t query(int x1, int y1, int x2, int y2) const {
        if (x1 > x2 || y1 > y2) return 0;
        return query(x2, y2) - query(x1-1, y2) - query(x2, y1-1) +
            query(x1-1, y1-1);
    }

private:
    void alloc() {
        root = new int*[N+1];
        for (int i = 0; i <= N; i++) {
            root[i] = new int[M+1]{};
        }
    }

    void dealloc() {
        for (int i = 0; i <= N; i++) {
            delete[] root[i];
        }
        delete[] root;
    }

    int lowbit(int x) const {return x & -x;}

    void addRow(int row, int y, int t) {
        for (int i = y; i <= M; i += lowbit(i)) {
            root[row][i] += t;
        }
    }

    // query range (1, 1) -> (x, y) inclusive
    int64_t query(int x, int y) const {
        if (x == 0) return 0;
        int64_t res = 0;
        while (x) {
            res += queryRow(x, y);
            x -= lowbit(x);
        }
        return res;
    }

    int64_t queryRow(int row, int y) const {
        if (y == 0) return 0;
        int64_t res = 0;
        while (y) {
            res += root[row][y];
            y -= lowbit(y);
        }
        return res;
    }
};

int N, M;

void add(FenwickInFenwick &fw0,
         FenwickInFenwick &fw1,
         FenwickInFenwick &fw2,
         FenwickInFenwick &fw3,
         int x, int y, int a) {
    fw0.add(x, y, a);
    fw1.add(x, y, a*x);
    fw2.add(x, y, a*y);
    fw3.add(x, y, a*x*y);
}

int query(const FenwickInFenwick &fw0,
          const FenwickInFenwick &fw1,
          const FenwickInFenwick &fw2,
          const FenwickInFenwick &fw3,
          int x1, int y1, int x2, int y2) {
    int64_t t0 = fw0.query(x1, y1, x2, y2);
    int64_t t1 = fw1.query(x1, y1, x2, y2);
    int64_t t2 = fw2.query(x1, y1, x2, y2);
    int64_t t3 = fw3.query(x1, y1, x2, y2);
    int64_t ans = t3 - t2*(x1-1) - t1*(y1-1) + t0*(x1-1)*(y1-1);

    t0 = fw0.query(x1, y2+1, x2, M);
    t1 = fw1.query(x1, y2+1, x2, M);
    ans += t1*(y2-y1+1) - t0*(x1-1)*(y2-y1+1);

    t0 = fw0.query(x2+1, y1, N, y2);
    t2 = fw2.query(x2+1, y1, N, y2);
    ans += t2*(x2-x1+1) - t0*(x2-x1+1)*(y1-1);

    t0 = fw0.query(x2+1, y2+1, N, M);
    ans += t0*(x2-x1+1)*(y2-y1+1);
    return ans;
}

int main() {
    char cmd[5];
    scanf("%s%d%d", cmd, &N, &M);
    FenwickInFenwick fw0(N, M), fw1(N, M), fw2(N, M), fw3(N, M);
    while (scanf("%s", cmd) > 0) {
        int a, b, c, d, e;
        if (cmd[0] == 'L') {
            scanf("%d%d%d%d%d", &a, &b, &c, &d, &e);
            add(fw0, fw1, fw2, fw3, c, d, e);
            add(fw0, fw1, fw2, fw3, a-1, d, -e);
            add(fw0, fw1, fw2, fw3, c, b-1, -e);
            add(fw0, fw1, fw2, fw3, a-1, b-1, e);
        } else {
            scanf("%d%d%d%d", &a, &b, &c, &d);
            int ans = query(fw0, fw1, fw2, fw3, a, b, c, d);
            printf("%d\n", ans);
        }
    }

    return 0;
}
