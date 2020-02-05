class Solution {
public:
    vector<int> twoSum(vector<int>& nums, int target) {
        // create and initialize a hash map
        unordered_map<int, int> mp;
        for (int i = 0; i < nums.size(); ++ i)
            mp[nums[i]] = i;
        
        // now let's find the answer
        int x, y;
        for (int i = 0; i < nums.size(); ++ i) {
            x = nums[i];
            y = target - x;
            auto iter = mp.find(y);
            if (iter != mp.end() && iter->second != i)
                return {i, iter->second};
        }
        
        return {};
    }
};
