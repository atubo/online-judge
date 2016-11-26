// http://www.tyvj.cn/p/1011
#include <bits/stdc++.h>
#define DEBUG
using namespace std;

const int MAXN = 50;
const int DX[2] = {-1, 0};
const int DY[2] = {0, -1};
int dp[MAXN][MAXN][MAXN][MAXN];

class Solution {
private:
    int M, N;
    vector<vector<int>> score;
public:
    Solution() {
#ifdef DEBUG
        istream& in = cin;
#else
        ifstream in("message.in");
#endif
        in >> M >> N;
        score.resize(M, vector<int>(N, 0));
        for (int i = 0; i < M; i++) {
            for (int j = 0; j < N; j++) {
                in >> score[i][j];
            }
        }
    }

    bool inRange(int i, int j) {
        return 0 <= i && i < M && 0 <= j && j < N;
    }

    void solve() {
        for (int i = 0; i < M; i++) {
            for (int j = 0; j < N; j++) {
                for (int k = 0; k < M; k++) {
                    for (int l = 0; l < N; l++) {
                        dp[i][j][k][l] = 0;
                        if (i == k && j == l) continue;
                        for (int d1 = 0; d1 < 2; d1++) {
                            for (int d2 = 0; d2 < 2; d2++) {
                                int i0 = i + DX[d1];
                                int j0 = j + DY[d1];
                                int k0 = k + DX[d2];
                                int l0 = l + DY[d2];
                                if (!inRange(i0, j0) || !inRange(k0, l0)) continue;
                                dp[i][j][k][l] = max(dp[i][j][k][l], dp[i0][j0][k0][l0]);
                            }
                        }
                        dp[i][j][k][l] += score[i][j] + score[k][l];
                    }
                }
            }
        }
#ifdef DEBUG
        ostream& out = cout;
#else
        ofstream out("message.out");
#endif
        out << dp[M-1][N-2][M-2][N-1] << endl;
    }
};

int main() {
    Solution solution;
    solution.solve();
    return 0;
}
