#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

class SegmentTreeMin {
public:
    SegmentTreeMin(int n, int init):data(max(3*n, 30), init), nData(n) {}

    void update(int i, int value) {
        i += nData + 1;
        data[i] = value;
        for (; i > 1; i >>= 1) {
            data[i>>1] = min(data[i], data[i^1]);
        }
    }

    int findMin() const {
        return data[1];
    }
private:
    vector<int> data;
    int nData;
};


#include <unordered_map>
#include <unordered_set>
int main() {
    int n;
    cin >> n;
    vector<int> xList;
    for (int i = 0; i < n; i++) {
        int x;
        cin >> x;
        xList.push_back(x);
    }
    sort(xList.begin(), xList.end());
    xList.erase(unique(xList.begin(), xList.end()), xList.end());
    n = xList.size();

    int a, b;
    cin >> a >> b;

    unordered_map<int, vector<int> > ladder;
    for (int i = 0; i < n; i++) {
        int x = xList[i];
        for (int k = b/x; k < a/x+1; k++) {
            if (ladder.count(x*k) == 0) {
                ladder[x*k] = vector<int>();
            }
            ladder[x*k].push_back(i);
        }
    }

    const int MAXVAL = 10000000;
    SegmentTreeMin tree(n, MAXVAL);

    int dist = 0;
    if (ladder.count(b) != 0) {
        for (int x: ladder[b]) {
            tree.update(x, 0);
        }
    }

    for (int i = b+1; i < a+1; i++) {
        if (ladder.count(i) != 0) {
            for (int x: ladder[i]) {
                tree.update(x, MAXVAL);
            }
        }
        dist = min(dist, tree.findMin()) + 1;
        if (ladder.count(i) != 0) {
            for (int x: ladder[i]) {
                tree.update(x, dist);
            }
        }
    }

    cout << dist << endl;

    return 0;
}

