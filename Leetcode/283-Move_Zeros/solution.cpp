/*
 * @Author: shawn233
 * @Date: 2020-07-28 17:01:10
 * @LastEditors: shawn233
 * @LastEditTime: 2020-07-28 17:01:18
 * @Description: 283. Move Zeroes
 */ 

class Solution {
public:
    // 8ms (93.2%) 9.1MB (81.95%) solution 1: count zeros
    void moveZeroes(vector<int>& nums) {
        int n_zeros = 0;
        
        for (int i = 0; i < nums.size(); ++ i) {
            if (!nums[i])
                ++ n_zeros;
            else if (n_zeros)
                nums[i - n_zeros] = nums[i];
        }
        
        for (int i = nums.size() - n_zeros; i < nums.size(); ++ i)
            nums[i] = 0;
    }
};