// https://www.luogu.org/problemnew/show/P3638
// [APIO2013]机器人

#include <bits/stdc++.h>
using namespace std;

const int MAXW = 510;
const int INF = 0x3f3f3f3f;
const int DX[4] = {0, -1, 0, 1};
const int DY[4] = {1, 0, -1, 0};
int N, W, H;
int NP, SZ;
char A[MAXW][MAXW];
int id[MAXW][MAXW];
int P[10];
int E[10][10];
bool *inq;
int **dp;
int *adj2[MAXW*MAXW];
int dp2[MAXW][MAXW][4];
bool vis[MAXW][MAXW][4];


#define PUSH(x) {Q.buf_[Q.back_++]=x; if (Q.back_==Q.MAXSZ) Q.back_ = 0;}
#define POP() {Q.front_++; if (Q.front_ == Q.MAXSZ) Q.front_ = 0;}
#define FRONT() Q.buf_[Q.front_]
#define BACK() Q.buf_[Q.back_-1]
#define EMPTY() (Q.front_ == Q.back_)
#define MIN(x, y) (x)<(y) ? (x):(y)
class Queue {
public:
    inline void push(int x) {
        buf_[back_++] = x;
        if (back_ == MAXSZ) back_ = 0;
    }

    int front() const {
        return buf_[front_];
    }

    void pop() {
        front_++;
        if (front_ == MAXSZ) front_ = 0;
    }

    void clear() {
        front_ = back_ = 0;
    }

    bool empty() const {
        return front_ == back_;
    }

    const static int MAXSZ = MAXW * MAXW;
    int buf_[MAXSZ];
    int front_ = 0, back_ = 0;
} Q;

struct Pos {
    int x, y;
};
class Queue2 {
public:
    inline void push(int x, int y) {
        buf_[back_++] = {x, y};
        if (back_ == MAXSZ) back_ = 0;
    }

    Pos front() const {
        return buf_[front_];
    }

    void pop() {
        front_++;
        if (front_ == MAXSZ) front_ = 0;
    }

    void clear() {
        front_ = back_ = 0;
    }

    bool empty() const {
        return front_ == back_;
    }

    const static int MAXSZ = MAXW * MAXW;
    Pos buf_[MAXSZ];
    int front_ = 0, back_ = 0;
} Q2;

#define INRANGE(x, y) (0 <= x && x < H && 0 <= y && y < W)

pair<int, int> travel(int x0, int y0, int d0) {
    int x = x0, y = y0, d = d0;
    while (true) {
        if (A[x][y] == 'A') d = (d+1) % 4;
        else if (A[x][y] == 'C') d = (d+3) % 4;
        int x1 = x + DX[d];
        int y1 = y + DY[d];
        if (!INRANGE(x1, y1) || A[x1][y1] == 'x') break;
        x = x1;
        y = y1;
        if (x == x0 && y == y0) return {-1, -1};
    }

    return make_pair(x, y);
}

int travel2(int x, int y, int d) {
    if (dp2[x][y][d] != -1) return dp2[x][y][d];
    if (vis[x][y][d]) return dp2[x][y][d] = -2;
    vis[x][y][d] = true;
    int d1 = d;
    if (A[x][y] == 'A') d1 = (d+1) & 3;
    else if (A[x][y] == 'C') d1 = (d+3) & 3;
    int x1 = x + DX[d1];
    int y1 = y + DY[d1];
    if (!INRANGE(x1, y1) || A[x1][y1] == 'x') {
        return dp2[x][y][d] = (x<<9) | y;
    }
    return dp2[x][y][d] = travel2(x1, y1, d1);
}

int encode(int r, int c) {
    return r*NP + c;
}

void build() {
    memset(dp2, -1, sizeof(dp2));
    vector<vector<int>> adj;
    memset(id, -1, sizeof(id));
    int curr = 0;
    for (int i = 0; i < H; i++) {
        for (int j = 0; j < W; j++) {
            if (A[i][j] >= '1' && A[i][j] <= '9') {
                id[i][j] = curr++;
                Q2.push(i, j);
                P[A[i][j]-'1'] = id[i][j];
            }
        }
    }
    NP = curr;

    for (int i = 0; i < NP; i++) {
        for (int j = 0; j < NP; j++) {
            E[i][j] = encode(i, j);
        }
    }

    while (!Q2.empty()) {
        auto p0 = Q2.front();
        int x0 = p0.x;
        int y0 = p0.y;
        Q2.pop();
        int u = id[x0][y0];
        if (u >= (int)adj.size()) adj.resize(u+1);
        for (int d = 0; d < 4; d++) {
#if 0
            auto p1 = travel(x0, y0, d);
            int x1 = p1.first;
            int y1 = p1.second;
            if (x1 == -1 && y1 == -1) continue;
#else
            int p1 = travel2(x0, y0, d);
            if (p1 == -2) continue;
            int x1 = (p1 >> 9);
            int y1 = (p1 & 511);

#endif
            if (id[x1][y1] == -1) {
                id[x1][y1] = curr++;
                Q2.push(x1, y1);
            }
            if (x1 != x0 || y1 != y0) {
                int v = id[x1][y1];
                adj[u].push_back(v);
            }
        }
    }

    SZ = curr;

    for (int u = 0; u < (int)adj.size(); u++) {
        sort(adj[u].begin(), adj[u].end());
        adj[u].erase(unique(adj[u].begin(), adj[u].end()), adj[u].end());
    }
    for (int u = 0; u < (int)adj.size(); u++) {
        int sz = adj[u].size();
        adj2[u] = new int[sz+1]{};
        adj2[u][0] = sz;
        for (int i = 1; i <= sz; i++) {
            adj2[u][i] = adj[u][i-1];
        }
    }
}

void spfa(int *d) {
    while (!EMPTY()) {
        int u = FRONT();
        POP();
        inq[u] = false;
        for (int i = 1; i <= adj2[u][0]; i++) {
            int v = adj2[u][i];
            if (d[v] > d[u]+1) {
                d[v] = d[u]+1;
                if (!inq[v]) {
                    PUSH(v);
                    inq[v] = true;
                }
            }
        }
    }
    Q.clear();
}

struct Data {
    int d, u;
    bool operator < (const Data &other) const {
        if (d != other.d) return d > other.d;
        return u > other.u;
    }
} D[MAXW*MAXW];

void spfa2(int *d, vector<int> &seeds) {
    int sz = 0;
    for (int u: seeds) {
        D[sz++] = {d[u], u};
        inq[u] = true;
    }
    sort(D, D+sz);

    while (sz != 0 || !EMPTY()) {
        int u;
        if (sz == 0) {
            u = FRONT();
            POP();
        } else if (EMPTY()) {
            u = D[sz-1].u;
            sz--;
        } else if (d[D[sz-1].u] < d[FRONT()]) {
            u = D[sz-1].u;
            sz--;
        } else {
            u = FRONT();
            POP();
        }
        inq[u] = false;
        for (int i = 1; i <= adj2[u][0]; i++) {
            int v = adj2[u][i];
            if (d[v] > d[u]+1) {
                d[v] = d[u]+1;
                if (!inq[v]) {
                    PUSH(v);
                    inq[v] = true;
                }
            }
        }
    }

    Q.clear();
}

void steiner() {
    dp = new int*[NP*NP];
    for (int i = 0; i < NP*NP; i++) {
        dp[i] = new int[SZ];
        memset(dp[i], 0x3f, SZ*sizeof(int));
    }
    inq = new bool[SZ]{};

    for (int i = 0; i < NP; i++) {
        dp[E[i][i]][P[i]] = 0;
    }

    for (int w = 1; w <= NP; w++) {
        for (int l = 0; l <= NP-w; l++) {
            vector<int> seeds;
            int r = l + w - 1;
            int s = E[l][r];
            for (int j = 0; j < SZ; j++) {
                for (int k = l; k < r; k++) {
                    dp[s][j] = MIN(
                        dp[s][j],
                        dp[E[l][k]][j] + dp[E[k+1][r]][j]
                        );
                }
                if (dp[s][j] < INF) {
                    //PUSH(j);
                    seeds.push_back(j);
                    //inq[j] = true;
                }
            }
            spfa2(dp[s], seeds);
        }
    }
}

int main() {
    scanf("%d%d%d", &N, &W, &H);
    for (int i = 0; i < H; i++) {
        scanf("%s", A[i]);
    }
    build();

    steiner();
    int ans = INF;
    for (int i = 0; i < SZ; i++) {
        ans = min(ans, dp[E[0][NP-1]][i]);
    }
    if (ans == INF) ans = -1;
    printf("%d\n", ans);
    return 0;
}
