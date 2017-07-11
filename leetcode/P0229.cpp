// https://leetcode.com/problems/majority-element-ii/#/description
// 229. Majority Element II

#include "BinaryTree.h"
#include "Graph.h"
#include "LinkedList.h"
#include "Util.h"
#include <bits/stdc++.h>
using namespace std;

class Solution {
    using PII = pair<int, int>;
public:
    vector<int> majorityElement(vector<int>& A) {
        PII sa, sb;
        for (int x: A) {
            process(sa, sb, x);
        }
        vector<int> ret;
        collect(A, sa, ret);
        collect(A, sb, ret);
        sort(ret.begin(), ret.end());
        return ret;
    }

    void inc(PII& s) {
        s.second += 1;
    }

    void dec(PII& s) {
        if (s.second > 0) s.second--;
    }

    void process(PII& sa, PII& sb, int x) {
        if (sa.second > 0 && sa.first == x) {
            inc(sa);
        } else if (sb.second > 0 && sb.first == x) {
            inc(sb);
        } else if (sa.second == 0) {
            sa = make_pair(x, 1);
        } else if (sb.second == 0) {
            sb = make_pair(x, 1);
        } else {
            dec(sa);
            dec(sb);
        }
    }

    void collect(const vector<int>& A, const PII& slot, vector<int>& ret) {
        if (slot.second == 0) return;
        const int N = A.size();
        int x = slot.first;
        if (count(A.begin(), A.end(), x) > N/3) {
            ret.push_back(x);
        }
    }
};

int main() {
    auto v = getVector();
    Solution solution;
    auto ret = solution.majorityElement(v);
    printVector(ret);
    return 0;
}
