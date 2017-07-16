// https://leetcode.com/problems/design-search-autocomplete-system/#/description
// 642. Design Search Autocomplete System

#include <bits/stdc++.h>
#include "Util.h"
using namespace std;

class AutocompleteSystem {
    struct Bucket {
        Bucket(int c = 0, int b = -2) : cnt(c), bid(b) {}
        int cnt;
        int bid;
        bool operator < (const Bucket& other) const {
            if (cnt > other.cnt) return true;
            if (cnt < other.cnt) return false;
            return (bid < other.bid);
        }

        bool operator == (const Bucket& other) const {
            return cnt == other.cnt && bid == other.bid;
        }
    };

    struct Node {
        Node(Node* f, int i): father(f), idx(i), children(27), freq(0) {}
        Node* father;
        int idx;
        vector<Node*> children;
        int freq;
        vector<Bucket> buckets;
    };

    int index(char c) {
        if (c == ' ') return 0;
        else return c - 'a' + 1;
    }

    char chr(int idx) {
        if (idx == 0) return ' ';
        else return 'a' + idx - 1;
    }
public:
    AutocompleteSystem(const vector<string>& words, vector<int> times) {
        const int N = words.size();
        root_ = new Node(NULL, -1);
        for (int i = 0; i < N; i++) {
            addWord(words[i], times[i]);
        }

        cursor_ = root_;
    }

    vector<string> input(char c) {
        vector<string> ret;
        if (c == '#') {
            cursor_->freq++;
            bool updated = update(cursor_->buckets, {cursor_->freq}, -1);
            if (updated) propagate(cursor_);
            cursor_ = root_;
            prefix_.clear();
            return ret;
        }

        prefix_.push_back(c);
        int idx = index(c);
        if (!cursor_->children[idx]) {
            cursor_->children[idx] = new Node(cursor_, idx);
        }
        cursor_ = cursor_->children[idx];
        for (int i = 0; i < (int) cursor_->buckets.size(); i++) {
            string prefix = prefix_;
            dfs(cursor_, ret, i, prefix);
        }
        return ret;
    }

    void dfs(Node* node, vector<string>& ret, int rank, string& s) {
        int bid = node->buckets[rank].bid;
        int nextRank = 0;
        for (int i = 0; i <= rank-1; i++) {
            if (node->buckets[i].bid == node->buckets[rank].bid) nextRank++;
        }
        if (bid == -1) {
            ret.push_back(s);
            return;
        }
        s.push_back(chr(bid));
        dfs(node->children[bid], ret, nextRank, s);
    }

    void addWord(const string& word, int freq) {
        Node* curr = root_;
        for (char c: word) {
            int idx = index(c);
            if (!curr->children[idx]) {
                curr->children[idx] = new Node(curr, idx);
            }
            curr = curr->children[idx];
        }
        curr->freq += freq;
        bool updated = update(curr->buckets, {curr->freq}, -1);
        if (updated) propagate(curr);
    }

    bool update(vector<Bucket>& buckets, vector<int> freqs, int bid) {
        vector<Bucket> before = buckets;
        vector<Bucket> after;
        for (const Bucket& b: buckets) {
            if (b.bid != bid) after.push_back(b);
        }
        for (int f: freqs) {
            after.push_back(Bucket(f, bid));
        }
        sort(after.begin(), after.end());
        if (after.size() > 3) after.resize(3);
        assert(after.size() <= 3);
        buckets = after;
        return before != after;
    }

    void propagate(Node* node) {
        while (node->father) {
            vector<int> freqs;
            for (const Bucket& bucket: node->buckets) {
                freqs.push_back(bucket.cnt);
            }
            bool updated = update(node->father->buckets, freqs, node->idx);
            if (!updated) break;
            node = node->father;
        }
    }

private:
    Node* root_;
    Node* cursor_;
    string prefix_;
};

int main() {
    vector<string> words = getStringVector();
    vector<int> freq = getBracketedIntVector();
    AutocompleteSystem as(words, freq);
    string s;
    getline(std::cin, s);
    for (char c: s) {
        auto ret = as.input(c);
        printf("char: %c\n", c);
        for (auto w: ret) {
            cout << w << endl;
        }
    }
    return 0;
}
