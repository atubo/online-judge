// https://www.luogu.org/problem/show?pid=2244
// 选举预测

#include <bits/stdc++.h>
using namespace std;

const int MAXN = 1000010;
int N;
bool isWinner[MAXN];
int head[MAXN];
struct Edge {
    int next, to;
} E[MAXN];
int eidx;
bool vis[MAXN];

class Partitioner {
public:
    Partitioner(int N_):N(N_) {
        v.resize(N);
        index.resize(N);
        rindex.resize(N);
        iota(v.begin(), v.end(), 0);
        iota(index.begin(), index.end(), 0);
        iota(rindex.begin(), rindex.end(), 0);
        pivot = 0;
    }

    void mark(int i) {
        int p = pivot;
        int q = index[i];
        int j = rindex[p];
        swap(rindex[p], rindex[q]);
        swap(v[p], v[q]);
        swap(index[i], index[j]);
        pivot++;
    }

    void commit() {
        N = pivot;
        pivot = 0;
    }

    int N;
    vector<int> v;
    vector<int> index;
    vector<int> rindex;
    int pivot;
};

void addEdge(int u, int v) {
    E[eidx].to = v;
    E[eidx].next = head[u];
    head[u] = eidx++;
}


int bfs(int u) {
    Partitioner part(N);
    queue<int> q;
    q.push(u);
    vis[u] = true;
    int cnt = 0;
    while (!q.empty()) {
        u = q.front();
        q.pop();
        isWinner[u] = true;
        cnt++;
        for (int eidx = head[u]; eidx != -1; eidx = E[eidx].next) {
            int v = E[eidx].to;
            if (!vis[v]) {
                part.mark(v);
            }
        }
        for (int i = part.pivot; i < part.N; i++) {
            int v = part.v[i];
            if (!vis[v]) {
                q.push(v);
                vis[v] = true;
            }
        }
        part.commit();
    }
    return cnt;
}


int main() {
    scanf("%d", &N);
    memset(head, -1, sizeof(head));
    int maxout = 0, maxid = 0;
    for (int i = 0; i < N; i++) {
        int k;
        scanf("%d", &k);
        if (k > maxout) {
            maxout = k;
            maxid  = i;
        }
        while (k--) {
            int u;
            scanf("%d", &u);
            addEdge(i, u-1);
        }
    }

    int cnt = bfs(maxid);
    printf("%d", cnt);
    for (int i = 0; i < N; i++) {
        if (isWinner[i]) printf(" %d", i + 1);
    }
    printf("\n");
    return 0;
}
