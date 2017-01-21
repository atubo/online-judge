// https://www.luogu.org/problem/show?pid=2495
// P2495 [SDOI2011]消耗战

#include <algorithm>
#include <climits>
#include <cstdio>
#include <cstring>
#include <vector>
using namespace std;

typedef pair<int, int> PII;

const int64_t INF = 0x7FFFFFFFFFFFFFFF;

const int MAXN = 250000;
int dfn[MAXN], depth[MAXN], vertices[MAXN], stk[MAXN];
int64_t dp[MAXN];
int64_t cost[MAXN];
bool hasResource[MAXN];
PII vEdges[MAXN];
int father[MAXN][20];
int64_t minCost[MAXN][20];
struct Edge {
    int next, to, wt;
} E[MAXN*2];
int head[MAXN], Ecnt;

Edge VE[MAXN];
int VH[MAXN];
int last;

class Solution {
public:
    int N, root;
    int MAXB;
    int sz;

    int veNum;

public:
    Solution() {
        // initialization: N, root and adj
        Ecnt = 0;

        scanf("%d", &N);
        for (int i = 0; i < N; i++) {
            head[i] = -1;
        }

        for (int i = 0; i < N-1; i++) {
            int u, v, w;
            scanf("%d %d %d", &u, &v, &w);
            u--; v--;
            E[Ecnt].to = v;
            E[Ecnt].next = head[u];
            E[Ecnt].wt = w;
            head[u] = Ecnt++;

            E[Ecnt].to = u;
            E[Ecnt].next = head[v];
            E[Ecnt].wt = w;
            head[v] = Ecnt++;
        }
        root = 0;
    }

    void preCompute() {
        MAXB = 0;
        int x = 1;
        while (x <= N) {
           MAXB++;
           x = x * 2;
        }

        for (int i = 0; i < N; i++) {
            for (int j = 0; j < MAXB; j++) {
                father[i][j] = -1;
                minCost[i][j] = INF;
            }
        }

        vector<bool> visited(N, false);
        sz = 0;
        dfs(root, -1, visited, 0, INF);

        binaryLift();

        for (int i = 0; i < N; i++) {
            cost[i] = findCost(i);
        }
    }

    void dfs(int x, int f, vector<bool>& visited, int d, int64_t c) {
        dfn[x] = sz++;
        depth[x] = d;
        father[x][0] = f;
        minCost[x][0] = c;
        visited[x] = true;
        for (int e = head[x]; e != -1; e = E[e].next) {
            int u = E[e].to;
            int w = E[e].wt;
            if (!visited[u]) dfs(u, x, visited, d+1, w);
        }

    }

    void binaryLift() {
        for (int j = 1; j < MAXB; j++) {
            for (int i = 0; i < N; i++) {
                if (father[i][j-1] != -1) {
                    father[i][j] = father[father[i][j-1]][j-1];
                    minCost[i][j] = min(minCost[i][j-1], minCost[father[i][j-1]][j-1]);
                }
            }
        }
    }

    int findLCA(int u, int v) {
        if (depth[u] < depth[v]) swap(u, v);
        for (int b = MAXB-1; b >= 0; b--) {
            if (father[u][b] == -1) continue;
            if (depth[father[u][b]] >= depth[v]) {
                u = father[u][b];
            }
        }

        if (u == v) return u;

        for (int b = MAXB-1; b >= 0; b--) {
            if (father[u][b] == -1) continue;
            if (father[u][b] != father[v][b]) {
                u = father[u][b];
                v = father[v][b];
            }
        }
        return father[u][0];
    }

    int64_t findCost(int u) {
        int64_t ans = INF;
        for (int b = MAXB-1; b >= 0; b--) {
            if (father[u][b] == -1) continue;
            ans = min(ans, minCost[u][b]);
            u = father[u][b];
        }
        return ans;
    }

    static bool cmpByDfn(int i, int j) {
        return dfn[i] < dfn[j];
    }

    int buildVirtualTree(int k) {
        veNum = 0;
        last = vertices[0];

        sz = 0;
        int cnt = k;
        sort(vertices, vertices+k, cmpByDfn);

        for (int i = 0; i < k; i++) {
            int u = vertices[i];
            int lca = (sz > 0 ? findLCA(u, stk[sz-1]) : u);
            if (sz == 0 || lca == stk[sz-1]) {
                VH[u] = -1;
                stk[sz++] = u;
            }
            else {
                while (sz - 2 >= 0 && depth[stk[sz-2]] >= depth[lca]) {
                    addVirtualEdge(stk[sz-2], stk[sz-1]);
                    sz--;
                }

                if (stk[sz-1] != lca) {
                    VH[lca] = -1;
                    addVirtualEdge(lca, stk[--sz]);
                    stk[sz++] = lca;
                    vertices[cnt++] = lca;
                }

                VH[u] = -1;
                stk[sz++] = u;
            }
        }

        for (int i = 0; i < sz-1; i++) {
            addVirtualEdge(stk[i], stk[i+1]);
        }

        return cnt;
    }

    void addVirtualEdge(int u, int v) {
        VE[veNum].to = v;
        VE[veNum].next = VH[u];
        VH[u] = veNum;
        veNum++;
        if (depth[last] > depth[u]) {
            last = u;
        }
    }

    int64_t wave() {
        int k;
        scanf("%d", &k);
        for (int i = 0; i < k; i++) {
            scanf("%d", &vertices[i]);
            vertices[i]--;
        }

        int cnt = buildVirtualTree(k);
        for (int i = 0; i < cnt; i++) {
            dp[vertices[i]] = INF;
            hasResource[vertices[i]] = (i < k);
        }

        return treeDp(last);
    }

    int64_t treeDp(int u) {
        dp[u] = cost[u];
        if (hasResource[u]) {
            return dp[u];
        }

        int64_t subtreeSum = 0;
        for (int e = VH[u]; e != -1; e = VE[e].next) {
            int v = VE[e].to;
            subtreeSum += treeDp(v);
        }
        return dp[u] = min(dp[u], subtreeSum);
    }

    void solve() {
        int m;
        scanf("%d", &m);
        while (m--) {
            printf("%lld\n", wave());
        }
    }
};

int main() {
    Solution solution;
    solution.preCompute();
    solution.solve();
    return 0;
}
