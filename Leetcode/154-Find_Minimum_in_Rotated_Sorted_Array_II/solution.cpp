/*
 * @Author: shawn233
 * @Date: 2020-07-19 14:47:07
 * @LastEditors: shawn233
 * @LastEditTime: 2020-07-19 14:47:58
 * @Description: Leetcode 154: Find Minimum in Rotated Sorted Array II
 */ 

class Solution {
public:
    // 8ms (96.54%) 12.5MB (13.84%)solution 3: a clear binary search
    // Reference: https://leetcode.com/problems/find-minimum-in-rotated-sorted-array-ii/discuss/167981/Beats-100-Binary-Search-with-Explanations
    // I think this solution is actually the same as solution 2.
    // In the while loop, each time we detect which half of the array is sorted.
    // But this solution is faster because it doesn't compare nums[left] and nums[right]
    int findMin(vector<int>& nums) {
        int left = 0, right = nums.size()-1;
        int mid;
        
        while (left < right) {
            mid = left + (right - left) / 2;
            if (nums[mid] > nums[right])
                left = mid+1;
            else if (nums[mid] < nums[left]) {
                ++ left;
                right = mid;
            } else // in this case, nums[left] <= nums[mid] <= nums[right]
                   // we can -- right since nums[right] can be dropped
                   // but we can't ++ left since nums[left] may be the only pivot
                -- right;
        }
        
        return nums[left];
    }
    
    // 12ms (69.99%) 12.6MB (7.71%) solution 2: binary search
    int findMin2(vector<int>& nums) {
        int left = 0, right = nums.size()-1;
        int mid;
        
        while (true) {
            if (left == right || nums[left] < nums[right])
                return nums[left];
            else {
                mid = left + (right - left) / 2;
                if (nums[mid] < nums[right])
                    right = mid;
                else if (nums[mid] > nums[right])
                    left = mid+1;
                else
                    ++left;
            }
        }
    }
    
    // 8ms (96.54%) 12.3MB (85.46%) solution 1: one-pass search
    // search for the first position where the number descends
    int findMin1(vector<int>& nums) {
        for (int i = 1; i < nums.size(); ++ i) {
            if (nums[i] < nums[i-1])
                return nums[i];
        }
        return nums[0];
    }
};