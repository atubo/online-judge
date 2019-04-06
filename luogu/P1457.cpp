// https://www.luogu.org/problemnew/show/P1457
// 城堡 The Castle

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

const int DX[4] = {0, -1, 0, 1};
const int DY[4] = {-1, 0, 1, 0};
const int MAXN = 52;
int N, M;
int A[MAXN][MAXN], B[MAXN][MAXN], C[MAXN*MAXN];

int encode(int i, int j) {
    return i * M + j;
}

void decode(int x, int &i, int &j) {
    j = x % M;
    i = x / M;
}

bool inRange(int x, int y) {
    return 0 <= x && x < N && 0 <= y && y < M;
}

void connect(Graph &g, int r, int c, int d) {
    int r2 = r + DX[d];
    int c2 = c + DY[d];
    if (inRange(r2, c2)) {
        g.addEdge(encode(r, c), encode(r2, c2));
    }
}

int dfs(const Graph &g, int r, int c, int id) {
    int ret = 1;
    B[r][c] = id;
    int u = encode(r, c);
    for (int eidx = g.head[u]; ~eidx; eidx = g.E[eidx].next) {
        int v = g.E[eidx].to;
        int r2, c2;
        decode(v, r2, c2);
        if (B[r2][c2] == -1) ret += dfs(g, r2, c2, id);
    }
    return ret;
}

int main() {
    memset(B, -1, sizeof(B));
    scanf("%d%d", &M, &N);
    Graph g(N*M, N*M*4);
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            int w;
            scanf("%d", &w);
            for (int d = 0; d < 4; d++) {
                if (((w >> d) & 1) == 0) connect(g, i, j, d);
            }
        }
    }

    int id = 0;
    int maxsz = 0;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            if (B[i][j] == -1) {
                C[id] = dfs(g, i, j, id);
                maxsz = max(maxsz, C[id]);
                id++;
            }
        }
    }

    printf("%d\n%d\n", id, maxsz);

    int mx = 0;
    int mi = -1, mj = -1, md = -1;
    for (int j = 0; j < M; j++) {
        for (int i = N-1; i >= 0; i--) {
            if (i > 0 && B[i][j] != B[i-1][j] &&
                C[B[i][j]] + C[B[i-1][j]] > mx) {
                mx = C[B[i][j]] + C[B[i-1][j]];
                mi = i;
                mj = j;
                md = 0;
            }
            if (j < M-1 && B[i][j] != B[i][j+1] &&
                C[B[i][j]] + C[B[i][j+1]] > mx) {
                mx = C[B[i][j]] + C[B[i][j+1]];
                mi = i;
                mj = j;
                md = 1;
            }
        }
    }
    printf("%d\n", mx);
    printf("%d %d %c\n", mi+1, mj+1, "NE"[md]);

    return 0;
}
