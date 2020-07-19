/*
 * @Author: shawn233
 * @Date: 2020-07-19 12:29:02
 * @LastEditors: shawn233
 * @LastEditTime: 2020-07-19 12:30:37
 * @Description: Leetcode 152: Maximum Product Subarray
 */ 

class Solution {
public:
    
    // 8ms (79.22%) 12.1MB (9.32%) solution 3: the most concise version of solution 2
    // I like its beautiful code organization!
    // Reference: https://leetcode.com/problems/maximum-product-subarray/discuss/48230/Possibly-simplest-solution-with-O(n)-time-complexity
    int maxProduct(vector<int>& nums) {
        int max_so_far, min_so_far, ans;
        
        for (int i = 1, max_so_far=min_so_far=ans=nums[0]; i < nums.size(); ++ i) {
            if (nums[i] < 0) swap(max_so_far, min_so_far);
            max_so_far = max(max_so_far*nums[i], nums[i]);
            min_so_far = min(min_so_far*nums[i], nums[i]);
            ans = max(ans, max_so_far);
        }
        
        return ans;
    }
    
    // 8ms (79.22%) 11.8MB (56.59%) solution 2: one-pass dynamic-programming solution
    //    The property of negative numbers in multiplication: 
    // changing the minimum value to the largest value
    int maxProduct2(vector<int>& nums) {
        // dp: max/min production of the contiguous subarray ending with nums[i]
        int max_so_far, min_so_far, tmp;
        int ans;
        
        max_so_far = min_so_far = ans = nums[0];
        
        for (int i = 1; i < nums.size(); ++ i) {
            // max_so_far = max(nums[i], 
            //                  max_so_far*nums[i], 
            //                  min_so_far*nums[i])
            // min_so_far = min(nums[i], 
            //                  max_so_far*nums[i], 
            //                  min_so_far*nums[i])
            if (nums[i] > 0) {
                // I add this comparison to reduce the number of following comparisons.
                // Actually this comparison is optional, as shown in the equations above.
                max_so_far = max(max_so_far*nums[i], nums[i]);
                min_so_far = min(min_so_far*nums[i], nums[i]);
            } else {
                ans = max(ans, max_so_far);
                tmp = min_so_far;
                min_so_far = min(max_so_far*nums[i], nums[i]);
                max_so_far = max(tmp*nums[i], nums[i]);
            }
        }
        
        ans = max(ans, max_so_far);
        return ans;
    }
    
    // 4ms (98.20%) 11.9MB (25.23%) solution 1: two-pass concise solution
    int maxProduct1(vector<int>& nums) {
        int ans = nums[0];
        int prod = 0;
        
        for (int i = 0; i < nums.size(); ++ i) {
            if (prod == 0)
                prod = nums[i];
            else 
                prod *= nums[i];
            ans = max(ans, prod);
        }
        
        prod = 0;
        for (int i = nums.size()-1; i >= 0; -- i) {
            if (prod == 0)
                prod = nums[i];
            else 
                prod *= nums[i];
            ans = max(ans, prod);
        }
        
        return ans;
    }
};