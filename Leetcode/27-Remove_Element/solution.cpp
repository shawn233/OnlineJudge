class Solution {
public:
    // 0ms solution 1
    int removeElement(vector<int>& nums, int val) {
        int val_cnt = 0;
        for (int i = 0; i < nums.size(); ++ i) {
            if (nums[i] == val) ++ val_cnt;
            else nums[i-val_cnt] = nums[i];
        }
        return nums.size()-val_cnt;
    }
};
