// https://leetcode.com/problems/design-snake-game/description/
// 353. Design Snake Game

#include <bits/stdc++.h>
using namespace std;

class SnakeGame {
    using PII = pair<int, int>;
public:
    SnakeGame(int w, int h, vector<PII> f) {
        width = w;
        height = h;
        food = f;
        head = make_pair(0, 0);
        body.push_front(head);
        occupied.insert(head);
        foodIdx = 0;
        score = 0;
    }

    int move(string direction) {
        const int DX[4] = {0, -1, 0, 1};
        const int DY[4] = {1, 0, -1, 0};

        int d = getDir(direction[0]);
        int nx = head.first + DX[d];
        int ny = head.second + DY[d];
        PII next = make_pair(nx, ny);
        if (!inRange(next) ||
            (occupied.count(next) > 0 && next != body.back())) return -1;
        if (foodIdx < (int)food.size() && food[foodIdx] == next) {
            pushFront(next);
            foodIdx++;
            score++;
        } else {
            popBack();
            pushFront(next);
        }
        return score;
    }

    void pushFront(const PII& f) {
        head = f;
        body.push_front(f);
        occupied.insert(f);
    }

    void popBack() {
        PII tail = body.back();
        body.pop_back();
        occupied.erase(tail);
    }

    int getDir(char c) {
        if (c == 'R') return 0;
        else if (c == 'U') return 1;
        else if (c == 'L') return 2;
        else return 3;
    }

    bool inRange(const PII& p) {
        return 0 <= p.first && p.first < height &&
            0 <= p.second && p.second < width;
    }

private:
    int width, height;
    vector<PII> food;
    PII head;
    deque<PII> body;
    set<PII> occupied;
    int foodIdx;
    int score;
};

int main() {
    return 0;
}
