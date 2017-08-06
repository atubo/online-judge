// https://leetcode.com/problems/design-hit-counter/description/
// 362. Design Hit Counter

#include <bits/stdc++.h>
using namespace std;

class HitCounter {
public:
    HitCounter() {
        curr = 0;
    }

    void hit(int timestamp) {
        if (!q.empty() && q.back().first == timestamp) {
            q.back().second++;
        } else {
            q.push(make_pair(timestamp, 1));
        }

        curr++;

        expire(timestamp);
    }

    int getHits(int timestamp) {
        expire(timestamp);
        return curr;
    }

    void expire(int timestamp) {
        while (!q.empty() && q.front().first <= timestamp - 300) {
            curr -= q.front().second;
            q.pop();
        }
    }
private:
    int curr;
    queue<pair<int, int>> q;
};

int main() {
    return 0;
}
