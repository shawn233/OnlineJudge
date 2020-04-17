class Solution {
public:
    // 8ms (84%) solution 1: count duplicate numbers 
    // to prevent duplicate subsets
    //
    // There seems to be a faster solution with hash map.
    vector<vector<int>> subsetsWithDup(vector<int>& nums) {
        vector<vector<int>> ans = {{}};
        
        sort(nums.begin(), nums.end());
        
        int dup_cnt = 1;
        for (int i = 0; i < nums.size(); ++ i) {
            if (i == nums.size()-1 || nums[i] != nums[i+1]) {
                int sz = ans.size();
                for (int j = 0; j < sz; ++ j) {
                    for (int t = 0; t < dup_cnt; ++ t) {
                        ans.push_back(ans[j]);
                        ans[j].push_back(nums[i]);
                    }
                }
                
                dup_cnt = 1;
            } else {
                ++ dup_cnt;
            }
        }
        
        return ans;
    }
};
