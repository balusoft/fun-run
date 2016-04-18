/**
Given an array of meeting time intervals consisting of start and end times
[[s1,e1],[s2,e2],...] (si < ei), determine if a person could attend all
meetings.

For example,
Given [[0, 30],[5, 10],[15, 20]],
return false.

Show Company Tags
Show Tags
Show Similar Problems
**/
struct Interval {
  int start;
  int end;
  Interval() : start(0), end(0) {}
  Interval(int s, int e) : start(s), end(e) {}
};

class Solution {
public:
    bool canAttendMeetings(vector<Interval>& intervals) {
        if (intervals.size() < 2) {
            return true;
        }
        std::sort(intervals.begin(), intervals.end(),
                  [](const Interval &x, const Interval &y) {
                    return x.start < y.start;
                  });
        for (size_t idx=1; idx<intervals.size(); ++idx) {
            if (intervals[idx].start < intervals[idx-1].end) {
                return false;
            }
        }
        return true;
    }
};
