#include "BinaryTree.h"
#include "Graph.h"
#include "LinkedList.h"
#include "Util.h"
#include <strings.h>
#include <algorithm>
#include <cassert>
#include <climits>
#include <cstring>
#include <deque>
#include <functional>
#include <iostream>
#include <map>
#include <queue>
#include <set>
#include <stack>
#include <tuple>
#include <unordered_map>
#include <utility>
#include <vector>
using namespace std;

class MedianFinder {
public:
    MedianFinder() {}

    void addNum(int num) {
        if (top.size() == bottom.size()) {
            bottom.push(num);
        } else {
            top.push(num);
        }
        if (!top.empty() && !bottom.empty() && top.top() < bottom.top()) {
            swapTopBottom();
        }
    }

    double findMedian() {
        if (top.size() < bottom.size()) return bottom.top();
        else return ((double)top.top() + bottom.top()) / 2;
    }

private:
    priority_queue<int> bottom;
    priority_queue<int, vector<int>, greater<int> > top;

    void swapTopBottom() {
        int x = top.top();
        int y = bottom.top();
        top.pop();
        bottom.pop();
        bottom.push(x);
        top.push(y);
    }
};

int main() {
    int N;
    cin >> N;
    MedianFinder mf;
    for (int i = 0; i < N; i++) {
        int t;
        cin >> t;
        if (t == 0) {
            int x;
            cin >> x;
            mf.addNum(x);
        } else {
            cout << mf.findMedian() << endl;
        }
    }
    return 0;
}
