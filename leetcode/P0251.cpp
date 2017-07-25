// https://leetcode.com/problems/flatten-2d-vector/#/description
// 251. Flatten 2D Vector

#include <bits/stdc++.h>
using namespace std;

class Vector2D {
public:
    Vector2D(vector<vector<int>>& vec2d_): vec2d(vec2d_) {
        M = vec2d.size();
        row = -1;
        nextLine();
    }

    int next() {
        int ret = vec2d[row][col++];
        if (col == vec2d[row].size()) {
            nextLine();
        }
        return ret;
    }

    bool hasNext() {
        return row < M;
    }

    void nextLine() {
        row++;
        while (row < M && vec2d[row].empty()) row++;
        col = 0;
    }

private:
    const vector<vector<int>>& vec2d;
    int M;
    int row, col;
};

int main() {
    return 0;
}
