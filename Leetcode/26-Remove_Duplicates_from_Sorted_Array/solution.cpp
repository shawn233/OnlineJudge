class Solution {
public:
    // 24ms solution: find all changes in values and move them to the front
    int removeDuplicates(vector<int>& nums) {
        if (nums.size() < 2) return nums.size();
        int pos = 1, ptr = 1, last_num = nums[nums.size()-1];
        for (; ptr < nums.size(); ++ ptr) {
            if (nums[ptr] != nums[ptr-1]) {
                nums[pos++] = nums[ptr];
                if (nums[ptr] == last_num) break;
            }
        }
        return pos;
    }
};
