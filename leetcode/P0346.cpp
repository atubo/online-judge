// https://leetcode.com/problems/moving-average-from-data-stream/
// 346. Moving Average from Data Stream

#include <bits/stdc++.h>
using namespace std;

class MovingAverage {
public:
    MovingAverage(int size): cap_(size) {}

    double next(int val) {
        if ((int)q_.size() < cap_) {
            q_.push_back(val);
            tot_ += val;
            return 1.0 * tot_ / q_.size();
        }

        tot_ -= q_.front();
        q_.pop_front();
        tot_ += val;
        q_.push_back(val);
        return 1.0 * tot_ / q_.size();
    }

private:
    int cap_;
    int tot_ = 0;
    deque<int> q_;
};

int main() {
    MovingAverage ma(3);
    vector<int> a = {1, 10, 3, 5};
    for (int x: a) {
        cout << ma.next(x) << endl;
    }
    return 0;
}
