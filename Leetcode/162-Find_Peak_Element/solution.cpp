/*
 * @Author: shawn233
 * @Date: 2020-07-24 10:40:57
 * @LastEditors: shawn233
 * @LastEditTime: 2020-07-24 10:42:10
 * @Description: Leetcode 162: Find Peak Element
 */ 

class Solution {
public:
    // 4ms (99.46%) 8.9MB (63.36%) super-fast solution 2: improved binary search
    // The official solution provides a better way to implement the binary search:
    // only compare nums[mid] with nums[mid+1].
    int findPeakElement(vector<int>& nums) {
        int left = 0, right = nums.size()-1;
        while (left < right) {
            int mid = (left + right) / 2;
            if (nums[mid] > nums[mid+1])
                right = mid;
            else
                left = mid + 1;
        }
        return left;
    }
    
    // 8ms (86.08%) 9MB (38.65%) solution 1: binary search
    // The target range always moves where there must be a peak.
    int findPeakElement1(vector<int>& nums) {
        int left = 0, right = nums.size()-1;
        while (left < right) {
            int mid = (left + right) / 2;
            if ((mid == 0 || nums[mid] > nums[mid-1]) && 
                nums[mid] > nums[mid+1])
                return mid;
            else if (nums[mid] > nums[mid+1] || 
                     nums[mid] < nums[left]) // this condition deals with left=mid=right
                right = mid - 1;
            else
                left = mid + 1;
        }
        return left;
    }
};
