// https://www.luogu.org/problem/show?pid=1613
// P1613 跑路

#include <inttypes.h>
#include <cstdio>
#include <queue>
#include <vector>
using namespace std;

typedef pair<int, int> PII;

const int MAXP = 64;

class Solution {
private:
    int N, M;
    vector<int64_t> origNbr;
public:
    Solution() {
        scanf("%d %d", &N, &M);
        origNbr.resize(N);
        for (int i = 0; i < M; i++) {
            int u, v;
            scanf("%d %d", &u, &v);
            u--; v--;
            origNbr[u] |= (1LL << v);
        }
    }

    void solve() {
        vector<vector<int64_t> > nbrByK(N);
        for (int i = 0; i < N; i++) {
            nbrByK[i].resize(MAXP);
            nbrByK[i][0] = origNbr[i];
        }

        for (int k = 1; k < MAXP; k++) {
            for (int i = 0; i < N; i++) {
                for (int j = 0; j < N; j++) {
                    if ((nbrByK[i][k-1] >> j) & 1) {
                        nbrByK[i][k] |= nbrByK[j][k-1];
                    }
                }
            }
        }

        vector<int64_t> neighbors(N);
        for (int i = 0; i < N; i++) {
            for (int k = 0; k < MAXP; k++) {
                neighbors[i] |= nbrByK[i][k];
            }
        }

        int ans = -1;
        vector<bool> visited(N, false);
        queue<PII> q;
        q.push(make_pair(0, 0));
        visited[0] = true;
        while (!q.empty()) {
            PII pr = q.front();
            q.pop();
            int u = pr.first;
            int d = pr.second;
            if (u == N-1) {
                ans = d;
                break;
            }

            for (int j = 0; j < N; j++) {
                if (((neighbors[u] >> j) & 1) && !visited[j]) {
                    q.push(make_pair(j, d+1));
                    visited[j] = true;
                }
            }
        }

        printf("%d\n", ans);
    }
};

int main() {
    Solution solution;
    solution.solve();
    return 0;
}
