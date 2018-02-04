// https://www.luogu.org/problemnew/show/P2346
// 四子连棋

#include <bits/stdc++.h>
using namespace std;

const int DX[4] = {0, -1, 0, 1};
const int DY[4] = {1, 0, -1, 0};
const int ROWMASK[4] = {0xF, 0xF0, 0xF00, 0xF000};
const int COLMASK[4] = {0x1111, 0x2222, 0x4444, 0x8888};
const int DIAMASK1 = 0x8421;
const int DIAMASK2 = 0x1248;

char board[4][4];

int dp[1<<24];

bool inRange(int x, int y) {
    return 0 <= x && x < 4 && 0 <= y && y < 4;
}

void unflatten(int u, int &x, int &y) {
    x = (u >> 2);
    y = (u & 0x3);
}

int flatten(int x, int y) {
    return (x << 2) | y;
}


void decode(int u, int &x1, int &y1, int &x2, int &y2, int &z) {
    unflatten(u>>20, x1, y1);
    unflatten((u>>16) & 0xF, x2, y2);
    z = u & 0xFFFF;
}

int encode(int x1, int y1, int x2, int y2, int z) {
    int f1 = flatten(x1, y1);
    int f2 = flatten(x2, y2);
    if (f1 < f2) swap(f1, f2);
    int ret = z;
    ret |= (f1 << 16);
    ret |= (f2 << 20);
    return ret;
}

int encodeBoard() {
    int ret = 0;
    vector<pair<int, int>> spaces;
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            if (board[i][j] == 'W') {
                ret |= (1 << (i*4+j));
            }
            if (board[i][j] == 'O') {
                spaces.push_back(make_pair(i, j));
            }
        }
    }
    assert(spaces.size() == 2);
    ret = encode(spaces[0].first, spaces[0].second,
                 spaces[1].first, spaces[1].second,
                 ret);
    return ret;
}

int swapBitsCopy(int u, int p, int q) {
    int bitp = (u >> p) & 1;
    int bitq = (u >> q) & 1;
    int ret = u & (~(1 << p));
    ret |= (bitq << p);
    ret &= (~(1 << q));
    ret |= (bitp << q);
    return ret;
}

vector<int> nextMoves(int u, int parity) {
    vector<int> ret;
    int x1, y1, x2, y2, z;
    decode(u, x1, y1, x2, y2, z);
    for (int d = 0; d < 4; d++) {
        int x3 = x1 + DX[d];
        int y3 = y1 + DY[d];
        if (inRange(x3, y3) && !(x3 == x2 && y3 == y2) &&
            ((z >> flatten(x3, y3) & 1) == parity)) {
            int next = swapBitsCopy(z, flatten(x1, y1), flatten(x3, y3));
            next = encode(x3, y3, x2, y2, next);
            ret.push_back(next);
        }
    }
    for (int d = 0; d < 4; d++) {
        int x3 = x2 + DX[d];
        int y3 = y2 + DY[d];
        if (inRange(x3, y3) && !(x3 == x1 && y3 == y1) &&
            ((z >> flatten(x3, y3) & 1) == parity)) {
            int next = swapBitsCopy(z, flatten(x2, y2), flatten(x3, y3));
            next = encode(x3, y3, x1, y1, next);
            ret.push_back(next);
        }
    }
    return ret;
}

bool isTarget(int u) {
    int x1, y1, x2, y2, z;
    decode(u, x1, y1, x2, y2, z);
    // rows
    for (int i = 0; i < 4; i++) {
        if (i == x1 || i == x2) continue;
        int x = z & ROWMASK[i];
        if (x == 0 || x == ROWMASK[i]) return true;
    }
    // cols
    for (int i = 0; i < 4; i++) {
        if (i == y1 || i == y2) continue;
        int x = z & COLMASK[i];
        if (x == 0 || x == COLMASK[i]) return true;
    }
    // diagonal
    if (x1 != y1 && x2 != y2) {
        int x = z & DIAMASK1;
        if (x == 0 || x == DIAMASK1) return true;
    }
    if (x1 + y1 != 3 && x2 + y2 != 3) {
        int x = z & DIAMASK2;
        if (x == 0 || x == DIAMASK2) return true;
    }
    return false;
}

int bfs(int start, int parity) {
    memset(dp, -1, sizeof(dp));
    queue<int> q;
    q.push(start);
    dp[start] = 0;
    while (!q.empty()) {
        int u = q.front();
        int d = dp[u];
        q.pop();
        for (int v: nextMoves(u, (d&1)^parity)) {
            if (isTarget(v)) return d+1;
            if (dp[v] == -1) {
                q.push(v);
                dp[v] = dp[u] + 1;
            }
        }
    }
    return INT_MAX;
}

int main() {
    char line[10];
    for (int i = 0; i < 4; i++) {
        scanf("%s", line);
        for (int j = 0; j < 4; j++) {
            board[i][j] = line[j];
        }
    }

    int start = encodeBoard();
    printf("%d\n", min(bfs(start, 0), bfs(start, 1)));

    return 0;
}
