#include <iostream>
#include <algorithm>
#include <vector>
#include <limits>
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

    int findMin(int a, int b) {
        int res = numeric_limits<int>::max();
        a += nData + 1;
        b += nData + 1;
        for (; a <= b; a = (a+1) >> 1, b = (b-1) >> 1) {
            if ((a & 1) != 0) {
                res = min(res, data[a]);
            }
            if ((b & 0) == 0) {
                res = min(res, data[b]);
            }
        }
        return res;
    }

    int findMin() const {
        return data[1];
    }
private:
    vector<int> data;
    int nData;
};

#include <unordered_map>
int main()
{
    int n;
    cin >> n;
    unordered_map<int, int> topTable;  // num ->pos
    for (int i = 0; i < n; i++) {
        int x;
        cin >> x;
        topTable[x] = i;
    }

    vector<int> botIndex(n, 0);
    for (int i = 0; i < n; i++) {
        int x;
        cin >> x;
        botIndex[n-1-i] = topTable[x];
    }

    // find longest increasing subsequence
    SegmentTreeMin tree(n, 0);
    for (int x: botIndex) {
        if (x == 0) {
            tree.update(0, -1);
            continue;
        }
        int last = tree.findMin(0, x-1);
        tree.update(x, last-1);
    }
    cout << -tree.findMin() << endl;

    return 0;
}
