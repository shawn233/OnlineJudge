class Solution {
public:
    // 4ms (98.33%) 9MB (94.92%) solution 1
    // the key observation is that
    // all subsets for 1,2,...,i (denoted as subsets(i)) is the union of
    // subsets(i-1) and [for any subset in subsets(i-1), add i]
    vector<vector<int>> subsets(vector<int>& nums) {
        vector<vector<int>> ans;
        ans.push_back({});
        for (int i = 0; i < nums.size(); ++ i) {
            for (int j = 0; j < (1<<i); ++ j) {
                ans.push_back(ans[j]);
                ans[j].push_back(nums[i]);
            }
        }
        return ans;
    }
};
