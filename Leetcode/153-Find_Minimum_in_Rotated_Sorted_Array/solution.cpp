/*
 * @Author: shawn233
 * @Date: 2020-07-19 12:42:27
 * @LastEditors: shawn233
 * @LastEditTime: 2020-07-19 12:42:54
 * @Description: Leetcode 153: Find Minimum in Rotated Sorted Array
 */ 

class Solution {
public:
    // 4ms (94.72%) 10.2MB (65.47%) solution: binary search
    int findMin(vector<int>& nums) {
        int left = 0, right = nums.size()-1;
        while (true) {
            if (left == right || nums[left] < nums[right])
                return nums[left];
            int mid = (left + right) / 2;
            if (nums[mid] < nums[right])
                right = mid;
            else
                left = mid+1;
        }
    }
};
