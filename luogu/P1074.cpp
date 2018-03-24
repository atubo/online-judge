// https://www.luogu.org/problemnew/show/P1074
// 靶形数独

#include <bits/stdc++.h>
using namespace std;

int curr[9][9];
int choices[9][9];
int tofill;
int ans = -1;
int start_score;
int score[9][9] = {
    {6, 6, 6, 6, 6, 6, 6, 6, 6},
    {6, 7, 7, 7, 7, 7, 7, 7, 6},
    {6, 7, 8, 8, 8, 8, 8, 7, 6},
    {6, 7, 8, 9, 9, 9, 8, 7, 6},
    {6, 7, 8, 9, 10, 9, 8, 7, 6},
    {6, 7, 8, 9, 9, 9, 8, 7, 6},
    {6, 7, 8, 8, 8, 8, 8, 7, 6},
    {6, 7, 7, 7, 7, 7, 7, 7, 6},
    {6, 6, 6, 6, 6, 6, 6, 6, 6}
};

void calc_choices(int row, int col) {
    choices[row][col] = (1 << 10) - 2;
    for (int j = 0; j < 9; j++) {
        int x = curr[row][j];
        if (x > 0) choices[row][col] &= ~(1 << x);
    }
    for (int i = 0; i < 9; i++) {
        int x = curr[i][col];
        if (x > 0) choices[row][col] &= ~(1 << x);
    }
    for (int i = (row/3)*3; i < (row/3)*3 + 3; i++) {
        for (int j = (col/3)*3; j < (col/3)*3 + 3; j++) {
            int x = curr[i][j];
            if (x > 0) choices[row][col] &= ~(1 << x);
        }
    }
}

void read() {
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            scanf("%d", &curr[i][j]);
        }
    }
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            start_score += curr[i][j] * score[i][j];
            if (curr[i][j] == 0) {
                tofill++;
                calc_choices(i, j);
            }
        }
    }
}

bool prune() {
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            if (curr[i][j] == 0 && choices[i][j] == 0) return true;
        }
    }

    return false;
}

void pick(int &row, int &col) {
    int dmin = INT_MAX;
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            if (curr[i][j] > 0) continue;
            int d = __builtin_popcount(choices[i][j]);
            if (d < dmin) {
                dmin = d;
                row = i;
                col = j;
            }
        }
    }
}

struct ChoiceSave {
    int x[27], y[27], c[27];
    int pos = 0;
    void save(int row, int col) {
        x[pos] = row;
        y[pos] = col;
        c[pos] = choices[row][col];
        ++pos;
    }

    void restore() {
        for (int i = pos-1; i >= 0; i--) {
            choices[x[i]][y[i]] = c[i];
        }
    }
};


void update_choices(int row, int col, int x, ChoiceSave &cs) {
    for (int i = 0; i < 9; i++) {
        cs.save(i, col);
        choices[i][col] &= ~(1 << x);
    }
    for (int j = 0; j < 9; j++) {
        cs.save(row, j);
        choices[row][j] &= ~(1 << x);
    }
    for (int i = (row/3)*3; i < (row/3)*3+3; i++) {
        for (int j = (col/3)*3; j < (col/3)*3+3; j++) {
            cs.save(i, j);
            choices[i][j] &= ~(1 << x);
        }
    }
}

void dfs(int depth, int curr_score) {
    if (depth == 0) {
        ans = max(ans, curr_score);
        return;
    }

    if (prune()) return;
    if (curr_score + depth * 90 < ans) return;
    int row, col;
    pick(row, col);
    for (int x = 9; x > 0; x--) {
        if ((choices[row][col] >> x) & 1) {
            curr[row][col] = x;
            ChoiceSave cs;
            update_choices(row, col, x, cs);
            dfs(depth-1, curr_score + x * score[row][col]);
            cs.restore();
            curr[row][col] = 0;
        }
    }
}

int main() {
    read();
    dfs(tofill, start_score);
    printf("%d\n", ans);
    return 0;
}
