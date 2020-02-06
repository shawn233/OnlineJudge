class Solution {
public:
    // 12ms solution 1: two binary searches to locate the start and end positions
    // of the new interval, and get the cover range by enumerating possible relationships
    // with the neighboring intervals. With the cover range, we can get the result
    // by replacing the covered range with the new interval
    vector<vector<int>> insert(vector<vector<int>>& intervals, vector<int>& newInterval) {
        if (intervals.empty()) return {newInterval};
        
        int a = my_search(intervals, newInterval[0], 1);
        int b = my_search(intervals, newInterval[1], 0);
        int left_cov, right_cov;
        
        if (a == intervals.size()) {
            intervals.push_back(newInterval);
            return intervals;
        } else {
            left_cov = a;
        }
        
        if (b == 0) {
            if (intervals[b][0] == newInterval[1]) {
                intervals[0][0] = newInterval[0];
            } else {
                intervals.insert(intervals.begin(), newInterval);
            }
            return intervals;
        } else if (b == intervals.size() || intervals[b][0] != newInterval[1]) {
            right_cov = b-1;
        } else {
            right_cov = b;
        }
        
        vector<vector<int>> ans;
        for(int i = 0; i < left_cov; ++ i)
            ans.push_back(intervals[i]);
        ans.push_back({min(intervals[left_cov][0], newInterval[0]), 
                       max(intervals[right_cov][1], newInterval[1])});
        for (int i = right_cov+1; i < intervals.size(); ++ i)
            ans.push_back(intervals[i]);
        return ans;
    }
    
    int my_search(vector<vector<int>>& inv, int num, int pos) {
        int left = 0, right = inv.size()-1;
        int mid = 0;
        while (left <= right) {
            mid = (left+right)/2;
            if (inv[mid][pos] == num)
                return mid;
            else if (inv[mid][pos] < num)
                left = mid+1;
            else
                right = mid-1;
        }
        return left;
    }
};
