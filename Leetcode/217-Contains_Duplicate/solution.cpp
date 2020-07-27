/*
 * @Author: shawn233
 * @Date: 2020-07-27 17:59:27
 * @LastEditors: shawn233
 * @LastEditTime: 2020-07-27 18:07:07
 * @Description: 217. Contains Duplicate
 */ 

class Solution {
public:
    // 64ms (82.72%) 20MB (62.62%) solution 2: hash map
    bool containsDuplicate(vector<int>& nums) {
        unordered_map<int, int> mp;
        for (int i: nums) {
            if (!mp.count(i))
                mp.insert({i, 1});
            else
                return true;
        }
        return false;
    }
    
    // 52ms (98.22%) 15.7MB (83.63%) solution 1: sorting
    bool containsDuplicate1(vector<int>& nums) {
        sort(nums.begin(), nums.end());
        for (int i = 1; i < nums.size(); ++ i)
            if (nums[i] == nums[i-1])
                return true;
        return false;
    }
};