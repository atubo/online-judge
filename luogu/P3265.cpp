// https://www.luogu.org/problemnew/show/P3265
// [JLOI2015]装备购买

#include <bits/stdc++.h>
using namespace std;

int64_t gcd(int64_t a, int64_t b) {
    if (b == 0) return a;
    return gcd(b, a % b);
}

const int MAXN = 510;
int N, M;
int A[MAXN][MAXN];

struct Expense {
    int cost, id;
    bool operator < (const Expense &other) const {
        return cost < other.cost ||
            (cost == other.cost && id < other.id);
    }
} expenses[MAXN];

bool isZero(int i) {
    for (int j = 0; j < M; j++) {
        if (A[i][j] != 0) return false;
    }
    return true;
}

void swapCol(int i, int col) {
    int p = col;
    while (p < M && A[i][p] == 0) p++;
    assert(p < M);
    for (int k = 0; k < N; k++) {
        swap(A[k][col], A[k][p]);
    }
}

void combine(const vector<int> &picked, int row) {
    for (int idx = 0; idx < (int)picked.size(); idx++) {
        int i = picked[idx];
        int64_t g = gcd(A[row][idx], A[i][idx]);
        int64_t c1 = A[i][idx] / g;
        int64_t c2 = A[row][idx] / g;
        for (int j = 0; j < M; j++) {
            A[row][j] = A[row][j] * c1 - A[i][j] * c2;
        }
    }
    if (A[row][row] < 0) {
        for (int j = row; j < M; j++) {
            A[row][j] = -A[row][j];
        }
    }
}

pair<int, int> purchase() {
    int cost = 0;
    vector<int> picked;
    for (int idx = 0; idx < N; idx++) {
        int i = expenses[idx].id;
#if 1
        printf("idx=%d i=%d\n", idx, i);
        for (int k1 = 0; k1 < N; k1++) {
            for (int k2 = 0; k2 < M; k2++) {
                printf("%d ", A[k1][k2]);
            }
            printf("\n");
        }
#endif
        combine(picked, i);
        if (isZero(i)) continue;
        swapCol(i, picked.size());
        picked.push_back(i);
        cost += expenses[idx].cost;
    }
    return make_pair(picked.size(), cost);
}

int main() {
    scanf("%d%d", &N, &M);
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            scanf("%d", &A[i][j]);
        }
    }
    for (int i = 0; i < N; i++) {
        expenses[i].id = i;
        scanf("%d", &expenses[i].cost);
    }
    sort(expenses, expenses+N);
    auto ans = purchase();
    printf("%d %d", ans.first, ans.second);
    return 0;
}
