// https://leetcode.com/problems/time-based-key-value-store/
// 981. Time Based Key-Value Store

#include <bits/stdc++.h>
using namespace std;
#include "../utils/BinaryTree.h"
#include "../utils/Graph.h"
#include "../utils/LinkedList.h"
#include "../utils/Util.h"

class TimeMap {
    struct Data {
        int t;
        string value;
        bool operator < (const Data &other) const {
            if (t != other.t) return t < other.t;
            return value < other.value;
        }
    };
public:
    TimeMap() {}

    void set(string key, string value, int timestamp) {
        ds_[key].push_back({timestamp, value});
    }

    string get(string key, int timestamp) {
        if (ds_.find(key) == ds_.end()) return "";
        const auto &v = ds_[key];
        auto it = upper_bound(v.begin(), v.end(), Data{timestamp+1, ""});
        if (it == v.begin()) return "";
        --it;
        return it->value;
    }
private:
    map<string, vector<Data>> ds_;
};

int main() {
    return 0;
}
