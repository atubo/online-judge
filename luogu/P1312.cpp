// https://www.luogu.org/problemnew/show/P1312
// Mayan游戏

#include <bits/stdc++.h>
using namespace std;

int B[7][9];
int last[6][6][8];
bool clr[6][8];

struct Op {
    int x, y, dir;
} op[6];

void save(int x) {
    for (int i = 1; i <= 5; i++) {
        for (int j = 1; j <= 7; j++) {
            last[x][i][j] = B[i][j];
        }
    }
}

void restore(int x) {
    for (int i = 1; i <= 5; i++) {
        for (int j = 1; j <= 7; j++) {
            B[i][j] = last[x][i][j];
        }
    }
}

void update() {
    for (int i = 1; i <= 5; i++) {
        int x = 0;
        for (int j = 1; j <= 7; j++) {
            if (B[i][j]) {
                if (x) {
                    B[i][j-x] = B[i][j];
                    B[i][j] = 0;
                }
            } else {
                x++;
            }
        }
    }
}

bool rowClear(int i, int j) {
    if (!B[i][j]) return false;
    return B[i-1][j] == B[i][j] && B[i][j] == B[i+1][j];
}

bool colClear(int i, int j) {
    if (!B[i][j]) return false;
    return B[i][j-1] == B[i][j] && B[i][j] == B[i][j+1];
}

bool remove() {
    int flag = 0;
    for (int i = 1; i <= 5; i++) {
        for (int j = 1; j <= 7; j++) {
            if (rowClear(i, j)) {
                clr[i-1][j] = clr[i][j] = clr[i+1][j] = true;
                flag = 1;
            }
            if (colClear(i, j)) {
                clr[i][j-1] = clr[i][j] = clr[i][j+1] = true;
                flag = 1;
            }
        }
    }
    if (!flag) return false;
    for (int i = 1; i <= 5; i++) {
        for (int j = 1; j <= 7; j++) {
            if (clr[i][j]) {
                B[i][j] = 0;
                clr[i][j] = false;
            }
        }
    }
    return true;
}

void move(int i, int j, int x) {
    swap(B[i][j], B[i+x][j]);
    update();
    while (remove()) update();
}

bool check() {
    for (int i = 1; i <= 5; i++) {
        if (B[i][1]) return false;
    }
    return true;
}

int N;

void dfs(int x) {
    if (check()) {
        cerr << "solution!" << endl;
        for (int i = 0; i < x; i++) {
            printf("%d %d %d\n", op[i].x-1, op[i].y-1, op[i].dir);
        }
        for (int i = x; i < N; i++) {
            printf("-1 -1 -1\n");
        }
        exit(0);
    }
    if (x == N) return;
    save(x);
    for (int i = 1; i <= 5; i++) {
        for (int j = 1; j <= 7; j++) {
            if (B[i][j]) {
                if (i < 5 && B[i][j] != B[i+1][j]) {
                    move(i, j, 1);
                    op[x] = {i, j, 1};
                    dfs(x+1);
                    restore(x);
                }
                if (i > 1 && !B[i-1][j]) {
                    move(i, j, -1);
                    op[x] = {i, j, -1};
                    dfs(x+1);
                    restore(x);
                }
            }
        }
    }
}

int main() {
    scanf("%d", &N);
    for (int i = 1; i <= 5; i++) {
        for (int j = 1, c; j <= 8; j++) {
            scanf("%d", &c);
            if (c == 0) break;
            B[i][j] = c;
        }
    }
    dfs(0);
    printf("-1\n");
    return 0;
}
