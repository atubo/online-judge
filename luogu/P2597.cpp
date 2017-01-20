// https://www.luogu.org/problem/show?pid=2597
// P2597 [ZJOI2012]灾难

#include <cstdio>
#include <iostream>
#include <stack>
#include <vector>
using namespace std;

class Solution {
public:
    int N;
    vector<vector<int> > out;
    vector<vector<int> > in;
    vector<int> topo;  // topologically sorted result

    int MAXB;
    vector<int> depth;
    vector<vector<int> > father;
    vector<vector<int> > children;

private:
    void topologicalSortUtil(int v, bool visited[],
                             stack<int> &order) {
        visited[v] = true;

        for (int i = 0; i < (int)out[v].size(); i++) {
            int m = out[v][i];
            if (!visited[m]) {
                topologicalSortUtil(m, visited, order);
            }
        }

        order.push(v);
    }

public:
    Solution() {
        scanf("%d", &N);
        out.resize(N+1);
        in.resize(N+1);
        for (int u = 0; u < N; u++) {
            int v;
            while (true) {
                scanf("%d", &v);
                if (v == 0) break;
                v--;
                out[v].push_back(u);
                in[u].push_back(v);
            }
        }

        for (int u = 0; u < N; u++) {
            if (in[u].empty()) {
                in[u].push_back(N);
                out[N].push_back(u);
            }
        }
        N++;

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
        children.resize(N);
    }

    void sort() {
        topo.resize(N);

        stack<int> order;
        bool visited[N];
        for (int i = 0; i < N; i++) {
            visited[i] = false;
        }

        for (int i = 0; i < N; i++) {
            if (!visited[i]) {
                topologicalSortUtil(i, visited, order);
            }
        }

        int i = 0;
        while (!order.empty()) {
            topo[i++] = order.top();
            order.pop();
        }
    }

    void buildExtinctionTree() {
        depth[N-1] = 0;
        for (int i = 0; i < MAXB; i++) {
            father[N-1][i] = -1;
        }

        for (int i = 1; i < N; i++) {
            int u = topo[i];
            int ancestor = in[u][0];
            for (int j = 1; j < (int)in[u].size(); j++) {
                int v = in[u][j];
                ancestor = findLCA(ancestor, v);
            }
            connect(ancestor, u);
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

    void connect(int u, int v) { // u is v's father
        depth[v] = depth[u]+1;
        children[u].push_back(v);

        father[v][0] = u;
        for (int j = 1; j < MAXB; j++) {
            if (father[v][j-1] != -1) {
                father[v][j] = father[father[v][j-1]][j-1];
            }
        }
    }

    void solve() {
        vector<int> sz(N);
        dfs(N-1, sz);
        for (int i = 0; i < N-1; i++) {
            printf("%d\n", sz[i]-1);
        }
    }

    int dfs(int u, vector<int>& sz) {
        int s = 1;
        for (int i = 0; i < (int)children[u].size(); i++) {
            int v = children[u][i];
            s += dfs(v, sz);
        }
        return sz[u] = s;
    }

};

int main() {
    Solution solution;
    solution.sort();
    solution.buildExtinctionTree();
    solution.solve();
    return 0;
}
