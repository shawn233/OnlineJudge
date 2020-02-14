class Solution {
public:
    // 12ms solution 1
    // use a counter to count the number of duplicates,
    // limiting the value of counter less than 3
    int removeDuplicates(vector<int>& nums) {
        if (nums.empty()) return 0;
        int cnt = 1, idx = 1;
        for (int i = 1; i < nums.size(); ++ i) {
            if (nums[i] != nums[i-1]) {
                cnt = 1;
                nums[idx++] = nums[i];
            } else if (cnt == 2)
                continue;
            else {
                nums[idx++] = nums[i];
                ++ cnt;
            }
        }
        return idx;
    }
};
