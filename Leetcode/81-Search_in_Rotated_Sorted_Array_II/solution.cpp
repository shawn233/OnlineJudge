class Solution {
public:
    // 4ms solution 3
    // The best solution to my knowledge with reference to https://leetcode.com/problems/search-in-rotated-sorted-array-ii/discuss/28218/My-8ms-C++-solution-(o(logn)-on-average-o(n)-worst-case)/284690
    // improved from my solution 2, avoiding too many checkings in my loop body,
    // by replacing my else condition with a simple branch of (nums[left] == nums[mid])
    bool search(vector<int>& nums, int target) {
        if (nums.empty()) return false;
        int left = 0, right = nums.size()-1, mid;
        while (left <= right) {
            mid = (left+right)/2;
            if (nums[mid] == target) return true;
            else if (nums[left] < nums[mid]) {
                if (nums[left] <= target && target < nums[mid]) right = mid-1;
                else left = mid+1;
            } else if (nums[left] == nums[mid])
                ++ left;
            else {
                if (nums[mid] < target && target <= nums[right]) left = mid+1;
                else right = mid-1;
            }
        }
        return false;
    }
    
    // 8ms solution 2
    // one-pass binary search
    // improved from my solution 3 for problem 33
    bool search2(vector<int>& nums, int target) {
        if (nums.empty()) return false;
        int left = 0, right = nums.size()-1, mid;
        while (left <= right) {
            mid = (left+right)/2;
            if (nums[mid] == target) return true;
            else if (nums[left] < nums[mid]) {
                if (nums[left] <= target && target < nums[mid]) right = mid-1;
                else left = mid+1;
            } else if (nums[mid] < nums[right]) {
                if (nums[mid] < target && target <= nums[right]) left = mid+1;
                else right = mid-1;
            } else {
                while (left <= right && nums[left] == nums[mid]) ++ left;
                while (left <= right && nums[right] == nums[mid]) -- right;
            }
        }
        return false;
    }
    
    // 8ms solution 1
    // O(n) finds pivot, O(log n) finds target
    // search pivot in linear time
    bool search1(vector<int>& nums, int target) {
        int pivot = 0;
        for (int i = 1; i < nums.size(); ++ i) {
            if (nums[i] < nums[i-1])
                pivot = i;
        }
        int left = 0, right = nums.size()-1;
        int mid, realmid;
        while (left <= right) {
            mid = (left+right)/2;
            realmid = (pivot+mid)%nums.size();
            if (nums[realmid] == target) return true;
            else if (nums[realmid] < target) left = mid+1;
            else right = mid-1;
        }
        return false;
    }
};
