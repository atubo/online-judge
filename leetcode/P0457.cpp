// https://leetcode.com/problems/circular-array-loop/#/description
// 457. Circular Array Loop

#include "BinaryTree.h"
#include "Graph.h"
#include "LinkedList.h"
#include "Util.h"
#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int next(int x, int step, int N) {
        return (x + step % N + N) % N;
    }

    bool circularArrayLoop(vector<int>& A) {
        const int N = A.size();
        for (int i = 0; i < N; i++) {
            int nxt = next(i, A[i], N);
            A[i] = (nxt == i ? 0 : A[i]);
        }

        for (int i = 0; i < N; i++) {
            if (A[i] != 0) {
                if (search(i, A)) return true;
            }
        }

        return false;
    }

    bool search(int p, vector<int>& A) {
        const int N = A.size();
        int fast = p, slow = p;
        bool init = true;
        int s = sgn(A[p]);
        while (init || fast != slow) {
            init = false;
            if (A[fast] == 0 || sgn(A[fast]) != s) {
                mark(p, A);
                return false;
            }
            fast = next(fast, A[fast], N);
            if (A[fast] == 0 || sgn(A[fast]) != s) {
                mark(p, A);
                return false;
            }
            fast = next(fast, A[fast], N);

            slow = next(slow, A[slow], N);
        }
        return true;
    }

    void mark(int p, vector<int>& A) {
        const int N = A.size();
        int s = sgn(A[p]);
        while (A[p] != 0 && sgn(A[p]) == s) {
            int q = next(p, A[p], N);
            A[p] = 0;
            p = q;
        }
    }

    int sgn(int x) {
        return x > 0 ? 1 : (x < 0 ? -1 : 0);
    }
};

int main() {
    Solution solution;
    auto v = getBracketedIntVector();
    cout << solution.circularArrayLoop(v) << endl;
    return 0;
}
