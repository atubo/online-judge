// https://leetcode.com/problems/robot-room-cleaner/
// 489. Robot Room Cleaner

#include <bits/stdc++.h>
using namespace std;
#include "../utils/BinaryTree.h"
#include "../utils/Graph.h"
#include "../utils/LinkedList.h"
#include "../utils/Util.h"

class Robot {
public:
    bool move() {return true;};
    void turnLeft() {};
    void turnRight() {}
    void clean() {};
};

class Solution {
    using PII = pair<int, int>;
    const vector<int> DX{-1, 0, 1, 0};
    const vector<int> DY{0, 1, 0, -1};
public:
    void cleanRoom(Robot& robot) {
        set<PII> vis;
        vis.insert({0, 0});
        robot.clean();
        for (int d = 0; d < 4; d++) {
            if (check(robot, 0, 0, d, vis)) {
                robot.move();
                dfs(robot, DX[d], DY[d], d, vis);
            }
            robot.turnRight();
        }
    }

    bool check(Robot &robot, int x, int y, int d, set<PII> &vis) {
        bool ok = robot.move();
        if (!ok) {
            return false;
        }
        int x2 = x + DX[d];
        int y2 = y + DY[d];
        bool ret = (vis.find({x2, y2}) == vis.end() ? true : false);
        backtrack(robot);
        return ret;
    }

    void backtrack(Robot &robot) {
        robot.turnRight(); robot.turnRight();
        robot.move();
        robot.turnRight(); robot.turnRight();
    }

    void dfs(Robot &robot, int x, int y, int d, set<PII> &vis) {
        vis.insert({x, y});
        robot.clean();
        for (int k = 0; k < 4; k++) {
            int d2 = (d + k) % 4;
            if (check(robot, x, y, d2, vis)) {
                robot.move();
                dfs(robot, x+DX[d2], y+DY[d2], d2, vis);
            }
            robot.turnRight();
        }
        backtrack(robot);
    }
};

int main() {
    Solution solution;
    return 0;
}
