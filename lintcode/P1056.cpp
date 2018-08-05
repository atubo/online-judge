// https://www.lintcode.com/problem/find-smallest-letter-greater-than-target/description
// 1056. Find Smallest Letter Greater Than Target


#include <bits/stdc++.h>
using namespace std;
#include "../utils/BinaryTree.h"
#include "../utils/Graph.h"
#include "../utils/LinkedList.h"
#include "../utils/Util.h"

class Solution {
public:
    char nextGreaterLetter(string &letters, char target) {
        const int n = letters.length();
        if (letters[n-1] <= target) return letters[0];
        int lo = -1, hi = n-1;
        while (lo < hi-1) {
            int mid = (lo + hi) / 2;
            if (letters[mid] <= target) lo = mid;
            else hi = mid;
        }
        return letters[hi];
    }
};

int main() {
    Solution solution;
    string s;
    char c;
    cin >> s >> c;
    cout << solution.nextGreaterLetter(s, c) << endl;
    return 0;
}
