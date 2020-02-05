class Solution {
public:
    // 4ms solution 3: optimized binary search strategy, inspired by
    // optimizing function findLowerBound in problem 34
    int searchInsert(vector<int>& nums, int target) {
        int left = 0, right = nums.size()-1;
        int mid;
        while (left <= right) {
            mid = (left+right)/2;
            if (nums[mid] < target) left = mid+1;
            else right = mid-1;
        }
        return left;
    }
    
    // 8ms solution 2: O(n), so I suppose the test cases are too weak
    int searchInsert2(vector<int>& nums, int target) {
        for (int i = 0; i < nums.size(); ++ i) {
            if (nums[i] >= target)
                return i;
        }
        return nums.size();
    }
    
    // 8ms solution 1: O(logn)
    int searchInsert1(vector<int>& nums, int target) {
        int left = 0, right = nums.size()-1;
        int mid;
        while (left <= right) {
            mid = (left+right)/2;
            if (nums[mid] == target) return mid;
            else if (nums[mid] < target) left = mid+1;
            else right = mid-1;
        }
        return left;
    }
};
