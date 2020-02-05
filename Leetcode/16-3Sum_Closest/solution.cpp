class Solution {
public:
    // 12ms solution: fix x, find y and z
    // follow the sorted two sum closest routine
    // when y+z > target, decrease z, 
    // when y+z < target, increase y
    int threeSumClosest(vector<int>& nums, int target) {
        sort(nums.begin(), nums.end());
        int prev = nums[0]-1;
        int left, right, k, min_diff=(1<<16), new_diff;
        int ans = 0;
        for (int i = 0; i < nums.size()-2; ++ i) {
            if (nums[i] == prev) continue;
            else prev = nums[i];
            // two pointers: sorted two sum closest
            left = i+1;
            right = nums.size()-1;
            k = target - nums[i];
            while (left < right) {
                new_diff = abs(nums[left]+nums[right]-k);
                if (new_diff < min_diff) {
                    min_diff = new_diff;
                    ans = nums[left]+nums[right]+nums[i];
                }
                if (nums[left]+nums[right] == k) break;
                else if (nums[left]+nums[right] < k) ++ left;
                else -- right;
            }
        }
        return ans;
    }
};
