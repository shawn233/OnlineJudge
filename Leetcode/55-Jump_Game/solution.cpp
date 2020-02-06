class Solution {
public:
    // 8ms solution 2: optimize BFS search
    // omit unnecessary step count
    bool canJump(vector<int>& nums) {
        int max_jump = 0;
        int i = 0;
        while (max_jump < nums.size()-1 && i <= max_jump) {
            max_jump = max(max_jump, i+nums[i]);
            ++ i;
        }
        return (max_jump >= nums.size()-1);
    }

    // 12ms solution 1: standard BFS solution
    bool canJump1(vector<int>& nums) {
        int start=0, end=0;
        int new_end = 0;
        while (end < nums.size()-1) {
            for (; new_end < nums.size()-1 && start <= end; ++ start) {
                new_end = max(nums[start]+start, new_end);
            }
            if (end == new_end) break;
            end = new_end;
        }
        if (end >= nums.size()-1)
            return true;
        else
            return false;
    }
};
