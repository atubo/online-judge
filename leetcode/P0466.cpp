// https://leetcode.com/problems/count-the-repetitions/#/description
// 466. Count The Repetitions

#include "BinaryTree.h"
#include "Graph.h"
#include "LinkedList.h"
#include "Util.h"
#include <bits/stdc++.h>
using namespace std;

class Solution {
    typedef vector<vector<int>> NextMap;
    static const int MAXP = 27;
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

        const int L1 = s1.length();
        vector<vector<int>> dist = calcDist(s1, s2, nextMap);

        int pos = 0, ret = 0;
        while (true) {
            int power = 0;
            while (pos + dist[power][pos%L1] < n1 * L1) {
                power++;
            }
            if (power == 0) break;
            pos = pos + dist[power-1][pos%L1] + 1;
            ret += (1 << (power-1));
        }
        return ret/n2;
    }

    int match(const string& s1, const string& s2, int i, int j,
              const NextMap& nextMap) {
        int L1 = s1.length(), L2 = s2.length();
        int p = i % L1, q = j % L2;
        char c = s2[q];
        int p2 = nextMap.at(c-'a')[p];
        return i + (p2 - p);
    }

    vector<vector<int>> calcDist(const string& s1, const string& s2,
                                 const NextMap& nextMap) {
        const int L1 = s1.length(), L2 = s2.length();
        vector<vector<int>> dist(MAXP+1, vector<int>(L1));
        for (int start = 0; start < L1; start++) {
            int i = start-1;
            for (int j = 0; j < L2; j++) {
                i = match(s1, s2, i+1, j, nextMap);
            }
            dist[0][start] = i - start;
        }

        for (int d = 1; d <= MAXP; d++) {
            for (int start = 0; start < L1; start++) {
                int p = (start + dist[d-1][start] + 1) % L1;
                dist[d][start] = dist[d-1][start] + dist[d-1][p] + 1;
            }
        }

        return dist;
    }

    NextMap calcNext(const string& s1) {
        string s = s1 + s1;
        int N = s.length();
        NextMap nextMap(26, vector<int>(N+1, INT_MAX));
        for (int i = N-1; i >= 0; i--) {
            char c = s[i];
            for (int j = 0; j < 26; j++) {
                if (c-'a' == j) nextMap[j][i] = i;
                else nextMap[j][i] = nextMap[j][i+1];
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
