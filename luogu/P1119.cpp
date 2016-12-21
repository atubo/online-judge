// https://www.luogu.org/problem/show?pid=1119
// 灾后重建

#include <cstdio>
#include <utility>
#include <vector>
using namespace std;

typedef vector<vector<int> > Adj;
typedef pair<int, pair<int, int> > Query;

const int MAXDIST = 123456789;

class Solution {
private:
    int N, M, Q;
    vector<int> T;
    Adj dist;
    vector<Query> queries;
    int curr_v;
    
public:
    Solution() {
        scanf("%d %d", &N, &M);
        T.resize(N);
        for (int i = 0; i < N; i++) {
            scanf("%d", &T[i]);
        }
        
        dist.resize(N);
        for (int i = 0; i < N; i++) {
            dist[i].resize(N, MAXDIST);
        }

        for (int i = 0; i < M; i++) {
            int u, v, w;
            scanf("%d %d %d", &u, &v, &w);
            dist[u][v] = dist[v][u] = w;
        }

        scanf("%d", &Q);
        queries.resize(Q);
        for (int i = 0; i < Q; i++) {
            int x, y, t;
            scanf("%d %d %d", &x, &y, &t);
            queries[i] = make_pair(t, make_pair(x, y));
        }

        curr_v = -1;
    }

    void solve() {
        for (int i = 0; i < Q; i++) {
            int t = queries[i].first;
            int x = queries[i].second.first;
            int y = queries[i].second.second;
            if (T[x] > t || T[y] > t) {
                printf("-1\n");
                continue;
            }
            floyd(t);
            printf("%d\n", dist[x][y] == MAXDIST ? -1 : dist[x][y]);
        }
    }

    void floyd(int t) {
        for (int k = curr_v+1; k < N && T[k] <= t; k++) {
            curr_v = k;
            for (int i = 0; i < N; i++) {
                for (int j = 0; j < N; j++) {
                    if (dist[i][k] + dist[k][j] < dist[i][j]) {
                        dist[i][j] = dist[i][k] + dist[k][j];
                    }
                }
            }
        }
    }
};

int main() {
    Solution solution;
    solution.solve();
    return 0;
}
