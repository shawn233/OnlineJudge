/*
 * @Author: shawn233
 * @Date: 2020-07-28 16:53:52
 * @LastEditors: shawn233
 * @LastEditTime: 2020-07-28 16:54:09
 * @Description: 268. Missing Number
 */ 

class Solution {
public:
    // solution 1
    int missingNumber(vector<int>& nums) {
        int total = nums.size() * (nums.size()+1) / 2;
        int total_now = 0;
        for (int n: nums)
            total_now += n;
        return total - total_now;
    }
};