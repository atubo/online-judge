// https://leetcode.com/problems/top-k-frequent-words/
// 692. Top K Frequent Words

#include <bits/stdc++.h>
using namespace std;
#include "../utils/BinaryTree.h"
#include "../utils/Graph.h"
#include "../utils/LinkedList.h"
#include "../utils/Util.h"

class Solution {
public:
    struct Data {
        string s;
        int cnt;
        bool operator < (const Data &other) const {
            if (cnt != other.cnt) return cnt > other.cnt;
            return s < other.s;
        }
    };
    vector<string> topKFrequent(vector<string> &words, int k) {
        map<string, int> cnt;
        for (const auto &w: words) {
            cnt[w]++;
        }
        priority_queue<Data> pq;
        for (auto it = cnt.begin(); it != cnt.end(); ++it) {
            pq.push({it->first, it->second});
            if ((int)pq.size() > k) pq.pop();
        }
        vector<string> ret;
        while (!pq.empty()) {
            ret.push_back(pq.top().s);
            pq.pop();
        }
        reverse(ret.begin(), ret.end());
        return ret;
    }
};

int main() {
    Solution solution;
    return 0;
}
