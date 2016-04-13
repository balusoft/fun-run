/*

146. LRU Cache My Submissions Question
Total Accepted: 66895 Total Submissions: 425395 Difficulty: Hard
Design and implement a data structure for Least Recently Used (LRU) cache. It
should support the following operations: get and set.

get(key) - Get the value (will always be positive) of the key if the key exists
in the cache, otherwise return -1.
set(key, value) - Set or insert the value if the key is not already present.
When the cache reached its capacity, it should invalidate the least recently
used item before inserting a new item.

Subscribe to see which companies asked this question

Show Tags

*/
#include <memory>
#include <unordered_map>
#include <tuple>
#include <cxxtest/TestSuite.h>

using Node = std::tuple<int, int>;
std::ostream& operator<<(std::ostream& ostr, const std::list<Node> &l) {
  bool isFirst=true;
  ostr << "{";
  for (auto &e : l) {
    int k;
    int v;
    std::tie(k, v) = e;
    if (isFirst) {
      isFirst = false;
    } else {
      ostr << ", ";
    }
    ostr << "(" << k << "," <<  v << ")";
  }
  ostr << "}";
  return ostr;
}

class LRUCache {
public:
  LRUCache(const int capacity)
      : usedList_(), kv_(), capacity_(capacity) {}

  int get(int key) {
    //std::cout << "get: key: " << key << "\n";
    // if key is not there return -1
    if (kv_.find(key) == kv_.end()) {
      return -1;
    }
    auto it = kv_[key];
    usedList_.splice(usedList_.begin(), usedList_, it);
    //std::cout << "list: " << usedList_ << "\n";
    return std::get<1>(*it);//value is second value of tuple
  }

  void set(int key, int value) {
    //std::cout << "get: key: " << key << " value: " << value << "\n";
    auto kvt = std::make_tuple(key, value);
    if (kv_.find(key) != kv_.end()) {
      auto it = kv_[key];
      *it = kvt;
      usedList_.splice(usedList_.begin(), usedList_, it);
      return;
    }
    // insert new element
    // check if we have exceeded capacity
    if (kv_.size() == capacity_) {
      int k, v;
      std::tie(k, v) = usedList_.back();
      kv_.erase(k);
      usedList_.pop_back();
    }
    // now insert kvt
    usedList_.push_front(kvt);
    kv_[key] = usedList_.begin();
    //std::cout << "list: " << usedList_ << "\n";
  }
  std::list<Node> usedList_;
  std::unordered_map<int, std::list<Node>::iterator> kv_;
  const int capacity_;
};

class TestSolution : public CxxTest::TestSuite {
public:
  void XXtest_example1() {
    LRUCache cache(3);
    cache.set(1, 2);
    cache.set(2, 3);
    cache.set(3, 4);
    TS_ASSERT_EQUALS(cache.get(3), 4);
    TS_ASSERT_EQUALS(cache.get(3), 4);
    TS_ASSERT_EQUALS(cache.get(3), 4);
    TS_ASSERT_EQUALS(cache.get(1), 2);
    cache.set(4, 5);
    TS_ASSERT_EQUALS(cache.get(2), -1);
    TS_ASSERT_EQUALS(cache.get(3), 4);
    TS_ASSERT_EQUALS(cache.get(4), 5);
    TS_ASSERT_EQUALS(cache.get(1), 2);
  }
  void XXtest_example2() {
    LRUCache cache(2);
    cache.set(2, 1);
    cache.set(2, 2);
    TS_ASSERT_EQUALS(cache.get(2), 1);
    cache.set(1, 1);
    cache.set(4, 1);
    TS_ASSERT_EQUALS(cache.get(2), -1);
  }
  void test_example3() {
    LRUCache cache(3);
    cache.set(1,1);
    cache.set(2,2);
    cache.set(3,3);
    cache.set(4,4);
    TS_ASSERT_EQUALS(cache.get(4), 4);
    TS_ASSERT_EQUALS(cache.get(3), 3);
    TS_ASSERT_EQUALS(cache.get(2), 2);
    TS_ASSERT_EQUALS(cache.get(1), -1);
    cache.set(5,5);
    TS_ASSERT_EQUALS(cache.get(1), -1);
    TS_ASSERT_EQUALS(cache.get(2), 2);
    TS_ASSERT_EQUALS(cache.get(3), 3);
    TS_ASSERT_EQUALS(cache.get(4), -1);
    TS_ASSERT_EQUALS(cache.get(5), 5);
  }
};
