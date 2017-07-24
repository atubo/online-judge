// https://leetcode.com/problems/unique-word-abbreviation/#/description
// 288. Unique Word Abbreviation

#include "BinaryTree.h"
#include "Graph.h"
#include "LinkedList.h"
#include "Util.h"
#include <bits/stdc++.h>
using namespace std;

class ValidWordAbbr {
public:
    ValidWordAbbr(vector<string> dict) {
        for (const string& word: dict) {
            if (words.count(word) == 0) abbrs[calcAbbr(word)]++;
            words.insert(word);
        }
    }

    bool isUnique(string word) {
        string abbr = calcAbbr(word);
        return words.count(word) == 0 && abbrs.count(abbr) == 0 ||
            words.count(word) == 1 && abbrs.at(abbr) == 1;
    }

    string calcAbbr(const string& word) {
        int len = word.length();
        if (len <= 2) return word;
        string ret(1, word[0]);
        ret += to_string(len-2);
        ret += word.back();
        return ret;
    }
private:
    set<string> words;
    map<string, int> abbrs;
};


int main() {
    return 0;
}
