class Solution {
public:
    // 16ms (94.67%) 12.4MB (97.67%) solution 1:
    // sort by the interval left end
    // merge if two consecutive intervals overlap
    // note that to use sort with self-defined comparison function in a class,
    // add static in the function signature
    vector<vector<int>> merge(vector<vector<int>>& intervals) {
        vector<vector<int>> ans;
        if (intervals.size() == 0) return ans;
        sort(intervals.begin(), intervals.end(), my_less);
        int start, end;
        for (int i = 0; i < intervals.size(); ++ i) {
            if (i == 0) {
                start = intervals[i][0];
                end = intervals[i][1];
            } else if (intervals[i][0] > end) {
                ans.push_back({start, end});
                start = intervals[i][0];
                end = intervals[i][1];
            } else {
                end = max(end, intervals[i][1]);
            }
        }
        ans.push_back({start, end});
        return ans;
    }
    
    static bool my_less(vector<int>& v1, vector<int>& v2) {
        return v1[0] < v2[0];
    }
};
