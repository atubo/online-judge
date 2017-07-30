// https://leetcode.com/problems/smallest-rectangle-enclosing-black-pixels/description/
// 302. Smallest Rectangle Enclosing Black Pixels

#include <bits/stdc++.h>
using namespace std;

class Solution {
    using PII = pair<int, int>;
public:
    int minArea(vector<vector<char>>& image, int x, int y) {
        const int M = image.size();
        if (M == 0) return 0;
        const int N = image[0].size();
        if (N == 0) return 0;
        int xmin = INT_MAX, xmax = INT_MIN;
        int ymin = INT_MAX, ymax = INT_MIN;

        const int DX[4] = {1, 0, -1, 0};
        const int DY[4] = {0, 1, 0, -1};

        vector<vector<bool>> visited(M, vector<bool>(N));
        queue<PII> q;
        q.push(make_pair(x, y));
        visited[x][y] = true;
        while (!q.empty()) {
            auto pt = q.front();
            q.pop();
            xmin = min(xmin, pt.first);
            ymin = min(ymin, pt.second);
            xmax = max(xmax, pt.first);
            ymax = max(ymax, pt.second);
            for (int d = 0; d < 4; d++) {
                int x2 = pt.first + DX[d];
                int y2 = pt.second + DY[d];
                if (inRange(x2, y2, M, N) && image[x2][y2] == '1' &&
                    !visited[x2][y2]) {
                    q.push(make_pair(x2, y2));
                    visited[x2][y2] = true;
                }
            }
        }
        return (xmax - xmin + 1) * (ymax - ymin + 1);
    }

    bool inRange(int r, int c, int m, int n) {
        return 0 <= r && r < m && 0 <= c && c < n;
    }
};

int main() {
    return 0;
}

