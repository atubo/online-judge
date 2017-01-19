// http://poj.org/problem?id=3368
// Frequent values

#include <climits>
#include <cstdio>
#include <vector>
using namespace std;

const int MAXN = 100000;
int A[MAXN], B[MAXN], first[MAXN], last[MAXN];
int st[MAXN][20];

class Solution {
public:
    int N, MAXB, Q;
    //vector<int> A;
    //vector<vector<int> > st;

public:
    Solution(int N_):N(N_) {
        scanf("%d", &Q);
        //A.resize(N);
        int prev = INT_MIN;
        int idx = 0;
        for (int i = 0; i < N; i++) {
            int x;
            scanf("%d", &x);
            if (x != prev) {
                A[i] = idx;
                B[i] = 1;
                first[idx] = i;
                last[idx] = i;
                prev = x;
                idx++;
            } else {
                A[i] = A[i-1];
                B[i] = B[i-1] + 1;
                last[idx-1] = i;
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

        //st.resize(N);
        for (int i = 0; i < N; i++) {
            //st[i].resize(MAXB, INT_MIN);
            st[i][0] = B[i];
        }

        for (int j = 1; j < MAXB; j++) {
            for (int i = 0; i + (1 << j) - 1 < N; i++) {
                st[i][j] = max(st[i][j-1], st[i+(1<<(j-1))][j-1]);
            }
        }

    }

    int rmq(int u, int v) {
        int j = 0;
        while (u + (1 << (j+1)) < v+1) j++;
        return max(st[u][j], st[v+1-(1<<j)][j]);
    }

    void solve() {
        for (int i = 0; i < Q; i++) {
            int x, y;
            scanf("%d %d", &x, &y);
            x--; y--;
            int ans = 0;
            int u = last[A[x]];
            if (u >= y) {
                ans = B[y] - B[x] + 1;
            } else {
                ans = max(B[u]-B[x]+1, rmq(u+1, y));
            }

            printf("%d\n", ans);
        }
    }
};

int main() {
    int N;
    while (true) {
        scanf("%d", &N);
        if (N == 0) break;
        Solution solution(N);
        solution.preCompute();
        solution.solve();
    }
    return 0;
}
