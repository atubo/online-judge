#include <cinttypes>
#include <cstring>
#include <cstdlib>
using namespace std;

class BIT {
public:
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
    int64_t get(int x) {
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

#include <iostream>
#include <algorithm>
#include <map>

int main()
{
    int n;
    cin >> n;
    int a[n], b[n];
    for (int i = 0; i < n; i++) {
        int x;
        cin >> x;
        a[i] = b[i] = x;
    }
    map<int, int> order;
    sort(b, b+n, greater<int>());
    for (int i = 0; i < n; i++) {
        order[b[i]] = i+1;
    }
    for (int i = 0; i < n; i++) {
        a[i] = order[a[i]];
    }

    BIT bit1(n), bit2(n);
    int64_t result = 0;
    for (int i = 0; i < n; i++) {
        int x = a[i];
        if (x == 1) {
            bit1.set(1, 1);
            continue;
        }
        result += bit2.get(x-1);
        int64_t sum = bit1.get(x-1);
        bit2.set(x, sum);
        bit1.set(x, 1);
    }

    cout << result << endl;

    return 0;
}
