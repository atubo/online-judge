#include <algorithm>
#include <iostream>
#include <limits>
#include <deque>
#include <vector>
#include <cassert>
using namespace std;

struct Node {
    Node() {
        id     = -1;
        left   = -1;
        right  = -1;
        parent = -1;
        key    = -1;
        depth  = -1;
        minVal = numeric_limits<int>::max();
        maxVal = -1;
    }

    int id;
    int left;
    int right;
    int parent;
    int key;
    int depth;
    int minVal;
    int maxVal;
};

class DepthComparator {
public:
    DepthComparator(const Node* tree_):tree(tree_) {}
    bool operator()(int a, int b) {
        return tree[a].depth > tree[b].depth;
    }
private:
    const Node* tree;
};

struct Range {
    Range(int left_ = 0, int right_ = 0, int id_ = 0):
        left(left_), right(right_), id(id_) {}
    int left;
    int right;
    int id;

    bool operator < (const Range& other) const {
        if (left < other.left) return true;
        if (left > other.left) return false;
        return right < other.right;
    }
};

bool inRange(const Range& range, int key)
{
    return range.left < key && key < range.right;
}

int findLeafId(const vector<Range>& leafRanges, int key)
{
    int i = 0;
    int j = leafRanges.size()-1;
    if (inRange(leafRanges[i], key)) {
        return leafRanges[i].id;
    }
    if (inRange(leafRanges[j], key)) {
        return leafRanges[j].id;
    }
    while (i < j) {
        int mid = (i+j)/2;
        if (inRange(leafRanges[mid], key)) {
            return leafRanges[mid].id;
        }
        if (key < leafRanges[mid].left) {
            j = mid;
        } else {
            i = mid;
        }
    }
    return leafRanges[i].id;
}

int main()
{
    int N;
    cin >> N;
    Node tree[N];
    int root = -1;
    for (int i = 0; i < N; i++) {
        int p, k;
        cin >> p >> k;
        if (p > 0) p--;
        tree[i].id     = i;
        tree[i].parent = p;
        tree[i].key    = k;
        if (p == -1) root = i;
    }
    // set up left, right pointers
    for (int i = 0; i < N; i++) {
        if (i != root) {
            int parent = tree[i].parent;
            if (tree[parent].key > tree[i].key) {
                tree[parent].left = tree[i].id;
            } else {
                tree[parent].right = tree[i].id;
            }
        }
    }
    
    // BFS to set up depth
    deque<int> queue;
    tree[root].depth = 0;
    queue.push_back(root);
    while (!queue.empty()) {
        const Node& node = tree[queue.front()];
        int d = node.depth;
        queue.pop_front();
        if (node.left >= 0) {
            assert(node.right >= 0);
            tree[node.left].depth  = d + 1;
            tree[node.right].depth = d + 1;
            queue.push_back(node.left);
            queue.push_back(node.right);
        }
    }

    // sort node by depth and set up min/max value
    int ids[N];
    for (int i = 0; i < N; i++) {
        ids[i] = i;
    }
    sort(ids, ids+N, DepthComparator(tree));
    for (int i = 0; i < N; i++) {
        Node& node = tree[ids[i]];
        if (node.left == -1) {
            node.minVal = node.maxVal = node.key;
        } else {
            node.minVal = tree[node.left].minVal;
            node.maxVal = tree[node.right].maxVal;
        }
    }

    int64_t dp[N];
    queue.push_back(root);
    dp[root] = 0;
    while (!queue.empty()) {
        const Node& node = tree[queue.front()];
        queue.pop_front();
        if (node.left != -1) {
            dp[node.left]  = dp[node.id] + tree[node.right].minVal;
            dp[node.right] = dp[node.id] + tree[node.left].maxVal;
            queue.push_back(node.left);
            queue.push_back(node.right);
        }
    }

    vector<Range> leafRanges;
    Range ranges[N];
    queue.push_back(root);
    ranges[root] = Range(0, numeric_limits<int>::max(), root);
    while (!queue.empty()) {
        const Range& prange = ranges[queue.front()];
        const Node& node = tree[queue.front()];
        queue.pop_front();
        if (node.left != -1) {
            ranges[node.left]  = Range(prange.left, node.key, node.left);
            ranges[node.right] = Range(node.key, prange.right, node.right);
            queue.push_back(node.left);
            queue.push_back(node.right);
        } else {
            leafRanges.push_back(ranges[node.id]);
        }
    }
    sort(leafRanges.begin(), leafRanges.end());

    int K;
    cin >> K;
    for (int i = 0; i < K; i++) {
        int key;
        cin >> key;
        int leafId = findLeafId(leafRanges, key);
        printf("%.9f\n", dp[leafId]/double(tree[leafId].depth));
    }

    return 0;
}



