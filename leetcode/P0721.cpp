// https://leetcode.com/problems/accounts-merge/
// 721. Accounts Merge

#include <bits/stdc++.h>
using namespace std;
#include "../utils/BinaryTree.h"
#include "../utils/Graph.h"
#include "../utils/LinkedList.h"
#include "../utils/Util.h"

class Solution {
public:
    vector<vector<string>> accountsMerge(vector<vector<string>>& accounts) {
        map<string, vector<int>> emailToAcct;
        for (int i = 0; i < (int)accounts.size(); i++) {
            for (int j = 1; j < (int)accounts[i].size(); j++) {
                string email = accounts[i][j];
                emailToAcct[email].push_back(i);
            }
        }

        vector<vector<string>> ret;
        set<string> vis;
        for (auto it = emailToAcct.begin(); it != emailToAcct.end(); ++it) {
            string email = it->first;
            if (vis.find(email) != vis.end()) continue;
            string user = accounts[it->second[0]][0];
            vector<string> list;
            list.push_back(user);
            dfs(email, emailToAcct, accounts, vis, list);
            sort(list.begin()+1, list.end());
            ret.push_back(list);
        }
        return ret;
    }

    void dfs(const string &email, const map<string, vector<int>> &emailToAcct,
             vector<vector<string>> &accounts, set<string> &vis,
             vector<string> &list) {
        list.push_back(email);
        vis.insert(email);
        for (int acct: emailToAcct.at(email)) {
            for (int i = 1; i < (int)accounts[acct].size(); i++) {
                string alias = accounts[acct][i];
                if (vis.find(alias) == vis.end()) {
                    dfs(alias, emailToAcct, accounts, vis, list);
                }
            }
        }
    }
};

int main() {
    Solution solution;
    return 0;
}
