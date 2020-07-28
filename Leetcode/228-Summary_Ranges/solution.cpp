/*
 * @Author: shawn233
 * @Date: 2020-07-28 11:49:27
 * @LastEditors: shawn233
 * @LastEditTime: 2020-07-28 11:49:41
 * @Description: 228. Summary Ranges
 */ 

class Solution {
public:
    // 0ms (100%) 6.8MB (82.25%) solution 1: trivial
    // use `std::to_string` and `stringstream` to convert integers to strings
    vector<string> summaryRanges(vector<int>& nums) {
        vector<string> ans;
        
        int left = 0;
        for (int i = 1; i <= nums.size(); ++ i) {
            if (i == nums.size() || nums[i] != (nums[i-1]+1)) { // non-continuous
                if (i == left+1)
                    ans.push_back(to_string(nums[i-1]));
                else
                    ans.push_back(to_string(nums[left]) + "->" + to_string(nums[i-1]));
                left = i;
            }
        }
        
        return ans;
    }
};