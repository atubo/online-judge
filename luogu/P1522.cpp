// https://www.luogu.org/problem/show?pid=1522
// 牛的旅行 Cow Tours

#include <cmath>
#include <cstdio>
#include <utility>
#include <vector>
using namespace std;

typedef pair<int, int> PII;
typedef vector<vector<double> > Adj;

const double MAXDIST = 123456789;

class Solution {
private:
    int N;
    vector<PII> pastures;
    Adj dist;
    vector<double> radius;
    vector<double> diameters;   // diameter of the component that i is in

public:
    Solution() {
        scanf("%d", &N);
        pastures.resize(N);
        for (int i = 0; i < N; i++) {
            int x, y;
            scanf("%d %d", &x, &y);
            pastures[i] = make_pair(x, y);
        }

        dist.resize(N);
        for (int i = 0; i < N; i++) dist[i].resize(N, MAXDIST);

        for (int i = 0; i < N; i++) {
            char s[N];
            scanf("%s", s);
            dist[i][i] = 0;
            for (int j = 0; j < N; j++) {
                if (s[j] == '1') {
                    dist[i][j] = dist[j][i] = calcDist(i, j);
                }
            }
        }

        radius.resize(N, 0);
        diameters.resize(N, 0);
    }

    double calcDist(int i, int j) {
        double dx = pastures[i].first - pastures[j].first;
        double dy = pastures[i].second - pastures[j].second;
        return sqrt(dx * dx + dy * dy);
    }

    void solve() {
        floyd();
        calcRadius();
        calcDiameters();

        double minDiameter = MAXDIST;
        for (int i = 0; i < N-1; i++) {
            for (int j = i+1; j < N; j++) {
                if (dist[i][j] < MAXDIST) continue;
                double d = max(diameters[i], diameters[j]);
                d = max(d, radius[i] + calcDist(i, j) + radius[j]);
                minDiameter = min(minDiameter, d);
            }
        }
        printf("%.6f\n", minDiameter);
    }

    void floyd() {
        for (int k = 0; k < N; k++) {
            for (int i = 0; i < N; i++) {
                for (int j = 0; j < N; j++) {
                    if (dist[i][k] + dist[k][j] < dist[i][j]) {
                        dist[i][j] = dist[i][k] + dist[k][j];
                    }
                }
            }
        }
    }

    void calcRadius() {
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                if (dist[i][j] < MAXDIST) {
                    radius[i] = max(radius[i], dist[i][j]);
                }
            }
        }
    }

    void calcDiameters() {
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                if (dist[i][j] < MAXDIST) {
                    diameters[i] = max(diameters[i], radius[j]);
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
