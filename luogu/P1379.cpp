// https://www.luogu.org/problemnew/show/P1379
// 八数码难题

#include <bits/stdc++.h>
using namespace std;

const int DX[4] = {0, -1, 0, 1};
const int DY[4] = {1, 0, -1, 0};

unsigned int encode(int pos[8]) {
    unsigned int ans = 0;
    for (int i = 0; i < 8; i++) {
        ans |= (pos[i] << (i*4));
    }
    return ans;
}

void decode(unsigned int code, int pos[8]) {
    for (int i = 0; i < 8; i ++) {
        pos[i] = (code >> (i*4)) & 0xF;
    }
}

bool inRange(int x, int y) {
    return 0 <= x && x < 3 && 0 <= y && y < 3;
}

vector<unsigned int> nextMoves(unsigned int code) {
    int pos[8];
    decode(code, pos);
    int board[3][3];
    memset(board, -1, sizeof(board));
    for (int i = 0; i < 8; i++) {
        int p = pos[i];
        board[p/3][p%3] = i;
    }

    vector<uint32_t> res;
    int x0, y0;
    bool found = false;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (board[i][j] == -1) {
                x0 = i;
                y0 = j;
                found = true;
                break;
            }
        }
        if (found) break;
    }

    for (int d = 0; d < 4; d++) {
        int x1 = x0 + DX[d];
        int y1 = y0 + DY[d];
        if (inRange(x1, y1)) {
            int t = board[x1][y1];
            pos[t] = x0*3 + y0;
            res.push_back(encode(pos));
            pos[t] = x1*3 + y1;
        }
    }
    return res;
}


struct Item {
    unsigned int code;
    int depth;
};

int bfs(unsigned int start, unsigned int end) {
    set<unsigned int> vis;
    queue<Item> q;
    q.push({start, 0});
    vis.insert(start);
    while (!q.empty()) {
        Item item = q.front();
        q.pop();
        if (item.code == end) return item.depth;
        vector<unsigned int> moves = nextMoves(item.code);
        for (const auto &m: moves) {
            if (vis.count(m) == 0) {
                q.push({m, item.depth+1});
                vis.insert(m);
            }
        }
    }
    return -1;
}

uint32_t encodeFromString(const string &s) {
    int pos[8];
    for (int i = 0; i < 9; i++) {
        int t = s[i] - '0';
        if (t) {
            pos[t-1] = i;
        }
    }
    return encode(pos);
}

int main() {
    string s;
    cin >> s;
    uint32_t start = encodeFromString(s);
    uint32_t end = encodeFromString("123804765");
    printf("%d\n", bfs(start, end));
    return 0;
}
