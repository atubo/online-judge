// http://acm.hdu.edu.cn/showproblem.php?pid=5902
// GCD is Funny

#include <inttypes.h>
#include <algorithm>
#include <cstdio>
#include <vector>

using namespace std;

int64_t gcd(int64_t a, int64_t b) {
    if (b == 0) return a;
    return gcd(b, a%b);
}

class Solution {
private:
    int N;
    vector<int> A;
public:
    Solution() {
        scanf("%d", &N);
        A.resize(N);
        for (int i = 0; i < N; i++) {
            scanf("%d", &A[i]);
        }
    }

    void solve() {
        vector<int> g(N*(N-1)/2);
        for (int i = 0, idx = 0; i < N-1; i++) {
            for (int j = i+1; j < N; j++) {
                g[idx++] = gcd(A[i], A[j]);
            }
        }
        sort(g.begin(), g.end());
        g.erase(unique(g.begin(), g.end()), g.end());
        for (int i = 0; i < (int)g.size()-1; i++) {
            printf("%d ", g[i]);
        }
        printf("%d\n", g.back());
    }
};

int main() {
    int T;
    scanf("%d", &T);
    for (int i = 0; i < T; i++) {
        Solution solution;
        solution.solve();
    }
    return 0;
}
