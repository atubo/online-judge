// https://leetcode.com/problems/rearrange-string-k-distance-apart/
// 358. Rearrange String k Distance Apart

#include <bits/stdc++.h>
using namespace std;
#include "../utils/BinaryTree.h"
#include "../utils/Graph.h"
#include "../utils/LinkedList.h"
#include "../utils/Util.h"

class Solution {
    struct Data {
        char c;
        int cnt;
        bool operator < (const Data &other) const {
            if (cnt != other.cnt) return cnt > other.cnt;
            return c < other.c;
        }
    };
public:
    string rearrangeString(string s, int k) {
        if (k == 0) return s;
        const int n = s.length();
        int cnt[26] = {0};
        for (char c: s) cnt[c-'a']++;
        vector<Data> alpha;
        for (int i = 0; i < 26; i++) {
            if (cnt[i] > 0) alpha.push_back({'a'+i, cnt[i]});
        }
        sort(alpha.begin(), alpha.end());
        reverse(alpha.begin(), alpha.end());
        string ret(n, '\0');
        int offset = k-1;
        int p = -1;
        bool ok = true;
        for (const Data &d: alpha) {
            p += k;
            if (p >= n) p = --offset; 
            int first = p;
            ret[p] = d.c;
            for (int i = 1; i < d.cnt; i++) {
                p += k;
                if (p >= n) p = --offset;
                ret[p] = d.c;
                if (abs(p-first) < k) {
                    ok = false;
                    break;
                }
            }
            if (!ok) break;
        }
        if (!ok) return "";
        return ret;
    }
};

int main() {
    Solution solution;
    cout << solution.rearrangeString("abcdabcdabdeac", 4) << endl;
    return 0;
}
