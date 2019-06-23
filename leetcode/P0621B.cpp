// https://leetcode.com/problems/task-scheduler/
// 621. Task Scheduler

#include <bits/stdc++.h>
using namespace std;
#include "../utils/BinaryTree.h"
#include "../utils/Graph.h"
#include "../utils/LinkedList.h"
#include "../utils/Util.h"

class Solution {
public:
    int leastInterval(vector<char>& tasks, int n) {
        vector<int> cnt(26);
        vector<int> last(26, -1);
        for (char c: tasks) {
            cnt[c-'A']++;
        }
        int m = tasks.size();
        int p = 1;
        while (m > 0) {
            int cmax = -1, cntmax = 0, lastmax = INT_MAX;
            for (int i = 0; i < 26; i++) {
                if (cnt[i] == 0 || (last[i] != -1 && p - last[i] <= n)) {
                    continue;
                }
                if ((cnt[i] > cntmax) ||
                    (cnt[i] == cntmax && last[i] < lastmax)) {
                    cntmax = cnt[i];
                    lastmax = last[i];
                    cmax = i;
                }
            }
            if (cmax != -1) {
                cnt[cmax]--;
                m--;
                last[cmax] = p;
            }
            p++;
        }
        return p-1;
    }
};

int main() {
    string s;
    int n;
    cin >> s >> n;
    Solution solution;
    vector<char> tasks;
    for (char c: s) tasks.push_back(c);
    cout << solution.leastInterval(tasks, n) << endl;
    return 0;
}
