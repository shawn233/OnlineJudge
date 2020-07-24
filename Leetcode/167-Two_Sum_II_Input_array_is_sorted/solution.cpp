/*
 * @Author: shawn233
 * @Date: 2020-07-24 22:04:46
 * @LastEditors: shawn233
 * @LastEditTime: 2020-07-24 22:05:10
 * @Description: Leetcode 167: Two Sum II - Input array is sorted
 */ 

class Solution {
public:
    // 8ms (96.65%) 9.8MB (49.87%) solution 1: two pointers
    vector<int> twoSum(vector<int>& numbers, int target) {
        int left = 0, right = numbers.size()-1;
        while (true) {
            int addition = numbers[left] + numbers[right];
            if (addition < target)
                ++ left;
            else if (addition > target)
                -- right;
            else
                return {left+1, right+1};
        }
    }
};