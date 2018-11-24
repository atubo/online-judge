#include <bits/stdc++.h>
using namespace std;
#include "../utils/BinaryTree.h"
#include "../utils/Graph.h"
#include "../utils/LinkedList.h"
#include "../utils/Util.h"

class Solution {
    const int DX[4] = {0,  1, 0, -1};
    const int DY[4] = {1, 0, -1, 0};
public:
    vector<vector<int>> floodFill(vector<vector<int>> &image,
                                  int sr, int sc, int newColor) {
        const int nr = image.size();
        const int nc = image[0].size();
        vector<vector<int>> ret(nr);
        for (int i = 0; i < nr; i++) ret[i].resize(nc);
        queue<pair<int, int>> q;
        ret[sr][sc] = -1;
        q.push({sr, sc});
        while (!q.empty()) {
            int x, y;
            tie(x, y) = q.front();
            q.pop();
            for (int d = 0; d < 4; d++) {
                int x2 = x + DX[d];
                int y2 = y + DY[d];
                if (inRange(x2, y2, nr, nc) && ret[x2][y2] != -1 &&
                    image[x2][y2] == image[x][y]) {
                    ret[x2][y2] = -1;
                    q.push({x2, y2});
                }
            }
        }

        for (int i = 0; i < nr; i++) {
            for (int j = 0; j < nc; j++) {
                ret[i][j] = (ret[i][j] == -1 ? newColor : image[i][j]);
            }
        }
        return ret;
    }
private:
    bool inRange(int x, int y, int nr, int nc) {
        return 0 <= x && x < nr && 0 <= y && y < nc;
    }
};

int main() {
    Solution solution;
    return 0;
}
