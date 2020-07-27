/*
 * @Author: shawn233
 * @Date: 2020-07-27 12:31:54
 * @LastEditors: shawn233
 * @LastEditTime: 2020-07-27 12:32:19
 * @Description: Leetcode 189: Rotate Array
 */ 

class Solution {
public:
    // 4ms (99.46%) 10.1MB (29.33%) solution 3: using reverse
    // 3 reverse operations can solve this problem
    // from Approach 4 in the official solution
    void rotate3(vector<int>& nums, int k) {
        k = k % nums.size();
        reverse(nums.begin(), nums.end());
        reverse(nums.begin(), nums.begin()+k);
        reverse(nums.begin()+k, nums.end());
    }
    
    // 4ms (99.46%) 9.9MB (82.56%) solution 2: in-place rotation
    // Cyclic replacement
    void rotate(vector<int>& nums, int k) {
        k = k % nums.size();
        if (k == 0)
            return;
        
        int n_rotation = 0;
        int pivot = 0, i = 0, tmp = nums[0];
        
        while (n_rotation != nums.size()) {
            ++ n_rotation;
            i = (i+k)%nums.size();
            swap(nums[i], tmp);
            if (i == pivot && n_rotation != nums.size()) {
                ++pivot;
                i = pivot;
                tmp = nums[i];
            }
        }
    }
    
    // 8ms (87.38%) 10.2MB (15.16%) solution 1: auxiliary array
    void rotate1(vector<int>& nums, int k) {
        vector<int> rot(nums.size());
        for (int i = 0; i < nums.size(); ++ i)
            rot[(i+k)%nums.size()] = nums[i];
        swap(rot, nums);
    }
};
