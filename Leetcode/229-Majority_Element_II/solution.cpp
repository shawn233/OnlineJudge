/*
 * @Author: shawn233
 * @Date: 2020-07-28 15:59:02
 * @LastEditors: shawn233
 * @LastEditTime: 2020-07-28 15:59:19
 * @Description: 229. Majority Element II
 */ 

class Solution {
public:
    // 40ms (35.92%) 15.4% (93.6%) solution 1: modified boyer-moore algorithm
    // Reference 1: https://leetcode.com/problems/majority-element-ii/discuss/63520/Boyer-Moore-Majority-Vote-algorithm-and-my-elaboration
    // Reference 2: https://zhuanlan.zhihu.com/p/85474828
    vector<int> majorityElement(vector<int>& nums) {
        int count1 = 0, candidate1 = 0;
        int count2 = 0, candidate2 = 0;
        
        for (int n: nums) {
            if (n == candidate1)
                ++ count1;
            else if (n == candidate2)
                ++ count2;
            else if (count1 == 0) {
                candidate1 = n;
                count1 = 1;
            } else if (count2 == 0) {
                candidate2 = n;
                count2 = 1;
            } else {
                -- count1;
                -- count2;
            }
        }
        
        vector<int> ans;
        count1 = count2 = 0;
        for (int n: nums) {
            if (n == candidate1)
                ++ count1;
            else if (n == candidate2)
                ++ count2;
        }
        
        if (count1 > nums.size()/3)
            ans.push_back(candidate1);
        if (count2 > nums.size()/3)
            ans.push_back(candidate2);
        
        return ans;
    }
};