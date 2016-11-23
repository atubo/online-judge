// 栈的压入、弹出序列
#include <bits/stdc++.h>
#include "Util.h"
using namespace std;

class Solution {
public:
    bool IsPopOrder(vector<int> A, vector<int> B) {
        const int N = A.size();
        stack<int> s;
        int p = 0, q = 0;
        while (true) {
            while (p < N && A[p] != B[q]) s.push(A[p++]);
            if (p == N) break;
            p++;
            q++;
            while (q < N && !s.empty() && B[q] == s.top()) {
                s.pop();
                q++;
            }
            if (q == N) break;
        }
        return (p == N && q == N && s.empty());
    }
};

int main() {
    auto A = getVector();
    auto B = getVector();
    Solution solution;
    cout << solution.IsPopOrder(A, B) << endl;
    return 0;
}
