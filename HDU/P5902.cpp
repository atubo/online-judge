// http://acm.hdu.edu.cn/showproblem.php?pid=5902
// GCD is Funny

#include <inttypes.h>
#include <algorithm>
#include <cstdio>
#include <set>
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
        typedef set<int>::const_iterator Iter;
        set<int> gcdSet, oldGcdSet;
        for (int i = 0; i < N-1; i++) {
            for (int j = i+1; j < N; j++) {
                int g = gcd(A[i], A[j]);
                oldGcdSet.insert(g);
                gcdSet.insert(g);
            }
        }
        set<int> newGcdSet;
        for (int i = 3; i <= N-1; i++) {
            for (Iter it = oldGcdSet.begin();
                 it != oldGcdSet.end(); ++it) {
                for (int j = 0; j < N; j++) {
                    int g = gcd(*it, A[j]);
                    if (gcdSet.count(g) == 0) {
                        newGcdSet.insert(g);
                    }
                }
            }
            if (newGcdSet.empty()) break;
            swap(newGcdSet, oldGcdSet);
            newGcdSet.clear();
            gcdSet.insert(oldGcdSet.begin(), oldGcdSet.end());
        }

        vector<int> ans(gcdSet.size());
        copy(gcdSet.begin(), gcdSet.end(), ans.begin());

        for (int i = 0; i < (int)ans.size()-1; i++) {
            printf("%d ", ans[i]);
        }
        printf("%d\n", ans.back());
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
