// https://leetcode.com/problems/keys-and-rooms/description/
// 841. Keys and Rooms

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    bool canVisitAllRooms(vector<vector<int>> & rooms) {
        const int N = rooms.size();
        vector<bool> vis(N);
        queue<int> q;
        q.push(0);
        vis[0] = true;
        while (!q.empty()) {
            int u = q.front();
            q.pop();
            for (int v: rooms[u]) {
                if (!vis[v]) {
                    q.push(v);
                    vis[v] = true;
                }
            }
        }
        int cnt = 0;
        for (int i = 0; i < N; i++) cnt += vis[i];
        return cnt == N;
    }
};

int main() {
    return 0;
}
