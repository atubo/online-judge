// https://leetcode.com/problems/zigzag-iterator/#/description
// 281. Zigzag Iterator

#include <bits/stdc++.h>
using namespace std;

class ZigzagIterator {
public:
    ZigzagIterator(vector<int>& v1_, vector<int>& v2_): v1(v1_), v2(v2_) {
        row = (v1.empty());
        col = 0;
    }

    int next() {
        int ret = (row == 0 ? v1[col] : v2[col]);
        if (row == 0) {
            if (col < v2.size()) row = 1;
            else col++;
        } else {
            if (col+1 < v1.size()) {
                row = 0;
                col++;
            } else {
                col++;
            }
        }
        return ret;
    }

    bool hasNext() {
        return row == 0 && col < v1.size() ||
            row == 1 && col < v2.size();
    }

private:
    int row, col;
    vector<int>& v1;
    vector<int>& v2;
};

int main() {
    return 0;
}

