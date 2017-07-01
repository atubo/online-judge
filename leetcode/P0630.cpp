// https://leetcode.com/problems/course-schedule-iii/#/description
// 630. Course Schedule III

#include "BinaryTree.h"
#include "Graph.h"
#include "LinkedList.h"
#include "Util.h"
#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int scheduleCourse(vector<vector<int>>& courses) {
        sort(courses.begin(), courses.end(),
             [](const vector<int>& a, const vector<int>& b) {
             return make_pair(a[1], a[0]) < make_pair(b[1], b[0]);
             });
        priority_queue<int> pq;
        int curr = 0;
        for (const auto& c: courses) {
            if (c[0] + curr <= c[1]) {
                curr += c[0];
                pq.push(c[0]);
            } else if (!pq.empty() && pq.top() > c[0] &&
                       curr - pq.top() + c[0] <= c[1]) {
                curr = curr - pq.top() + c[0];
                pq.pop();
                pq.push(c[0]);
            }
        }
        return pq.size();
    }
};

int main() {
    vector<vector<int>> c = {{7,17},{3,12},{10,20},{9,10},{5,20},{10,19},{4,18}};
    Solution solution;
    cout << solution.scheduleCourse(c) << endl;
    return 0;
}
