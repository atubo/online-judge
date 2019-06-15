// https://www.luogu.org/problemnew/show/P3681
// [CERC2016]舞动的盘子 Dancing Disks

#include <bits/stdc++.h>
using namespace std;

struct Range {
    int l, r;
};

struct Data {
    int value;
    int row, col;
    int pos;
    bool operator > (const Data &other) const {
        if (value != other.value) return value > other.value;
        if (row != other.row) return row > other.row;
        if (col != other.col) return col > other.col;
        return pos > other.pos;
    }

    bool operator < (const Data &other) const {
        if (value != other.value) return value < other.value;
        if (row != other.row) return row < other.row;
        if (col != other.col) return col < other.col;
        return pos < other.pos;
    }
};

vector<int> D[6][6];
int N;

void move(int x1, int y1, int x2, int y2, int pos) {
    int r = D[x1][y1].size() - pos;
    for (int i = pos; i < (int)D[x1][y1].size(); i++) {
        D[x2][y2].push_back(D[x1][y1][i]);
    }
    D[x1][y1].erase(D[x1][y1].begin()+pos, D[x1][y1].end());

    for (int x = x1; x < x2; x++) {
        printf("%d %d D %d\n", x+1, y1+1, r);
    }
    for (int y = y1; y < y2; y++) {
        printf("%d %d R %d\n", x2+1, y+1, r);
    }
}

void merge0(int row, int col, const Range ranges[][6]) {
    priority_queue<Data, vector<Data>, less<Data>> pq;
    for (int i = 0; i <= row; i++) {
        for (int j = 0; j <= col; j++) {
            if (i == row && j == col) continue;
            if (ranges[i][j].r > ranges[i][j].l) {
                int pos = ranges[i][j].r-1;
                pq.push({D[i][j][pos], i, j, pos});
            }
        }
    }
    while (!pq.empty()) {
        Data d = pq.top();
        pq.pop();
        move(d.row, d.col, row, col, d.pos);
        if (d.pos > ranges[d.row][d.col].l) {
            pq.push({D[d.row][d.col][d.pos-1], d.row, d.col, d.pos-1});
        }
    }
}

void merge1(int row, int col, const Range ranges[][6]) {
    priority_queue<Data, vector<Data>, greater<Data>> pq;
    for (int i = 0; i <= row; i++) {
        for (int j = 0; j <= col; j++) {
            if (i == row && j == col) continue;
            if (ranges[i][j].r > ranges[i][j].l) {
                int pos = ranges[i][j].r-1;
                pq.push({D[i][j][pos], i, j, pos});
            }
        }
    }
    while (!pq.empty()) {
        Data d = pq.top();
        pq.pop();
        move(d.row, d.col, row, col, d.pos);
        if (d.pos > ranges[d.row][d.col].l) {
            pq.push({D[d.row][d.col][d.pos-1], d.row, d.col, d.pos-1});
        }
    }
}

Range arrange(int row, int col, int order) {
    if (row == 0 && col == 0) {
        int s = D[0][0].size();
        if (s > 0) return {s-1, s};
        return {s, s};
    }
    if (row == 0 && col == 1) {
        int s = D[0][0].size();
        if (s >= 2) {
            if (D[0][0][s-1] > D[0][0][s-2]) {
                if (order == 0) {
                    move(0, 0, 0, 1, s-1);
                    move(0, 0, 0, 1, s-2);
                } else {
                    move(0, 0, 0, 1, s-2);
                }
            } else {
                if (order == 0) {
                    move(0, 0, 0, 1, s-2);
                } else {
                    move(0, 0, 0, 1, s-1);
                    move(0, 0, 0, 1, s-2);
                }
            }
            return {(int)D[0][1].size()-2, (int)D[0][1].size()};
        } else if (s == 1) {
            move(0, 0, 0, 1, s-1);
            return {(int)D[0][1].size()-1, (int)D[0][1].size()};
        } else {
            return {0, 0};
        }
    }
    if (row == 1 && col == 0) {
        int s = D[0][0].size();
        if (s >= 2) {
            if (D[0][0][s-1] > D[0][0][s-2]) {
                if (order == 0) {
                    move(0, 0, 1, 0, s-1);
                    move(0, 0, 1, 0, s-2);
                } else {
                    move(0, 0, 1, 0, s-2);
                }
            } else {
                if (order == 0) {
                    move(0, 0, 1, 0, s-2);
                } else {
                    move(0, 0, 1, 0, s-1);
                    move(0, 0, 1, 0, s-2);
                }
            }
            return {(int)D[1][0].size()-2, (int)D[1][0].size()};
        } else if (s == 1) {
            move(0, 0, 1, 0, s-1);
            return {(int)D[1][0].size()-1, (int)D[1][0].size()};
        } else {
            return {0, 0};
        }
    }
    int start = D[row][col].size();
    int end = start;
    Range ranges[6][6];
    for (int i = row; i >= 0; i--) {
        for (int j = col; j >= 0; j--) {
            if (i == row && j == col) continue;
            ranges[i][j] = arrange(i, j, 1-order);
            end += ranges[i][j].r - ranges[i][j].l;
        }
    }

    if (order == 0) merge0(row, col, ranges);
    else merge1(row, col, ranges);
    return {start, end};
}


int main() {
    scanf("%d", &N);
    for (int i = 0; i < N; i++) {
        int d;
        scanf("%d", &d);
        D[0][0].push_back(d);
    }

    arrange(5, 5, 0);

    return 0;
}
