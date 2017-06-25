// 432. All O`one Data Structure
#include "BinaryTree.h"
#include "Graph.h"
#include "LinkedList.h"
#include "Util.h"
#include <bits/stdc++.h>
using namespace std;

class AllOne {
public:
    AllOne() {
    }

    void inc(string key) {
        if (iterMap.count(key) > 0) {
            RowIter rowIt;
            KeyIter keyIt;
            tie(rowIt, keyIt) = iterMap[key];
            moveUp(rowIt, keyIt, key);
        } else {
            if (rows.empty() || rows.front().val > 1) {
                insertRow(rows.begin(), key, 1);
            } else {
                assert(rows.front().val == 1);
                rows.front().strs.push_front(key);
                iterMap[key] = make_pair(rows.begin(), rows.front().strs.begin());
            }
        }
    }

    void dec(string key) {
        if (iterMap.count(key) == 0) return;

        RowIter rowIt;
        KeyIter keyIt;
        tie(rowIt, keyIt) = iterMap[key];
        moveDown(rowIt, keyIt, key);
    }

    string getMaxKey() {
        if (rows.empty()) return "";
        return rows.back().strs.front();
    }

    string getMinKey() {
        if (rows.empty()) return "";
        return rows.front().strs.front();
    }

private:
    struct Row {
        int val;
        list<string> strs;
        Row(int v, const string& s): val(v), strs({s}) {}
    };

    typedef list<Row>::iterator RowIter;
    typedef list<string>::iterator KeyIter;
    typedef pair<RowIter, KeyIter> IterPair;

    list<Row> rows;
    unordered_map<string, IterPair> iterMap;

    void insertRow(RowIter it, const string& key, int value) {
        it = rows.insert(it, Row(value, key));
        iterMap[key] = make_pair(it, it->strs.begin());
    }

    void moveUp(RowIter rowIter, KeyIter keyIter, const string& key) {
        rowIter->strs.erase(keyIter);
        int value = rowIter->val + 1;
        if (rowIter->strs.empty()) {
            rowIter = rows.erase(rowIter);
        } else {
            rowIter++;
        }
        if (rowIter == rows.end() || rowIter->val != value) {
            insertRow(rowIter, key, value);
        } else {
            rowIter->strs.push_front(key);
            iterMap[key] = make_pair(rowIter, rowIter->strs.begin());
        }
    }

    void eraseRow(RowIter rowIter) {
        rows.erase(rowIter);
    }

    void moveDown(RowIter rowIter, KeyIter keyIter, const string& key) {
        rowIter->strs.erase(keyIter);
        int value = rowIter->val - 1;
        RowIter oldIter = rowIter;
        if (value > 0) {
            if (rowIter == rows.begin() || (--rowIter)->val != value) {
                insertRow(oldIter, key, value);
            } else {
                rowIter->strs.push_front(key);
                iterMap[key] = make_pair(rowIter, rowIter->strs.begin());
            }
        } else {
            iterMap.erase(key);
        }
    
        if (oldIter->strs.empty()) {
            rows.erase(oldIter);
        }
    }
};

int main() {
    AllOne a;
    int n;
    cin >> n;
    string cmd, s;
    for (int i = 0; i < n; i++) {
        cin >> cmd;
        if (cmd == "inc") {
            cin >> s;
            a.inc(s);
        } else if (cmd == "dec") {
            cin >> s;
            a.dec(s);
        } else if (cmd == "getMinKey") {
            cout << a.getMinKey() << endl;
        } else {
            cout << a.getMaxKey() << endl;
        }
    }
    return 0;
}
