// https://www.luogu.org/problem/P4906
// 小奔关闹钟

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

const int MAXN = 20;
int N;
int ALL;
int A[MAXN];
int B[MAXN][MAXN];
bool inq[1<<MAXN];

int bfs1(int s) {
    int ret = (1 << s);
    for (int i = 0; i < N; i++) {
        if (B[s][i] >= 0 && s != i) {
            ret ^= (1 << i);
            for (int j = 0; j < N; j++) {
                if (B[i][j] >= 0 && i != j) {
                    ret ^= (1 << j);
                }
            }
        }
    }
    return ret;
}

void bfs2() {
    int ret = -1;
    queue<pair<int, int>> q;
    q.push(make_pair(0, 0));
    while (!q.empty()) {
        auto p = q.front();
        q.pop();
        int s = p.first;
        int d = p.second;
        if (s == ALL) {
            ret = d;
            break;
        }
        for (int u = 0; u < N; u++) {
            int m = s ^ A[u];
            if (!inq[m]) {
                q.push(make_pair(m, d+1));
                inq[m] = true;
            }
        }
    }
    if (ret >= 0) printf("%d\n", ret);
    else printf("Change an alarm clock, please!\n");
}

int main() {
    memset(B, -1, sizeof(B));
    scanf("%d", &N);
    ALL = (1<<N) - 1;
    Graph g(N, N*(N-1));
    for (int i = 0; i < N; i++) {
        int m;
        scanf("%d", &m);
        for (int j = 0; j < m; j++) {
            int v;
            scanf("%d", &v);
            v--;
            B[i][v] = 1;
        }
    }
    for (int i = 0; i < N; i++) {
        A[i] = bfs1(i);
    }

    bfs2();
    return 0;
}
