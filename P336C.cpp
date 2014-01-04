#include <iostream>
#include <vector>
using namespace std;

int main() {
    vector<vector<int> > numByDigit;
    for (int i = 0; i < 32; i++) {
        numByDigit.push_back(vector<int>());
    }

    int n;
    cin >> n;
    for (int i = 0; i < n; i++) {
        int x;
        cin >> x;
        for (int d = 0; d < 32; d++) {
            if ((x & 1 << d) != 0) {
                numByDigit[d].push_back(x);
            }
        }
    }

    for (int d = 31; d >= 0; d--) {
        vector<int>& nums = numByDigit[d];
        int andResult = 0xFFFFFFFF;
        for (int x: nums) {
            andResult &= x;
        }
        if ((andResult & ((1 << d) - 1)) == 0) {
            cout << nums.size() << endl;
            for (int x: nums) {
                cout << x << " ";
            }
            cout << endl;
            break;
        }
    }

    return 0;
}
