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
    vector<string> findWords(vector<vector<char>>& board, vector<string>& words) {
        vector<string> ret;
        if (board.size() == 0 || board[0].size() == 0) return ret;
        sort(words.begin(), words.end());
        words.erase(unique(words.begin(), words.end()), words.end());

        const int M = board.size();
        const int N = board[0].size();
        vector<vector<bool>> visited(M, vector<bool>(N));
        for (const string& word: words) {
            if (search(board, word, visited)) ret.push_back(word);
        }
        return ret;
    }

    bool search(const vector<vector<char>>& board, const string& word,
                vector<vector<bool>>& visited) {
        const int M = board.size();
        const int N = board[0].size();
        for (int i = 0; i < M; i++) {
            for (int j = 0; j < N; j++) {
                if (dfs(board, i, j, word, 0, visited)) return true;
            }
        }
        return false;
    }

    bool dfs(const vector<vector<char>>& board, int row, int col,
             const string& word, int pos, vector<vector<bool>>& visited) {
        const int M = board.size();
        const int N = board[0].size();
        visited[row][col] = true;
        bool ret = false;
        if (board[row][col] == word[pos]) {
            if (pos == (int)word.size()-1) ret = true;
            else {
                for (int d = 0; d < 4; d++) {
                    int rn = row + DX[d];
                    int cn = col + DY[d];
                    if (inRange(rn, cn, M, N) && !visited[rn][cn]) {
                        if (dfs(board, rn, cn, word, pos+1, visited)) {
                            ret = true;
                            break;
                        }
                    }
                }
            }
        }
        visited[row][col] = false;
        return ret;
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
