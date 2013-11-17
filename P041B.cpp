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

int main()
{
    int n, b;
    cin >> n >> b;
    int a[n];
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }

    SegmentTreeMin tree(n, 0);
    for (int i = 0; i < n; i++) {
        tree.update(i, -a[i]);
    }

    int ans = b;
    for (int i = 0; i < n-1; i++) {
        int curr = a[i];
        int maxPrice = -tree.findMin(i+1, n-1);
        if (maxPrice <= curr) continue;
        ans = max(b/curr * maxPrice + b%curr, ans);
    }

    cout << ans << endl;

    return 0;
}
