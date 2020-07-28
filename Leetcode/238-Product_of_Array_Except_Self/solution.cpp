/*
 * @Author: shawn233
 * @Date: 2020-07-28 16:37:22
 * @LastEditors: shawn233
 * @LastEditTime: 2020-07-28 16:37:30
 * @Description: 238. Product of Array Except Self
 */ 

class Solution {
public:
    // 16ms (97.07%) 15.7MB (94.79%) solution 2: O(1) extra space solution
    // In the first pass (left to right), the `output` array stores
    // the product of elements to its left: output[i] = nums[0]*...*nums[i-1].
    // Then in the second pass (right to left), the final result is obtained
    // by multiplying the product of elements to its right to the current value:
    // output[i] = output[i] * `prod_to_right`.
    // In this process, we only need a single variable to store the product.
    vector<int> productExceptSelf(vector<int>& nums) {
        vector<int> output(nums.size());
        output[0] = 1;
        
        // left to right
        for (int i = 1; i < nums.size(); ++ i)
            output[i] = output[i-1] * nums[i-1];
        
        // right to left
        int prod = 1;
        for (int i = nums.size()-2; i >= 0; -- i) {
            prod *= nums[i+1];
            output[i] *= prod;
        }
        
        return output;
    }
    
    // 32ms (26.17%) 16.3MB (24.41%) solution 1: simple O(N) solution
    vector<int> productExceptSelf1(vector<int>& nums) {
        // left_prod[i] = nums[0]*...*nums[i]
        vector<int> left_prod(nums);
        // right_prod[i] = nums[i]*...*nums[nums.size()-1]
        vector<int> right_prod(nums);
        
        for (int i = 1; i < nums.size(); ++ i)
            left_prod[i] *= left_prod[i-1];
        for (int i = nums.size()-2; i >= 0; -- i)
            right_prod[i] *= right_prod[i+1];
        
        // output[i] = left_prod[i-1] * right_prod[i+1]
        vector<int> output(nums.size());
        
        output[0] = right_prod[1];
        output[output.size()-1] = left_prod[output.size()-2];
        for (int i = 1; i < nums.size()-1; ++ i)
            output[i] = left_prod[i-1] * right_prod[i+1];
        
        return output;
    }
};