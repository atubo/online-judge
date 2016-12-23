// https://www.luogu.org/problem/show?pid=1265
// 公路修建

#include <stdint.h>

#include <algorithm>
#include <cassert>
#include <cmath>
#include <cstdio>
#include <map>
#include <queue>
#include <vector>

using namespace std;


typedef pair<int, int> PII;

const int MAXN = 5010;

int64_t dist[MAXN];
bool visited[MAXN];

class Solution {
private:
    int N;
    vector<PII> cities;
    double totalDist;

public:
    Solution() {
        scanf("%d", &N);
        cities.resize(N);
        for (int i = 0; i < N; i++) {
            scanf("%d %d", &cities[i].first, &cities[i].second);
        }

        for (int i = 0; i < N; i++) {
            dist[i] = calcDist(0, i);
        }

        totalDist = 0;
    }

    int64_t calcDist(int i, int j) {
        int64_t dx = cities[i].first - cities[j].first;
        int64_t dy = cities[i].second - cities[j].second;
        return (dx*dx + dy*dy);
    }

    void solve() {
        prim();
        printf("%.2f\n", totalDist);
    }

    void prim() {
        visited[0] = true;
        for (int i = 0; i < N-1; i++) {
            int64_t mindist = 0x7fffffffffffffffLL;
            int pos = 0;
            for (int j = 0; j < N; j++) {
                if (!visited[j] && dist[j] < mindist) {
                    mindist = dist[j];
                    pos = j;
                }
            }
            visited[pos] = true;
            totalDist += sqrt(double(mindist));

            for (int j = 0; j < N; j++) {
                if (!visited[j]) {
                    dist[j] = min(calcDist(pos, j), dist[j]);
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
