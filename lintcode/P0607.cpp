// https://www.lintcode.com/problem/two-sum-iii-data-structure-design/description
// 607. Two Sum III - Data structure design

#include <bits/stdc++.h>
using namespace std;

class TwoSum {
private:
    int curr_ = 0;
    vector<int> a;
public:
    void add(int number) {
        a.push_back(number);
    }

    bool find(int value) {
        const int n = a.size();
        sort(a.begin() + curr_, a.end());
        vector<int> tmp(n);
        int p = 0, q = curr_, r = 0;
        while (p < curr_ && q < n) {
            if (a[p] < a[q]) {
                tmp[r++] = a[p++];
            } else {
                tmp[r++] = a[q++];
            }
        }
        if (p < curr_) {
            copy(a.begin() + p, a.begin() + curr_, tmp.begin() + r);
        } else {
            copy(a.begin() + q, a.end(), tmp.begin() + r);
        }
        a.swap(tmp);
        curr_ = n;

        p = 0, q = n-1;
        while (p < q) {
            int x = a[p] + a[q];
            if (x == value) return true;
            else if (x < value) p++;
            else q--;
        }
        return false;
    }
};

int main() {
    TwoSum ts;
    ts.add(1);
    ts.add(3);
    ts.add(5);
    cout << ts.find(4) << endl;
    cout << ts.find(7) << endl;
    return 0;
}
