// https://www.luogu.org/problem/show?pid=1525
// P1525 关押罪犯

#include <algorithm>
#include <cstdio>
#include <cstring>
#include <utility>
#include <vector>
using namespace std;

typedef pair<int, int> PII;
typedef vector<vector<PII> > Adj;

const int MAXN = 20010;
char color[MAXN];

class Solution {
private:
    int N, M;
    Adj adj;
    vector<int> C;
public:
    Solution() {
        scanf("%d %d", &N, &M);
        adj.resize(N);
        C.resize(M);

        for (int i = 0; i < M; i++) {
            int a, b, c;
            scanf("%d %d %d", &a, &b, &c);
            a--; b--;
            adj[a].push_back(make_pair(b, c));
            adj[b].push_back(make_pair(a, c));
            C[i] = c;
        }

        sort(C.begin(), C.end());
        C.erase(unique(C.begin(), C.end()), C.end());
    }

    bool dfs(int u, int c, int w) {
        color[u] = c;
        for (int i = 0; i < (int)adj[u].size(); i++) {
            int v = adj[u][i].first;
            int wt = adj[u][i].second;
            if (wt < w || color[v] == 3-c) continue;
            if (color[v] == c) return false;
            if (!dfs(v, 3-c, w)) return false;
        }
        return true;
    }

    bool feasible(int w) {
        memset(color, 0, N*sizeof(char));
        for (int i = 0; i < N; i++) {
            if (color[i] == 0) {
                if (!dfs(i, 1, w)) return false;
            }
        }
        return true;
    }

    int solve() {
        int lo = 0, hi = C.size()-1;
        if (feasible(C[lo])) return 0;
        if (!feasible(C[hi])) return C[hi];
        while (lo < hi-1) {
            int mid = (lo + hi) / 2;
            if (feasible(C[mid])) hi = mid;
            else lo = mid;
        }
        return C[lo];
    }
};

int main() {
    Solution solution;
    printf("%d\n", solution.solve());
    return 0;
}
