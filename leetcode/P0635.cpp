// https://leetcode.com/problems/design-log-storage-system/#/description
// 635. Design Log Storage System

#include "BinaryTree.h"
#include "Graph.h"
#include "LinkedList.h"
#include "Util.h"
#include <bits/stdc++.h>
using namespace std;

class LogSystem {
public:
    LogSystem() {
        logs.resize(7);
    }

    vector<int> parse(const string& s) {
        vector<int> ret(6);
        ret[0] = stoi(s.substr(0, 4));
        for (int i = 1; i < 6; i++) {
            ret[i] = stoi(s.substr(2+3*i, 2));
        }
        return ret;
    }

    vector<int> slice(const vector<int>& v, int level) {
        vector<int> ret;
        for (int i = 0; i < level; i++) {
            ret.push_back(v[i]);
        }
        return ret;
    }

    int getGraLevel(const string& s) {
        if (s == "Year") return 1;
        else if (s == "Month") return 2;
        else if (s == "Day") return 3;
        else if (s == "Hour") return 4;
        else if (s == "Minute") return 5;
        else {
            assert(s == "Second");
            return 6;
        }
    }

    void put(int id, string timestamp) {
        vector<int> tm = parse(timestamp);
        for (int level = 1; level <= 6; level++) {
            logs[level][slice(tm, level)].insert(id);
        }
    }

    vector<int> retrieve(string s, string e, string gra) {
        vector<int> ts = parse(s);
        vector<int> te = parse(e);
        int level = getGraLevel(gra);
        vector<int> start = slice(ts, level);
        vector<int> end = slice(te, level);

        vector<int> ret;
        auto it1 = logs[level].lower_bound(start);
        auto it2 = logs[level].upper_bound(end);
        for (auto it = it1; it != it2; it++) {
            for (int id: it->second) {
                ret.push_back(id);
            }
        }

        return ret;
    }

private:
    vector<map<vector<int>, set<int>>> logs;
};

int main() {
    LogSystem log;
    log.put(1, "2017:01:01:23:59:59");
    log.put(2, "2017:01:01:22:59:59");
    log.put(3, "2016:01:01:00:00:00");

    printVector(log.retrieve("2016:01:01:01:01:01","2017:01:01:23:00:00","Year"));
    printVector(log.retrieve("2016:01:01:01:01:01","2017:01:01:23:00:00","Hour"));
    return 0;
}
