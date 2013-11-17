#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

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

    int result = 0;
    while (a > b) {
        int imax = 1;
        for (int i = 0; i < n; i++) {
            if (a - a % xList[i] >= b) {
                imax = max(imax, a % xList[i]);
            }
        }
        a -= imax;
        result++;
        while (n > 1 && a - a % xList[n-1] < b) n--;
    }
    cout << result << endl;
    return 0;
}

