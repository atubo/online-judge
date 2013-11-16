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
            int newVal = min(data[i], data[i^1]);
            if (data[i>>1] == newVal) break;
            data[i>>1] = newVal;
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
int round_up(int x, int y) {
    return (x + y - 1) / y;
}

void updateLadder(vector<vector<int> >& ladder,
                  const vector<int> xList, int i) {
    int n = ladder.size();
    for (int j: ladder[i]) {
        if (i + xList[j] < n) {
            ladder[i+xList[j]].push_back(j);
        }
    }
    ladder[i].clear();
}

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

    const int MAXVAL = 10000000;
    SegmentTreeMin tree(n, MAXVAL);

    vector<vector<int> > ladder(a-b+1, vector<int>());
    for (int i = 0; i < n; i++) {
        int x = xList[i];
        int r = round_up(b, x) * x;
        if (r > a) continue;
        ladder[r-b].push_back(i);
    }

    int dist = 0;
    for (int x: ladder[0]) {
        tree.update(x, 0);
    }
    updateLadder(ladder, xList, 0);

    for (int i = 1; i < a-b+1; i++) {
        for (int x: ladder[i]) {
            tree.update(x, MAXVAL);
        }
        dist = min(dist, tree.findMin()) + 1;
        for (int x: ladder[i]) {
            tree.update(x, dist);
        }
        updateLadder(ladder, xList, i);
    }

    cout << dist << endl;

    return 0;
}

