// https://www.luogu.org/problemnew/show/P4030
// [Code+#2]可做题1

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

const int MAXN = 510;
int N, M, T;
int A[MAXN][MAXN], B[MAXN][MAXN];

int main() {
    scanf("%d%d%d", &N, &M, &T);
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            scanf("%d", &A[i][j]);
        }
    }
    FenwickInFenwick ft(N, M);
    for (int i = 1; i < N; i++) {
        for (int j = 0; j < M; j++) {
            B[i][j] = A[i][j] - A[i-1][j];
            if (j > 0 && B[i][j] != B[i][j-1]) {
                ft.add(i+1, j, 1);
            }
        }
    }
    for (int i = 0; i < T; i++) {
        int x, y, k;
        scanf("%d%d%d", &x, &y, &k);
        int cnt = ft.query(x+1, y, x+k-1, y+k-2);
        printf("%c\n", cnt == 0 ? 'Y' : 'N');
    }
    return 0;
}
