// https://www.luogu.org/problemnew/show/P3191
// [HNOI2007]紧急疏散EVACUATE

#include <bits/stdc++.h>
using namespace std;

struct Coord {
    int x, y;
};

const int MAXN = 22;
char area[MAXN][MAXN];
int dist[410][410];
int doorIdx[MAXN][MAXN];
int N, M;
int NX, NY;
vector<Coord> doors, cells;

class Dinic {
public:
    static const int inf = 0x3f3f3f3f;
    struct Edge {
        int to, next, cap;
    };

    const int N, MAXM;
    int *head;
    Edge *E;
    int e;
private:
    //static const int MAXM = 1000;
    int *curr;

public:
    Dinic(int N_, int MAXM_): N(N_), MAXM(2*MAXM_) {
        alloc();
        reset();
    }

    ~Dinic() {
        dealloc();
    }

    void reset() {
        e = 0;
        memset(head, -1, N * sizeof(int));
    }

    void addEdge(int x, int y, int w, int rw = 0) {
        E[e] = {y, head[x], w};
        head[x] = e++;
        E[e] = {x, head[y], rw};
        head[y] = e++;
    }

    int dinic(int s, int t) {
        int ans = 0;
        while (bfs(s, t)) {
            for (int i = 0; i < N; i++) {
                curr[i] = head[i];
            }
            int k = dfs(s, inf, t);
            if (k > 0) ans += k;
        }
        return ans;
    }

private:
    void alloc() {
        head = new int[N]{};
        curr = new int[N]{};
        E    = new Edge[MAXM]{};
        d    = new int[N]{};
        q    = new int[N]{};
    }

    void dealloc() {
        delete[] head;
        delete[] curr;
        delete[] E;
        delete[] d;
        delete[] q;
    }

    int *d;
    int *q;

    bool bfs(int s, int t) {
        memset(d, -1, N * sizeof(int));
        int front = 0, back = 0;
        q[back++] = t;

        d[t] = 0;
        while (front != back) {
            int u = q[front];
            front++;
            for (int i = head[u]; i != -1; i = E[i].next) {
                int v = E[i].to;
                if (d[v] == -1 && E[i^1].cap) {
                    d[v] = d[u] + 1;
                    q[back++] = v;
                    if (v == s) return true;
                }
            }
        }
        return false;
    }

    int dfs(int x, int low, int t) {
        if (x == t || !low) return low;
        int ret = 0;
        for (int &i = curr[x]; i != -1; i = E[i].next) {
            int v = E[i].to;
            if (d[v] == d[x] - 1) {
                int k = dfs(v, min(low-ret, E[i].cap), t);
                if (k > 0) {
                    E[i].cap -= k;
                    E[i^1].cap += k;
                    ret += k;
                }
            }
        }
        return ret;
    }
};

struct Item {
    int x, y, d;
};

const int DX[4] = {0, -1, 0, 1};
const int DY[4] = {1, 0, -1, 0};

bool inRange(int x, int y) {
    return 0 <= x && x < N && 0 <= y && y < M;
}

void bfs(int nx) {
    Coord c = cells[nx];
    bool vis[MAXN][MAXN];
    memset(vis, 0, sizeof(vis));
    queue<Item> q;
    q.push({c.x, c.y, 0});
    vis[c.x][c.y] = true;
    while (!q.empty()) {
        Item item = q.front();
        q.pop();
        int x = item.x, y = item.y, d = item.d;
        int ny = doorIdx[x][y];
        if (ny != -1) {
            dist[nx][ny] = d;
            continue;
        }
        for (int dir = 0; dir < 4; dir++) {
            int x2 = x + DX[dir];
            int y2 = y + DY[dir];
            if (inRange(x2, y2) && !vis[x2][y2] && area[x2][y2] != 'X') {
                q.push({x2, y2, d+1});
                vis[x2][y2] = true;
            }
        }
    }
}

int doorNode(int i, int j, int mid) {
    return NX + i * mid + j;
}

bool feasible(int mid) {
    int sz = 2 + NX + NY * mid;
    Dinic dinic(sz, NX + NX*NY + 2 * NY * mid);
    int S = 0, T = sz - 1;
    for (int i = 0; i < NX; i++) {
        dinic.addEdge(S, i+1, 1);
        for (int j = 0; j < NY; j++) {
            if (dist[i][j] >= 0 && dist[i][j] <= mid) {
                dinic.addEdge(i+1, doorNode(j, dist[i][j], mid), 1);
            }
        }
    }

    for (int i = 0; i < NY; i++) {
        for (int j = 1; j < mid; j++) {
            dinic.addEdge(doorNode(i, j, mid), T, 1);
            dinic.addEdge(doorNode(i, j, mid),
                          doorNode(i, j+1, mid), Dinic::inf);
        }
        dinic.addEdge(doorNode(i, mid, mid), T, 1);
    }

    int c = dinic.dinic(S, T);
    return (c == NX);
}
    
void solve() {
    int lo = 0, hi = 400;
    if (!feasible(hi)) {
        printf("impossible\n");
        return;
    }
    while (lo < hi-1) {
        int mid = (lo + hi) / 2;
        if (feasible(mid)) hi = mid;
        else               lo = mid;
    }
    printf("%d\n", hi);
}

int main() {
    memset(doorIdx, -1, sizeof(doorIdx));
    scanf("%d%d", &N, &M);
    for (int i = 0; i < N; i++) {
        scanf("%s", area[i]);
    }
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            if (area[i][j] == 'D') {
                doorIdx[i][j] = doors.size();
                doors.push_back({i, j});
            } else if (area[i][j] == '.') {
                cells.push_back({i, j});
            }
        }
    }
    NX = cells.size(), NY = doors.size();
    if (NX == 0) {
        printf("0\n");
        return 0;
    }
    if (NY == 0) {
        printf("impossible\n");
        return 0;
    }
    memset(dist, -1, sizeof(dist));
    for (int i = 0; i < NX; i++) {
        bfs(i);
    }

    solve();

    return 0;
}
