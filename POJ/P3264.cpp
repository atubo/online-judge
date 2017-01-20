// http://poj.org/problem?id=3264
// Balanced Lineup

#include <climits>
#include <cstdio>
#include <vector>
using namespace std;

const int MAXN = 50000;
int A[MAXN];
int stMin[MAXN][20];
int stMax[MAXN][20];

class Solution {
public:
    int N, Q, MAXB;
    //vector<int> A;
    //vector<vector<int> > stMin;
    //vector<vector<int> > stMax;

public:
    Solution() {
        scanf("%d %d", &N, &Q);
        //A.resize(N);
        for (int i = 0; i < N; i++) {
            scanf("%d", &A[i]);
        }
    }

    void preCompute() {
        MAXB = 0;
        int x = 1;
        while (x <= N) {
            MAXB++;
            x = x * 2;
        }

        //stMin.resize(N);
        //stMax.resize(N);
        for (int i = 0; i < N; i++) {
            //stMin[i].resize(MAXB, INT_MAX);
            //stMax[i].resize(MAXB, INT_MIN);
            stMin[i][0] = stMax[i][0] = A[i];
        }

        for (int j = 1; j < MAXB; j++) {
            for (int i = 0; i + (1 << j) - 1 < N; i++) {
                stMin[i][j] = min(stMin[i][j-1], stMin[i+(1<<(j-1))][j-1]);
                stMax[i][j] = max(stMax[i][j-1], stMax[i+(1<<(j-1))][j-1]);
            }
        }
    }

    int rmq(int u, int v) {
        int j = 0;
        while (u + (1 << (j+1)) < v+1) j++;
        return max(stMax[u][j], stMax[v+1-(1<<j)][j]) -
            min(stMin[u][j], stMin[v+1-(1<<j)][j]);
    }

    void solve() {
        for (int i = 0; i < Q; i++) {
            int a, b;
            scanf("%d %d", &a, &b);
            a--; b--;
            printf("%d\n", rmq(a, b));
        }
    }
};

int main() {
    Solution solution;
    solution.preCompute();
    solution.solve();
    return 0;
}
