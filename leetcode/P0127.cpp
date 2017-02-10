#include "BinaryTree.h"
#include "Graph.h"
#include "LinkedList.h"
#include "Util.h"
#include <strings.h>
#include <algorithm>
#include <cassert>
#include <climits>
#include <cstring>
#include <deque>
#include <functional>
#include <iostream>
#include <map>
#include <queue>
#include <set>
#include <stack>
#include <tuple>
#include <unordered_map>
#include <utility>
#include <vector>
using namespace std;

class Solution {
public:
    int ladderLength(string beginWord, string endWord, vector<string>& wordList) {
        int N = wordList.size();
        int b = -1, e = -1;
        for (int i = 0; i < N; i++) {
           if (beginWord == wordList[i]) {
              b = i;
              break;
           }
        }
        for (int i = 0; i < N; i++) {
            if (endWord == wordList[i]) {
                e = i;
                break;
            }
        }
        if (b == -1) {
            b = N++;
            wordList.push_back(beginWord);
        }
        if (e == -1) {
            return 0;
        }

        vector<vector<int> > adj(N);
        for (int i = 0; i < N; i++) {
            for (int j = i+1; j < N; j++) {
                if (dist(wordList[i], wordList[j]) == 1) {
                    adj[i].push_back(j);
                    adj[j].push_back(i);
                }
            }
        }

        vector<bool> visited(N);
        queue<pair<int, int> > q;
        q.push(make_pair(b, 0));
        visited[b] = true;
        while (!q.empty()) {
            int u = q.front().first;
            int d = q.front().second;
            q.pop();
            if (u == e) {
                return d + 1;
            }
            for (int v: adj[u]) {
                if (!visited[v]) {
                    q.push(make_pair(v, d+1));
                    visited[v] = true;
                }
            }
        }
        return 0;
    }

    int dist(const string& s, const string& t) {
        int ans = 0;
        for (int i = 0; i < (int)s.length(); i++) {
            if (s[i] != t[i]) ans++;
        }
        return ans;
    }
};

int main() {
    Solution solution;
    string b, e;
    cin >> b >> e;
    int N;
    cin >> N;
    vector<string> wl;
    for (int i = 0; i < N; i++) {
        string s;
        cin >> s;
        wl.push_back(s);
    }

    cout << solution.ladderLength(b, e, wl) << endl;
    return 0;
}
