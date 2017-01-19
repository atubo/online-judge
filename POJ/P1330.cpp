// http://poj.org/problem?id=1330
// Nearest Common Ancestors

#include <cstdio>
#include <vector>
using namespace std;

vector<vector<int> > adj(10000);

class Solution {
public:
    int N, root;
    int MAXB;
    //vector<vector<int> > adj;
    vector<int> depth;
    vector<vector<int> > father;

public:
    Solution() {
        scanf("%d", &N);
        for (int i = 0; i < N; i++) {
            adj[i].clear();
        }
        vector<bool> isRoot(N, true);
        for (int i = 0; i < N-1; i++) {
            int x, y;
            scanf("%d %d", &x, &y);
            x--; y--;
            adj[x].push_back(y);
            adj[y].push_back(x);
            isRoot[y] = false;
        }

        for (int i = 0; i < N; i++) {
            if (isRoot[i]) {
                root = i;
                break;
            }
        }
    }

    void preCompute() {
        MAXB = 0;
        int x = 1;
        while (x <= N) {
           MAXB++;
           x = x * 2;
        }

        depth.resize(N);
        father.resize(N);
        for (int i = 0; i < N; i++) {
            father[i].resize(MAXB, -1);
        }

        vector<bool> visited(N, false);
        dfs(root, -1, visited, 0);

        binaryLift();
    }

    void dfs(int x, int f, vector<bool>& visited, int d) {
        depth[x] = d;
        father[x][0] = f;
        visited[x] = true;
        for (int i = 0; i < (int)adj[x].size(); i++) {
            int u = adj[x][i];
            if (!visited[u]) dfs(u, x, visited, d+1);
        }
    }

    void binaryLift() {
        for (int j = 1; j < MAXB; j++) {
            for (int i = 0; i < N; i++) {
                if (father[i][j-1] != -1) {
                    father[i][j] = father[father[i][j-1]][j-1];
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

    void solve() {
        int x, y;
        scanf("%d %d", &x, &y);
        printf("%d\n", findLCA(x-1, y-1)+1);
    }
};

int main() {
    int T;
    scanf("%d", &T);
    while (T--) {
        Solution solution;
        solution.preCompute();
        solution.solve();
    }
    return 0;
}
