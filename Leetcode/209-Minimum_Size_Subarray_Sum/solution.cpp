/*
 * @Author: shawn233
 * @Date: 2020-07-27 17:08:54
 * @LastEditors: shawn233
 * @LastEditTime: 2020-07-27 17:09:48
 * @Description: 209. Minimum Size Subarray Sum
 */ 

class Solution {
public:
    // 16ms (84.51%) 11MB (5.29%) solution 3: binary search
    // Pre-processing: for any 0 <= i <= nums.size(),
    // sum[i] = nums[0] + nums[1] + ... + nums[i];
    // Binary search: for starting point i, the shortest contiguous subarray with
    // its sum greater than `s` can be found by searching the first larger element
    // than `sums[i] + s`, say `right_pos`.
    // The length is `right_pos - i + 1`.
    // O(N logN)
    int minSubArrayLen(int s, vector<int>& nums) {
        vector<int> sums(nums);
        for (int i = 1; i < sums.size(); ++ i)
            sums[i] += sums[i-1];
        
        int sum_to_left = 0;
        int ans = nums.size()+1;
        for (int i = 0; i < nums.size(); ++ i) {
            int right_pos = my_search(sums, sum_to_left+s);
            ans = min(ans, right_pos - i + 1);
            sum_to_left = sums[i];
        }
        
        if (ans == nums.size()+1)
            ans = 0;
        return ans;
    }
    
    int my_search(vector<int>& sums, int target) {
        if (target > sums[sums.size()-1])
            return 2*sums.size();
        int left = 0, right = sums.size()-1;
        while (left < right) {
            int mid = (left + right) / 2;
            if (sums[mid] == target) {
                return mid;
            } else if (sums[mid] < target)
                left = mid+1;
            else
                right = mid;
        }
        
        return left;
    }
    
    // 16ms (84.51%) 10.5MB (91.47%) solution 2: one-pass scan (two pointers)
    // Try all possible shortest contiguous subarrays without duplicate additions:
    // Whenever the current contiguous subarray sums up equal to or larger than `s`, 
    // keep droping the leading elements until its sum is smaller than `s`.
    // O(N)
    int minSubArrayLen2(int s, vector<int>& nums) {
        int ans = nums.size()+1;
        
        for (int start = 0, end = 0, sum = 0, len = 0; end < nums.size(); ++ end) {
            sum += nums[end];
            ++ len;
            
            while (sum >= s) {
                ans = min(ans, len);
                sum -= nums[start];
                ++ start;
                -- len;
            }
        }
        
        if (ans == nums.size()+1)
            ans = 0;
        return ans;
    }
    
    // 680ms (5.03%) 10.5MB (90.1%) solution 1: brute force
    // Try all possible shortest contiguous subarrays
    // O(N^2)
    int minSubArrayLen1(int s, vector<int>& nums) {
        int ans = nums.size()+1;
        for (int i = 0; i < nums.size(); ++ i) {
            int sum = 0;
            for (int j = i; j < nums.size(); ++ j) {
                sum += nums[j];
                if (sum >= s) {
                    ans = min(ans, j-i+1);
                    break;
                }
            }
        }
        if (ans > nums.size())
            ans = 0;
        return ans;
    }
};