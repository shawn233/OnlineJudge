/*
 * @Author: shawn233
 * @Date: 2020-07-28 11:37:45
 * @LastEditors: shawn233
 * @LastEditTime: 2020-07-28 11:38:07
 * @Description: 219. Contains Duplicate II
 */ 

class Solution {
public:
    // 72ms (43.41%) 16.6MB (29.87%) solution 2: hash set
    // The set always keeps unique number from nums[i-k] to nums[i-1].
    bool containsNearbyDuplicate2(vector<int>& nums, int k) {
        unordered_set<int> s;
        for (int i = 0; i < nums.size(); ++ i) {
            if (i > k)
                s.erase(nums[i-k-1]);
            if (s.find(nums[i]) != s.end())
                return true;
            s.insert(nums[i]);
        }
        return false;
    }
    
    // 52ms (75.96%) 16,4MB (57.14%) solution 1: hash map
    // Key is a number, and the mapped value is the index of this number's 
    // last occurance.
    bool containsNearbyDuplicate(vector<int>& nums, int k) {
        unordered_map<int, int> mp;
        for (int i = 0; i < nums.size(); ++ i) {
            if (mp.count(nums[i]) && (i - mp[nums[i]] <= k))
                return true;
            else
                mp[nums[i]] = i; // update last index
        }
        return false;
    }
};