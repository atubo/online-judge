// https://leetcode.com/problems/task-scheduler/#/description
// 621. Task Scheduler

#include "BinaryTree.h"
#include "Graph.h"
#include "LinkedList.h"
#include "Util.h"
#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int leastInterval(vector<char>& tasks, int n) {
        deque<char> dq;
        vector<int> freq(26), zero(26);
        for (char c: tasks) {
            freq[c-'A']++;
        }
        auto cmp = [&freq](char a, char b) {return freq[a-'A'] < freq[b-'A'];};
        priority_queue<char, vector<char>, decltype(cmp)> pq(cmp);
        for (char c = 'A'; c <= 'Z'; c++) {
            if (freq[c-'A'] != 0) pq.push(c);
        }
        int ret = 0;
        while (freq != zero) {
            char c = '0';
            if (!pq.empty()) {
                c = pq.top();
                pq.pop();
                freq[c-'A']--;
            }
            dq.push_back(c);
            ret++;
            if ((int)dq.size() > n) {
                c = dq.front();
                dq.pop_front();
                if (c != '0' && freq[c-'A'] > 0) {
                    pq.push(c);
                }
            }
        }
        return ret;
    }
};

int main() {
    int n;
    string s;
    cin >> s >> n;
    vector<char> tasks;
    for (char c : s) tasks.push_back(c);
    Solution solution;
    cout << solution.leastInterval(tasks, n) << endl;
    return 0;
}
