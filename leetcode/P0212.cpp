// https://leetcode.com/problems/word-search-ii/#/description
// 212. Word Search II

#include "BinaryTree.h"
#include "Graph.h"
#include "LinkedList.h"
#include "Util.h"
#include <bits/stdc++.h>
using namespace std;

const static int DX[4] = {1, 0, -1, 0};
const static int DY[4] = {0, 1, 0, -1};
class Solution {
public:
    struct Node {
        Node() : children(26) {}
        vector<Node*> children;
        string word;
    };

    Node* buildTrie(const vector<string>& words) {
        Node* root = new Node;
        for (const string& word: words) {
            Node* curr = root;
            for (char c: word) {
                if (!curr->children[c-'a']) curr->children[c-'a'] = new Node;
                curr = curr->children[c-'a'];
            }
            curr->word = word;
        }
        return root;
    }

    vector<string> findWords(vector<vector<char>>& board, vector<string>& words) {
        vector<string> ret;
        if (board.size() == 0 || board[0].size() == 0) return ret;
        sort(words.begin(), words.end());
        words.erase(unique(words.begin(), words.end()), words.end());

        Node* root = buildTrie(words);

        const int M = board.size();
        const int N = board[0].size();
        for (int i = 0; i < M; i++) {
            for (int j = 0; j < N; j++) {
                dfs(board, i, j, root, ret);
            }
        }
        return ret;
    }

    void dfs(vector<vector<char>>& board, int row, int col,
             Node* node, vector<string>& ret) {
        const int M = board.size();
        const int N = board[0].size();
        char c = board[row][col];
        if (c == '#' || !node->children[c-'a']) return;

        node = node->children[c-'a'];
        if (!node->word.empty()) {
            ret.push_back(node->word);
            node->word = "";
        }
        board[row][col] = '#';
        for (int d = 0; d < 4; d++) {
            int rn = row + DX[d];
            int cn = col + DY[d];
            if (inRange(rn, cn, M, N)) {
                dfs(board, rn, cn, node, ret);
            }
        }
        board[row][col] = c;
    }

    bool inRange(int r, int c, int M, int N) {
        return 0 <= r && r < M && 0 <= c && c < N;
    }
};

int main() {
    vector<vector<char>> board = { {'b'}, {'a'}, {'b'}, {'b'}, {'a'} };
    vector<string> words = {"baa", "abba", "baab", "aba"};
    Solution solution;
    auto ret = solution.findWords(board, words);
    for (auto w: ret) {
        cout << w << endl;
    }
    return 0;
}
