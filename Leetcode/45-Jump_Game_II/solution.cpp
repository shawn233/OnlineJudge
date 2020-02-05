class Solution {
public:
    // 4ms solution 2: BFS
    // reference to ![discussion](https://leetcode.com/problems/jump-game-ii/discuss/18019/10-lines-C%2B%2B-(16ms)-Python-BFS-Solutions-with-Explanations)
    // This problem has a nice BFS structure.
    // In order to get the steps to reach the end, we don't need to know
    // the steps at all positions, as I did in the dp solution.
    // Instead, the BFS structure allows us to know the farthest 
    // range of positions to reach with a certain number of steps, 
    // in O(n) time. When the range covers the end, we get the steps
    // that we need.
    int jump(vector<int>& nums) {
        int start = 0, end = 0; // assume nums.size()>0
        int ans = 0, new_end;
        while (end < nums.size()-1) {
            ++ ans;
            for (new_end = end; new_end < nums.size()-1 && start <= end; ++ start) {
                new_end = max(new_end, start+nums[start]);
            }
            end = new_end;
        }
        return ans;
    }

    // Time Limited Exceeded solution 1
    // dynamic programming, O(n^2) complexity
    int jump1(vector<int>& nums) {
        vector<int> dp(nums.size(), (1<<16));
        dp[dp.size()-1] = 0;
        for (int i = nums.size()-2; i >= 0; -- i) {
            for (int j = min(i+nums[i], (int)nums.size()-1); j > i; -- j)
                dp[i] = min(dp[i], 1+dp[j]);
        }
        //cout << "nums: " << nums << endl;
        //cout << "dp:   " << dp << endl;
        return dp[0];
    }
};
