// https://www.luogu.org/problemnew/show/P4011
// 孤岛营救问题

#include <bits/stdc++.h>
using namespace std;

const int DX[4] = {0, 1, 0, -1};
const int DY[4] = {1, 0, -1, 0};
const int MAXN = 12;
int N, M, P, K, S;
int V[MAXN][MAXN], H[MAXN][MAXN];
bool vis[100*1024];
vector<vector<vector<int>>> maze(MAXN, vector<vector<int>>(MAXN));

struct Node {
    int x, y, z, d;
};

int encode(int x, int y, int z) {
    return ((x*M + y) << 10) | z;
}

bool canPass(int x1, int y1, int x2, int y2, int z) {
    if (x1 == x2) {
        if (y1 > y2) swap(y1, y2);
        if (H[x1][y1] == 0) return false;
        return H[x1][y1] == -1 || ((z >> (H[x1][y1]-1)) & 1);
    } else {
        if (x1 > x2) swap(x1, x2);
        if (V[x1][y1] == 0) return false;
        return V[x1][y1] == -1 || ((z >> (V[x1][y1]-1)) & 1);
    }
}

bool inRange(int x, int y) {
    return 0 <= x && x < N && 0 <= y && y < M;
}

int bfs() {
    queue<Node> q;
    q.push({0, 0, 0, 0});
    vis[0] = true;
    while (!q.empty()) {
        auto node = q.front();
        q.pop();
        int x = node.x, y = node.y, z = node.z, d = node.d;
        if (x == N-1 && y == M-1) return d;
        for (int dir = 0; dir < 4; dir++) {
            int x2 = x + DX[dir];
            int y2 = y + DY[dir];
            if (inRange(x2, y2) && canPass(x, y, x2, y2, z) &&
                !vis[encode(x2, y2, z)]) {
                q.push({x2, y2, z, d+1});
                vis[encode(x2, y2, z)] = true;
            }
            for (int k: maze[x][y]) {
                if ((z >> (k-1)) & 1) continue;
                int z2 = z | (1<<(k-1));
                int code = encode(x, y, z2);
                if (!vis[code]) {
                    q.push({x, y, z2, d});
                    vis[code] = true;
                }
            }
        }
    }
    return -1;
}

int main() {
    memset(V, -1, sizeof(V));
    memset(H, -1, sizeof(H));
    scanf("%d%d%d", &N, &M, &P);
    scanf("%d", &K);
    for (int i = 0; i < K; i++) {
        int x1, y1, x2, y2, g;
        scanf("%d%d%d%d%d", &x1, &y1, &x2, &y2, &g);
        x1--; y1--; x2--; y2--;
        if (x1 == x2) {
            if (y1 > y2) swap(y1, y2);
            H[x1][y1] = g;
        } else {
            if (x1 > x2) swap(x1, x2);
            V[x1][y1] = g;
        }
    }

    scanf("%d", &S);
    for (int i = 0; i < S; i++) {
        int x, y, q;
        scanf("%d%d%d", &x, &y, &q);
        x--; y--;
        maze[x][y].push_back(q);
    }

    int ans = bfs();
    printf("%d\n", ans);

    return 0;
}
