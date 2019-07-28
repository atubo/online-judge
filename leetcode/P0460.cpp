// https://leetcode.com/problems/lfu-cache/
// 460. LFU Cache

#include <bits/stdc++.h>
using namespace std;
#include "../utils/BinaryTree.h"
#include "../utils/Graph.h"
#include "../utils/LinkedList.h"
#include "../utils/Util.h"

class LFUCache {
    struct FNode;

    struct DNode {
        int key;
        int value;
        FNode *parent;
        DNode *prev, *next;
    };

    struct DList {
        DList(FNode* p): parent(p), head(NULL), tail(NULL) {}
        FNode *parent;
        DNode *head, *tail;
        bool empty() const {
            return head == NULL;
        }

        void push_back(DNode *node) {
            node->parent = parent;
            if (!head) {
                head = tail = node;
                node->prev = node->next = NULL;
            } else {
                tail->next = node;
                node->prev = tail;
                node->next = NULL;
                tail = node;
            }
        }

        DNode* pop_front() {
            assert(head);
            auto ret = head;
            if (!head->next) {
                head = tail = NULL;
            } else {
                head = head->next;
                head->prev = NULL;
            }
            return ret;
        }

        void erase(DNode *node) {
            if (head == node) {
                head = head->next;
                if (head) head->prev = NULL;
            } else if (tail == node) {
                tail = tail->prev;
                if (tail) tail->next = NULL;
            } else {
                auto prev = node->prev;
                auto next = node->next;
                prev->next = next;
                next->prev = prev;
            }
        }
    };

    struct FNode {
        FNode(int f): dlist(this) {
            freq = f;
            prev = next = NULL;
        }
        int freq;
        FNode *prev, *next;
        DList dlist;
    };


    struct FList {
        FNode *head;
        FList(): head(NULL) {}

        void inc(DNode *node) {
            FNode *fnode = node->parent;
            fnode->dlist.erase(node);
            if (fnode->next && fnode->next->freq == fnode->freq+1) {
                fnode->next->dlist.push_back(node);
            } else {
                FNode *fnew = new FNode(fnode->freq+1);
                fnew->dlist.push_back(node);
                fnew->next = fnode->next;
                fnode->next = fnew;
                fnew->prev = fnode;
                if (fnew->next) fnew->next->prev = fnew;
            }
            if (fnode->dlist.empty()) {
                erase(fnode);
            }
        }

        void erase(FNode *fnode) {
            if (head == fnode) {
                head = head->next;
                if (head) head->prev = NULL;
            } else {
                auto prev = fnode->prev;
                auto next = fnode->next;
                if (prev) prev->next = next;
                if (next) next->prev = prev;
            }
            delete fnode;
        }

        DNode *evict() {
            DNode *ret = head->dlist.pop_front();
            if (head->dlist.empty()) erase(head);
            return ret;
        }

        void push_front(DNode *node) {
            if (!head || head->freq > 1) {
                FNode *fnew = new FNode(1);
                fnew->dlist.push_back(node);
                fnew->next = head;
                if (head) head->prev = fnew;
                head = fnew;
            } else {
                head->dlist.push_back(node);
            }
        }
    };

public:
    LFUCache(int capacity): cap_(capacity) {}

    int get(int key) {
        if (cap_ == 0) return -1;
        if (data_.find(key) == data_.end()) return -1;
        auto dnode = data_[key];
        flist_.inc(dnode);
        return dnode->value;
    }

    void put(int key, int value) {
        if (cap_ == 0) return;
        if (data_.find(key) != data_.end()) {
            auto node = data_[key];
            node->value = value;
            flist_.inc(node);
            return;
        }
        if ((int)data_.size() < cap_) {
            DNode *node = new DNode{key, value, NULL, NULL, NULL};
            flist_.push_front(node);
            data_[key] = node;
        } else {
            DNode *node = flist_.evict();
            node->value = value;
            flist_.push_front(node);
            data_.erase(node->key);
            node->key = key;
            data_[key] = node;
        }
    }

private:
    map<int, DNode*> data_;
    int cap_;
    FList flist_;
};

int main() {
    LFUCache lfu(1);
    lfu.put(2, 1);
    cout << lfu.get(2) << endl;
    lfu.put(3, 2);
    cout << lfu.get(2) << endl;
    cout << lfu.get(3) << endl;
    return 0;
}
