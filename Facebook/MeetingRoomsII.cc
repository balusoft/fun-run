/**
Given an array of meeting time intervals consisting of start and end times
[[s1,e1],[s2,e2],...] (si < ei), find the minimum number of conference rooms
required.

For example,
Given [[0, 30],[5, 10],[15, 20]],
return 2.

Show Company Tags
Show Tags
Show Similar Problems

**/

/**
 * Definition for an interval.
 * struct Interval {
 *     int start;
 *     int end;
 *     Interval() : start(0), end(0) {}
 *     Interval(int s, int e) : start(s), end(e) {}
 * };
 */
/**
 * Definition for an interval.
 * struct Interval {
 *     int start;
 *     int end;
 *     Interval() : start(0), end(0) {}
 *     Interval(int s, int e) : start(s), end(e) {}
 * };
 */
class Solution {
public:
  int minMeetingRooms(vector<Interval> &intervals) {
    if (intervals.size() < 2) {
      return intervals.size();
    }
    std::sort(intervals.begin(), intervals.end(),
              [](const Interval &i1, const Interval &i2) {
                return i1.start < i2.start;
              });
    auto cmp = [](const Interval &i1, const Interval &i2) {
      return i1.end > i2.end;
    };
    std::priority_queue<Interval, std::vector<Interval>, decltype(cmp)> pq(cmp);
    pq.push(intervals[0]);
    for (int i = 1; i < intervals.size(); ++i) {
      Interval top = pq.top();
      pq.pop();
      if (top.end <= intervals[i].start) {
        top.end = intervals[i].end;
      } else {
        pq.push(intervals[i]);
      }
      pq.push(top);
    }
    return pq.size();
  }
  bool overlaps(const Interval &i1, const Interval &i2) {
    return i1.start >= i2.start && i1.start <= i2.end;
  }
};
