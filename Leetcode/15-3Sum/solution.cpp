class Solution {
public:
    // 440ms solution 1: sort, then use hash-table based two sum (non-sorted version)
    // 108ms solution 2: sort, then use sorted two sum (two pointers)
    vector<vector<int>> threeSum(vector<int>& nums) {
        vector<vector<int>> ans;
        //unordered_map<int, int> mp;
        
        if (nums.size() < 3)
            return ans;
        
        sort(nums.begin(), nums.end());
        /*
        for (int i = 0; i < nums.size(); ++i) {
            mp[nums[i]] = i;
        }
        */
        
        int prev = nums[0]-1;
        for (int i = 0; i < nums.size() && nums[i] <= 0; ++ i) {
            if (nums[i] == prev) continue;
            else prev = nums[i];
            //twoSum(nums, ans, mp, i);
            twoSumSorted(nums, ans, i);
        }
        
        return ans;
    }
    
    void twoSum(vector<int>& nums, vector<vector<int>>& ans, unordered_map<int, int>& mp, int k) {
        // each result contains three elements which sum up to -nums[k]
        int prev = nums[0]-1;
        for (int i = k+1; i < nums.size(); ++ i) {
            if (nums[i] == prev) continue;
            else prev = nums[i];
            int dif = - nums[k] - nums[i];
            int ind = mp[dif];
            if (ind <= i || ind == k) continue;
            else 
                ans.push_back({nums[k], nums[i], nums[ind]});
        }
    }
    
    void twoSumSorted(vector<int>& nums, vector<vector<int>>& ans, int k) {
        // find triplets which sum up to -nums[k]
        int left = k+1, right = nums.size()-1;
        while (left < right) {
            if (nums[left]+nums[right]+nums[k] == 0) {
                //printf("k: %d left: %d right: %d\n", k, left, right);
                ans.push_back({nums[k], nums[left], nums[right]});
                do {++left;} while (left < right && nums[left-1] == nums[left]);
                do {--right;} while (left < right && nums[right+1] == nums[right]);
            }
            else if (nums[left]+nums[right]+nums[k] < 0) {
                do {++left;} while (left < right && nums[left-1] == nums[left]);
            } else {
                do {--right;} while (left < right && nums[right+1] == nums[right]);
            }
        }
    }
};
