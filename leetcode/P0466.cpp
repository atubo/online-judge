// https://leetcode.com/problems/count-the-repetitions/#/description
// 466. Count The Repetitions

#include "BinaryTree.h"
#include "Graph.h"
#include "LinkedList.h"
#include "Util.h"
#include <bits/stdc++.h>
using namespace std;

class Solution {
    typedef map<char, vector<int>> NextMap;
public:
    int getMaxRepetitions(string s1, int n1, string s2, int n2) {
        for (char c2: s2) {
            bool found = false;
            for (char c1: s1) {
                if (c1 == c2) {
                    found = true;
                    break;
                }
            }
            if (!found) return 0;
        }

        NextMap nextMap = calcNext(s1);

        const int L1 = s1.length(), L2 = s2.length();
        vector<int> last(L2, -1);
        int i = -1, j = 0;
        while (true) {
            i = match(s1, s2, i+1, j, nextMap);
            if (i >= L1 * n1 ||
                ((last[j%L2] >= 0) && last[j%L2]%L1 == (i % L1))) break;
            last[j%L2] = i;
            j++;
        }

        //printf("i=%d j=%d\n", i, j);
        if (i < L1 * n1) {
            int L = i - last[j%L2];
            int m = (L1*n1 - 1 - last[j%L2]) / L;
            i = last[j%L2] + L * m;
            j = j + L2 * (m-1);

            j++;
            while (i < L1 * n1) {
                i = match(s1, s2, i+1, j, nextMap);
                //printf("%d %d\n", i, j);
                if (i >= L1 * n1) break;
                j++;
            }
        }
        return (j/L2) / n2;
    }

    int match(const string& s1, const string& s2, int i, int j,
              const NextMap& nextMap) {
        int L1 = s1.length(), L2 = s2.length();
        int p = i % L1, q = j % L2;
        char c = s2[q];
        int p2 = nextMap.at(c)[p];
        return i + (p2 - p);
    }

    NextMap calcNext(const string& s1) {
        string s = s1 + s1;
        int N = s.length();
        NextMap nextMap;
        for (char c: s) {
            if (nextMap.count(c) == 0) {
                nextMap[c] = vector<int>(N+1, INT_MAX);
            }
        }
        for (int i = N-1; i >= 0; i--) {
            char c = s[i];
            for (auto& p: nextMap) {
                if (p.first == c) {
                    p.second[i] = i;
                } else {
                    p.second[i] = p.second[i+1];
                }
            }
        }
        return nextMap;
    }
};

int main() {
    string s1, s2;
    int n1, n2;
    cin >> s1 >> n1 >> s2 >> n2;
    Solution solution;
    cout << solution.getMaxRepetitions(s1, n1, s2, n2) << endl;
    return 0;
}
