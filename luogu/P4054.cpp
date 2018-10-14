// https://www.luogu.org/problemnew/show/P4054
// [JSOI2009]计数问题

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
        for (int i = x; i <= N; i += lowbit(i)) {
            addRow(i, y, t);
        }
    }

    // weight sum in region (x1, y1) -> (x2, y2), inclusive
    int query(int x1, int y1, int x2, int y2) {
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
    int query(int x, int y) const {
        if (x == 0) return 0;
        int res = 0;
        while (x) {
            res += queryRow(x, y);
            x -= lowbit(x);
        }
        return res;
    }

    int queryRow(int row, int y) const {
        if (y == 0) return 0;
        int res = 0;
        while (y) {
            res += root[row][y];
            y -= lowbit(y);
        }
        return res;
    }
};

const int MAXN = 310, MAXQ = 200010;
int N, M;
int A[MAXN][MAXN], B[MAXN][MAXN];
int Q;

struct Query {
    int t, x, y, x2, y2, id;
} queries[MAXQ];


int main() {
    scanf("%d%d", &N, &M);
    for (int i = 1; i <= N; i++) {
        for (int j = 1; j <= M; j++) {
            scanf("%d", &A[i][j]);
            B[i][j] = --A[i][j];
        }
    }
    scanf("%d", &Q);
    vector<vector<Query>> color_query(100);
    int curr = 0;
    for (int i = 0; i < Q; i++) {
        int t;
        scanf("%d", &t);
        if (t == 1) {
            int x, y, c;
            scanf("%d%d%d", &x, &y, &c);
            c--;
            int c1 = A[x][y];
            A[x][y] = c;
            color_query[c1].push_back({-1, x, y, -1, -1, -1});
            color_query[c].push_back({1, x, y, -1, -1, -1});
        } else {
            int x1, x2, y1, y2, c;
            scanf("%d%d%d%d%d", &x1, &x2, &y1, &y2, &c);
            c--;
            color_query[c].push_back({0, x1, y1, x2, y2, curr++});
        }
    }

    vector<int> ans(curr);
    for (int c = 0; c < 100; c++) {
        if (color_query[c].empty()) continue;
        FenwickInFenwick ft(N, M);
        for (int i = 1; i <= N; i++) {
            for (int j = 1; j <= M; j++) {
                if (B[i][j] == c) ft.add(i, j, 1);
            }
        }

        for (const auto &q: color_query[c]) {
            if (q.t == 0) {
                ans[q.id] = ft.query(q.x, q.y, q.x2, q.y2);
            } else {
                ft.add(q.x, q.y, q.t);
            }
        }
    }

    for (int i = 0; i < curr; i++) {
        printf("%d\n", ans[i]);
    }

    return 0;
}
