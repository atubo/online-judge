// https://www.luogu.org/problemnew/show/P3265
// [JLOI2015]装备购买

#include <bits/stdc++.h>
using namespace std;

const double EPS = 1e-9;
const int MAXN = 510;
int N, M;
double A[MAXN][MAXN];

struct Expense {
    int cost, id;
    bool operator < (const Expense &other) const {
        return cost < other.cost ||
            (cost == other.cost && id < other.id);
    }
} expenses[MAXN];

bool isZero(int i) {
    bool ret = true;
    for (int j = 0; j < M; j++) {
        if (fabs(A[i][j]) > EPS) ret = false;
        else A[i][j] = 0;
    }
    return ret;
}

void swapCol(int i, int col) {
    int p = col;
    double maxv = fabs(A[i][col]);
    for (int j = col+1; j < M; j++) {
        if (maxv < fabs(A[i][j])) {
            maxv = fabs(A[i][j]);
            p = j;
        }
    }

    for (int k = 0; k < N; k++) {
        swap(A[k][col], A[k][p]);
    }
}

void combine(const vector<int> &picked, int row) {
    for (int idx = 0; idx < (int)picked.size(); idx++) {
        int i = picked[idx];
        double c = - A[row][idx]/A[i][idx];
        for (int j = 0; j < M; j++) {
            A[row][j] += A[i][j] * c;
        }
    }
}

void print() {
    for (int k1 = 0; k1 < N; k1++) {
        for (int k2 = 0; k2 < M; k2++) {
            printf("%lf ", A[k1][k2]);
        }
        printf("\n");
    }
}

pair<int, int> purchase() {
    int cost = 0;
    vector<int> picked;
    for (int idx = 0; idx < N; idx++) {
        int i = expenses[idx].id;
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
            scanf("%lf", &A[i][j]);
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
