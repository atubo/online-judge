// http://codeforces.com/problemset/problem/501/D

#include <iostream>
#include <vector>

using namespace std;

#define READ_ARRAY(N, A) \
    for (int i = 0; i < N; i++) {\
        cin >> A[i];\
    }

template <typename T>
void printVector(const vector<T>& A) {
    for (const T& x: A) {
        cout << x << " ";
    }
    cout << endl;
}

#include <cinttypes>
#include <cstring>
#include <cstdlib>
using namespace std;

class BIT {
public:
    // Note size needs to be power of 2
    BIT(int size): N(size) {
        tree = (int64_t*)malloc((size+1) * sizeof(int64_t));
        memset(tree, 0, (size+1) * sizeof(int64_t));
    }
    
    ~BIT() {
        free(tree);
        tree = NULL;
    }
    // add v to value at x
    void set(int x, int v) {
        while(x <= N) {
            tree[x] += v;
            x += (x & -x);
        }
    }

    // get cumulative sum up to and including x
    int64_t get(int x) const {
        int64_t res = 0;
        while(x) {
            res += tree[x];
            x -= (x & -x);
        }
        return res;
    }

    // get largest value with cumulative sum less than or equal to x;
    // for smallest, pass x-1 and add 1 to result
    int getind(int x) {
        int idx = 0, mask = N;
        while(mask && idx < N) {
            int t = idx + mask;
            if(x >= tree[t]) {
                idx = t;
                x -= tree[t];
            }
            mask >>= 1;
        }
        return idx;
    }

private:
    int64_t* tree;
    const int N;
};

#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>

class Solution {
private:
    int N;
    vector<int> P;
    vector<int> Q;
public:
    Solution() {
        cin >> N;
        P.resize(N);
        Q.resize(N);
        READ_ARRAY(N, P);
        READ_ARRAY(N, Q);
    }

    void solve() {
        vector<int> sum(N);
        vector<int> repP(N), repQ(N);
        BIT bitP(262144);
        BIT bitQ(262144);
        for (int i = N-1; i >= 0; i--) {
            repP[i] = bitP.get(P[i]+1);
            bitP.set(P[i]+1, 1);

            repQ[i] = bitQ.get(Q[i]+1);
            bitQ.set(Q[i]+1, 1);
        }

        int carry = 0;
        for (int i = N-1; i >= 0; i--) {
            int m = N - i;
            int s = repP[i] + repQ[i] + carry;
            sum[i] = s % m;
            carry = s / m;
            assert(carry <= 1);
        }

        vector<int> result = build(sum);
        printVector(result);
    }

    vector<int> build(const vector<int>& sum) {
        using namespace __gnu_pbds;
        typedef tree<int, null_type, less<int>, rb_tree_tag,
                     tree_order_statistics_node_update> ordered_set;

        vector<int> ret;
        ordered_set s;
        for (int i = 0; i < N; i++) {
            s.insert(i);
        }

        for (int i = 0; i < N; i++) {
            assert(sum[i] < (N-i));
            auto it = s.find_by_order(sum[i]);
            ret.push_back(*it);
            s.erase(it);
        }
        return ret;
    }
};

int main() {
    Solution solution;
    solution.solve();
    return 0;
}
