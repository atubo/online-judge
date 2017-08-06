// https://leetcode.com/problems/bomb-enemy/description/
// 361. Bomb Enemy

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int maxKilledEnemies(vector<vector<char>>& grid) {
        const int M = grid.size();
        if (M == 0) return 0;
        const int N = grid[0].size();
        if (N == 0) return 0;
        vector<vector<int>> lastL(M, vector<int>(N, 0));
        vector<vector<int>> lastR(M, vector<int>(N, 0));
        vector<vector<int>> lastU(M, vector<int>(N, 0));
        vector<vector<int>> lastD(M, vector<int>(N, 0));

        for (int i = 0; i < M; i++) {
            lastL[i][0] = (grid[i][0] == 'W');
            for (int j = 1; j < N; j++) {
                if (grid[i][j] == 'W') lastL[i][j] = j+1;
                else lastL[i][j] = lastL[i][j-1];
            }
            lastR[i][N-1] = (grid[i][N-1] != 'W') + N;
            for (int j = N-2; j >= 0; j--) {
                if (grid[i][j] == 'W') lastR[i][j] = j+1;
                else lastR[i][j] = lastR[i][j+1];
            }
        }

        for (int j = 0; j < N; j++) {
            lastU[0][j] = (grid[0][j] == 'W');
            for (int i = 1; i < M; i++) {
                if (grid[i][j] == 'W') lastU[i][j] = i+1;
                else lastU[i][j] = lastU[i-1][j];
            }
            lastD[M-1][j] = (grid[M-1][j] != 'W') + M;
            for (int i = M-2; i >= 0; i--) {
                if (grid[i][j] == 'W') lastD[i][j] = i+1;
                else lastD[i][j] = lastD[i+1][j];
            }
        }

        vector<vector<int>> psh(M, vector<int>(N+2, 0));
        vector<vector<int>> psv(M+2, vector<int>(N, 0));
        for (int i = 0; i < M; i++) {
            for (int j = 0; j < N; j++) {
                psh[i][j+1] = psh[i][j] + (grid[i][j] == 'E');
            }
            psh[i][N+1] = psh[i][N];
        }

        for (int j = 0; j < N; j++) {
            for (int i = 0; i < M; i++) {
                psv[i+1][j] = psv[i][j] + (grid[i][j] == 'E');
            }
            psv[M+1][j] = psv[M][j];
        }

        int ret = 0;
        for (int i = 0; i < M; i++) {
            for (int j = 0; j < N; j++) {
                if (grid[i][j] != '0') continue;
                int l = lastL[i][j];
                int r = lastR[i][j];
                int u = lastU[i][j];
                int d = lastD[i][j];
                int curr = psh[i][r] - psh[i][l] + psv[d][j] - psv[u][j];
                ret = max(ret, curr);
            }
        }
        return ret;
    }
};

int main() {
    int M;
    cin >> M;
    vector<vector<char>> grid(M);
    for (int i = 0; i < M; i++) {
        string s;
        cin >> s;
        for (char c: s) {
            grid[i].push_back(c);
        }
    }

    Solution solution;
    cout << solution.maxKilledEnemies(grid) << endl;

    return 0;
}
