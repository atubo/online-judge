// https://leetcode.com/problems/encode-and-decode-tinyurl/
// 535. Encode and Decode TinyURL

#include <bits/stdc++.h>
using namespace std;
#include "../utils/BinaryTree.h"
#include "../utils/Graph.h"
#include "../utils/LinkedList.h"
#include "../utils/Util.h"

class Solution {
public:
    string encode(string longUrl) {
        urls.push_back(longUrl);
        return to_string(urls.size()-1);
    }
    string decode(string shortUrl) {
        int idx = stoi(shortUrl);
        return urls[idx];
    }
private:
    vector<string> urls;
};

int main() {
    Solution solution;
    return 0;
}
