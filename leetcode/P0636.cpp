// https://leetcode.com/problems/exclusive-time-of-functions/#/description
// 636. Exclusive Time of Functions

#include "BinaryTree.h"
#include "Graph.h"
#include "LinkedList.h"
#include "Util.h"
#include <bits/stdc++.h>
using namespace std;

class Solution {
    struct Frame {
        Frame(int id_, int start_): id(id_), start(start_), foreign(0) {}
        int id;
        int start;
        int foreign;
    };
public:
    vector<int> exclusiveTime(int n, vector<string>& logs) {
        vector<int> consume(n);
        stack<Frame> frames;
        for (const string& log: logs) {
            int id, type, ts;
            tie(id, type, ts) = parse(log);
            if (type == 0) {
                frames.push(Frame(id, ts));
            } else {
                Frame f = frames.top();
                frames.pop();
                assert(id == f.id);
                int duration = ts - f.start + 1;
                consume[id] += duration - f.foreign;
                if (!frames.empty()) {
                    frames.top().foreign += duration;
                }
            }
        }
        return consume;
    }

    tuple<int, int, int> parse(const string& log) {
        int p = log.find(':');
        int id = stoi(log.substr(0, p));
        int q = log.find(':', p+1);
        string t = log.substr(p+1, q-p-1);
        int type = (t == "end");
        int ts = stoi(log.substr(q+1));
        return make_tuple(id, type, ts);
    }
};

int main() {
    int n, m;
    cin >> n >> m;
    vector<string> logs(m);
    for (int i = 0; i < m; i++) {
        cin >> logs[i];
    }

    Solution solution;
    auto ret = solution.exclusiveTime(n, logs);
    printVector(ret);
    return 0;
}
