// https://www.luogu.org/problemnew/show/P2845
// [USACO15DEC]Switching on the Lights 开关灯

#include <bits/stdc++.h>
using namespace std;

// Note graph node is 0-indexed
class Graph {
public:
    struct Edge {
        int next, to;
    };

    vector<int> head;
    int eidx;
    int N, M;

    Edge *E;

    Graph(int N_, int M_):N(N_), M(M_) {
        head.resize(N);
        eidx = 0;

        for (int i = 0; i < N; i++) {
            head[i] = -1;
        }

        E = new Edge[M]{};
    }

    ~Graph() {
        delete[] E;
    }

    // assume 0-indexed and no duplication
    void addEdge(int u, int v) {
        E[eidx].to = v;
        E[eidx].next = head[u];
        head[u] = eidx++;
    }
};

const int MAXN = 102;
int N, M;
int color[MAXN][MAXN];

const int DX[4] = {0, -1, 0, 1};
const int DY[4] = {1, 0, -1, 0};

int encode(int i, int j) {
    return i * N + j;
}

void decode(int x, int &i, int &j) {
    j = x % N;
    i = x / N;
}

bool inRange(int x, int y) {
    return 0 <= x && x < N && 0 <= y && y < N;
}

int bfs(const Graph &g) {
    queue<int> q;
    q.push(encode(0, 0));
    color[0][0] = 2;
    while (!q.empty()) {
        int c = q.front();
        q.pop();
        int x, y;
        decode(c, x, y);
        for (int d = 0; d < 4; d++) {
            int x2 = x + DX[d];
            int y2 = y + DY[d];
            if (inRange(x2, y2) && color[x2][y2] == 1) {
                color[x2][y2] = 2;
                q.push(encode(x2, y2));
            }
        }
        for (int eidx = g.head[c]; ~eidx; eidx = g.E[eidx].next) {
            int c2 = g.E[eidx].to;
            int x2, y2;
            decode(c2, x2, y2);
            if (color[x2][y2] != 0) continue;
            color[x2][y2] = 1;
            for (int d = 0; d < 4; d++) {
                int x3 = x2 + DX[d];
                int y3 = y2 + DY[d];
                if (inRange(x3, y3) && color[x3][y3] == 2) {
                    color[x2][y2] = 2;
                    q.push(encode(x2, y2));
                    break;
                }
            }
        }
    }
    int ret = 0;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            ret += (color[i][j] != 0);
        }
    }
    return ret;
}

int main() {
    scanf("%d%d", &N, &M);
    Graph g(N*N, M);
    for (int i = 0; i < M; i++) {
        int x1, y1, x2, y2;
        scanf("%d%d%d%d", &x1, &y1, &x2, &y2);
        x1--; y1--; x2--; y2--;
        g.addEdge(encode(x1, y1), encode(x2, y2));
    }
    int ans = bfs(g);
    printf("%d", ans);

    return 0;
}
