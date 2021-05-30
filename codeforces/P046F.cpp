// https://codeforces.com/problemset/problem/46/F
// Hercule Poirot Problem

#include <bits/stdc++.h>
using namespace std;

class BitMask {
 public:
  BitMask() {
    memset(mask_, 0, sizeof(mask_));
  }
  void set(int i) {
    mask_[i/64] |= ((uint64_t(1)) << (i%64));
  }

  bool get(int i) const {
    return (mask_[i/64] >> (i%64)) & 1;
  }

  BitMask& operator |= (const BitMask& other) {
    for (int i = 0; i < 16; i++) {
      mask_[i] |= other.mask_[i];
    }
    return *this;
  }

  bool operator == (const BitMask& other) const {
    for (int i = 0; i < 16; i++) {
      if (mask_[i] != other.mask_[i]) return false;
    }
    return true;
  }
 private:
  uint64_t mask_[16];
};

const int MAXN = 1010;
int N, M, K;
struct Edge {
  int u, v;
} E[MAXN];

class Realm {
 public:
  void merge(const Realm& other) {
    rooms_ |= other.rooms_;
    residents_ |= other.residents_;
    keys_ |= other.keys_;
  }

  void addRoom(int r) {
    rooms_.set(r);
  }

  void addResident(int r) {
    residents_.set(r);
  }

  void addKey(int k) {
    keys_.set(k);
  }

  bool operator == (const Realm& other) const {
    return rooms_ == other.rooms_ && residents_ == other.residents_ &&
        keys_ == other.keys_;
  }

  bool operator != (const Realm& other) const {
    return !(*this == other);
  }

 private:
  BitMask rooms_, residents_, keys_;
  friend class Solver;
};

class Solver {
 public:
  Solver(int n) : n_(n) {
    alloc();
    for (int i = 0; i < n_; i++) {
      realms_[i].addRoom(i);
      roomToRealm_[i] = i;
    }
  }

  ~Solver() {
    dealloc();
  }

  void addResident(int res, int room, const vector<int>& keys) {
    realms_[room].addRoom(room);
    realms_[room].addResident(res);
    for (int key : keys) {
      realms_[room].addKey(key);
    }
  }

  void explore(int r) {
    bool updated = false;
    for (int i = 0; i < M; i++) {
      if (!realms_[r].keys_.get(i)) continue;
      int u = E[i].u;
      int v = E[i].v;
      if (roomToRealm_[u] == r && roomToRealm_[v] != r) {
        int s = roomToRealm_[v];
        realms_[r].merge(realms_[s]);
        for (int j = 0; j < N; j++) {
          if (roomToRealm_[j] == s) roomToRealm_[j] = r;
        }
        updated = true;
        queue_.erase(s);
      } else if (roomToRealm_[u] != r && roomToRealm_[v] == r) {
        int s = roomToRealm_[u];
        realms_[r].merge(realms_[s]);
        for (int j = 0; j < N; j++) {
          if (roomToRealm_[j] == s) roomToRealm_[j] = r;
        }
        updated = true;
        queue_.erase(s);
      }
    }
    if (!updated) {
      queue_.erase(r);
    }
  }

  bool operator == (const Solver& other) const {
    for (int i = 0; i < N; i++) {
      int u = roomToRealm_[i];
      int v = other.roomToRealm_[i];
      if (realms_[u] != other.realms_[v]) return false;
    }
    return true;
  }

  void solve() {
    for (int i = 0; i < N; i++) {
      queue_.insert(i);
    }
    while (!queue_.empty()) {
      int r = *queue_.begin();
      explore(r);
    }
  }

 private:
  int n_;
  int* roomToRealm_;
  Realm* realms_;
  set<int> queue_;

  void alloc() {
    roomToRealm_ = new int[n_]{};
    realms_ = new Realm[n_]{};
  }

  void dealloc() {
    delete[] roomToRealm_;
    delete[] realms_;
  }
};

int main() {
  scanf("%d%d%d", &N, &M, &K);
  for (int i = 0; i < M; i++) {
    int u, v;
    scanf("%d%d", &u, &v);
    u--; v--;
    E[i] = {u, v};
  }
  map<string, int> strMap;
  Solver before(N);
  for (int i = 0; i < K; i++) {
    string res;
    int room;
    cin >> res >> room;
    strMap[res] = i;
    room--;
    int nk;
    cin >> nk;
    vector<int> keys(nk);
    for (int j = 0; j < nk; j++) {
      scanf("%d", &keys[j]);
      keys[j]--;
    }
    before.addResident(i, room, keys);
  }
  before.solve();

  Solver after(N);
  for (int i = 0; i < K; i++) {
    string res;
    int room;
    cin >> res >> room;
    room--;
    int r = strMap.at(res);
    int nk;
    cin >> nk;
    vector<int> keys(nk);
    for (int j = 0; j < nk; j++) {
      scanf("%d", &keys[j]);
      keys[j]--;
    }
    after.addResident(r, room, keys);
  }
  after.solve();
  if (before == after) {
    printf("YES\n");
  } else {
    printf("NO\n");
  }

  return 0;
}
