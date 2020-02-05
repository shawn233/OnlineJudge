class Solution {
public:
    // 4ms solution 1: no comment, just remember the pattern
    int maxSubArray(vector<int>& nums) {
        int ans = nums[0];
        int tmp_sum = 0;
        for (int i = 0; i < nums.size(); ++ i) {
            tmp_sum += nums[i];
            ans = max(ans, tmp_sum);
            tmp_sum = max(0, tmp_sum);
        }
        return ans;
    }
};
