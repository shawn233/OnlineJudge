class Solution {
public:
    // 28ms solution 3: prune based on solution 2, early stop when nums[a]+...+nums[a+3] > target
    // 52ms solution 2: prune based on solution 1, skip when nums[a]+nums[-3]+nums[-2]+nums[-1] < target
    // 68ms solution 1: reduce to sorted two sum by two loops O(n^3)
    vector<vector<int>> fourSum(vector<int>& nums, int target) {
        vector<vector<int>> ans;
        if (nums.size() < 4) return ans;
        sort(nums.begin(), nums.end());
        int left, right, tmp;
        // for pruning to optimize
        int largest = nums[nums.size()-1];
        int two_largest = largest + nums[nums.size()-2];
        int three_largest = two_largest + nums[nums.size()-3];
        for (int a = 0; a < nums.size()-3; ++ a) {
            if (a > 0 && nums[a] == nums[a-1]) continue;
            else if (nums[a]+nums[a+1]+nums[a+2]+nums[a+3] > target) break;
            else if (nums[a]+three_largest < target) continue;
            // three sum
            for (int b = a+1; b < nums.size()-2; ++ b) {
                if (b > a+1 && nums[b] == nums[b-1]) continue;
                else if (nums[a]+nums[b]+two_largest < target) continue;
                left = b+1;
                right = nums.size()-1;
                // sorted two sum
                while (left < right) {
                    tmp = nums[a]+nums[b]+nums[left]+nums[right];
                    if (tmp == target) {
                        ans.push_back({nums[a], nums[b], nums[left], nums[right]});
                        // sorted two sum trick: use do...while... after finding an answer to prevent duplicate answers
                        do {++ left;} while (left < right && nums[left] == nums[left-1]);
                        do {-- right;} while (left < right && nums[right] == nums[right+1]);
                    } else if (tmp < target) ++ left;
                    else -- right;
                }
            }
        }
        return ans;
    }
};
