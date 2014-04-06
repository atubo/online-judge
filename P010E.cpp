// Reference: http://graal.ens-lyon.fr/~abenoit/algo09/coins2.pdf
#include <iostream>
#include <vector>
#include <utility>
using namespace std;

class Solution {
public:
    Solution() {
        cin >> n;
        for (int i = 0; i < n; i++) {
            int x;
            cin >> x;
            denom.push_back(x);
        }
    }

    vector<int> greedy(int64_t w) {
        vector<int> v(n, 0);
        for (int i = 0; i < n; i++) {
            v[i] = w / denom[i];
            w -= v[i] * denom[i];
        }
        return v;
    }

    int64_t value(const vector<int>& v) {
        int64_t result = 0;
        for (int i = 0; i < n; i++) {
            result += v[i] * denom[i];
        }
        return result;
    }

    int size(const vector<int>& v) {
        int result = 0;
        for (int i = 0; i < n; i++) {
            result += v[i];
        }
        return result;
    }

    pair<int64_t, bool> isGreedyOK(int i, int j) {
        vector<int> v = greedy(denom[i-1]-1);
        v[j]++;
        for (int k = j+1; k < n; k++) {
            v[k] = 0;
        }
        int64_t w = value(v);
        return make_pair(w, size(greedy(w)) <= size(v));
    }

    void solve() {
        for (int i = n-1; i >= 1; i--) {
            for (int j = n-1; j >= 0; j--) {
                pair<int64_t, bool> p = isGreedyOK(i, j);
                if (!p.second) {
                    cout << p.first << endl;
                    return;
                }
            }
        }
        cout << -1 << endl;
    }

private:
    int n;
    vector<int> denom;
};

int main()
{
    Solution solution;
    solution.solve();
    return 0;
}

