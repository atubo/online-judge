// https://www.luogu.org/problemnew/show/P1606
// [USACO07FEB]白银莲花池Lilypad Pond

#include <bits/stdc++.h>
using namespace std;

int M, N;
int A[32][32];
int DX[8] = {-1, -2, -2, -1, 1, 2, 2, 1};
int DY[8] = {2, 1, -1, -2, -2, -1, 1, 2};
int X0, Y0, X1, Y1;
int BEL[32*32];
int D[32*32];
int SRC, DST;
bool ADJ[32*32][32*32];
int IDX;
int64_t P[32*32];

bool inRange(int x, int y) {
    return 0 <= x && x < M && 0 <= y && y < N;
}

int encode(int r, int c) {
    return r*N + c;
}

class UnionFind {
private:
    const int N;
    vector<int> rank;
    vector<int> parent;

    void makeSet(int k) {
        assert(0 <= k && k < N);

        parent[k] = k;
        rank[k] = 0;
    }

    int link(int u, int v) {
        if (u == v) return u;
        if (rank[u] > rank[v]) {
            parent[v] = u;
            return u;
        } else {
            parent[u] = v;
            if (rank[u] == rank[v]) {
                rank[v]++;
            }
            return v;
        }
    }

public:
    UnionFind(int n): N(n) {
        rank.resize(N);
        parent.resize(N);

        reset();
    }

    void reset() {
        for (int i = 0; i < N; i++) {
            makeSet(i);
        }
    }

    int find(int k) {
        if (parent[k] == k) return k;
        int root = find(parent[k]);
        return parent[k] = root;
    }

    int join(int u, int v) {
        return link(find(u), find(v));
    }
};

void build() {
    UnionFind uf(N*M);
    for (int x = 0; x < M; x++) {
        for (int y = 0; y < N; y++) {
            if (A[x][y] == 3) {X0 = x; Y0 = y; continue;}
            if (A[x][y] == 4) {X1 = x; Y1 = y; continue;}
            if (A[x][y] == 2) continue;
            int u = encode(x, y);
            if (A[x][y] == 0) continue;
            for (int d = 0; d < 8; d++) {
                int x2 = x + DX[d];
                int y2 = y + DY[d];
                if (inRange(x2, y2) && A[x2][y2] == 1) {
                    int v = encode(x2, y2);
                    uf.join(u, v);
                }
            }
        }
    }
    memset(BEL, -1, sizeof(BEL));

    for (int x = 0; x < M; x++) {
        for (int y = 0; y < N; y++) {
            if (A[x][y] == 1 || A[x][y] == 2) continue;
            int u = encode(x, y);
            if (x == X0 && y == Y0) {
                SRC = IDX;
            }
            if (x == X1 && y == Y1) {
                DST = IDX;
            }
            BEL[u] = IDX++;
        }
    }

    for (int x = 0; x < M; x++) {
        for (int y = 0; y < N; y++) {
            if (A[x][y] != 1) continue;
            int u = encode(x, y);
            int r = uf.find(u);
            if (BEL[r] == -1) {
                BEL[r] = IDX++;
            }
            BEL[u] = BEL[r];
        }
    }

    map<int, vector<int>> nb;
    for (int x = 0; x < M; x++) {
        for (int y = 0; y < N; y++) {
            if (A[x][y] != 1) continue;
            int u = encode(x, y);
            int r = uf.find(u);
            for (int d = 0; d < 8; d++) {
                int x2 = x + DX[d];
                int y2 = y + DY[d];
                if (inRange(x2, y2) && A[x2][y2] != 2) {
                    nb[r].push_back(BEL[encode(x2, y2)]);
                }
            }
        }
    }

    for (const auto &p: nb) {
        auto v = p.second;
        sort(v.begin(), v.end());
        v.erase(unique(v.begin(), v.end()), v.end());
        const int sz = v.size();
        for (int i = 0; i < sz; i++) {
            for (int j = i+1; j < sz; j++) {
                ADJ[v[i]][v[j]] = ADJ[v[j]][v[i]] = true;
            }
        }
    }

    for (int x = 0; x < M; x++) {
        for (int y = 0; y < N; y++) {
            if (A[x][y] == 1 || A[x][y] == 2) continue;
            int u = encode(x, y);
            for (int d = 0; d < 8; d++) {
                int x2 = x + DX[d];
                int y2 = y + DY[d];
                if (inRange(x2, y2) && (A[x2][y2] != 1 && A[x2][y2] != 2)) {
                    int v = encode(x2, y2);
                    ADJ[BEL[u]][BEL[v]] = ADJ[BEL[v]][BEL[u]] = true;
                }
            }
        }
    }
}

void bfs() {
    queue<int> q;
    q.push(SRC);
    P[SRC] = 1;
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        for (int v = 0; v < IDX; v++) {
            if (ADJ[u][v]) {
                if (D[v] == 0) {
                    D[v] = D[u] + 1;
                    q.push(v);
                }
                if (D[v] == D[u] + 1) P[v] += P[u];
            }
        }
    }

    printf("%d", D[DST]-1);
    if (D[DST] > 0) {
        printf("\n%ld", P[DST]);
    }
}

int main() {
    scanf("%d%d", &M, &N);
    for (int i = 0; i < M; i++) {
        for (int j = 0; j < N; j++) {
            scanf("%d", &A[i][j]);
        }
    }

    build();
    bfs();

    return 0;
}
