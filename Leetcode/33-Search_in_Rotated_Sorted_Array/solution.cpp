class Solution {
public:
    // 4ms solution 3
    // This solution runs binary search in one pass, 
    // avoiding the need to locate pivot element
    // Reference: https://leetcode.com/problems/search-in-rotated-sorted-array/discuss/14436/Revised-Binary-Search
    int search(vector<int>& nums, int target) {
        if (nums.empty()) return -1;
        int left = 0, right = nums.size()-1, mid;
        while (left <= right) {
            mid = (left+right)/2;
            if (nums[mid] == target) return mid;
            // must use <= in the condition to deal with the case
            // when left == mid, i.e., left+1 == right. 
            // If we use <, then when left == mid,
            // we will get that [nums[left], nums[right]] is monotonically
            // increasing, which is clearly wrong in most cases
            else if (nums[left] <= nums[mid]) {
                if (nums[left] <= target && target < nums[mid])
                    right = mid-1;
                else
                    left = mid+1;
            } else {
                if (nums[mid] < target && target <= nums[right])
                    left = mid+1;
                else
                    right = mid-1;
            }
        }
        return -1;
    }
    
    // 4ms solution 2: the same with my 2-year-ago implemention
    // for detailed analysis please see my note before solution 1 
    int search2(vector<int>& nums, int target) {
        if (nums.size() == 0)
            return -1;

        // find pivot
        int pivot, left=0, right=nums.size()-1, mid, realmid;
        if (nums[0] < nums[nums.size()-1])
            pivot = 0;
        else {
            while (left < right) {
                mid = (left+right)/2;
                if (mid > 0 && nums[mid] < nums[mid-1]) {
                    left = mid;
                    break;
                } else if (nums[mid] <= nums[nums.size()-1]) right = mid-1;
                else if (nums[mid] >= nums[0]) left = mid+1;
            }
            pivot = left;
        }
        
        left = 0;
        right = nums.size()-1;
        while (left < right) {
            mid = (left + right)/2;
            realmid = (pivot+mid)%nums.size();
            if (nums[realmid] == target) return realmid;
            else if (nums[realmid] < target) left = mid+1;
            else right = mid-1;
        }
        realmid = (pivot+left)%nums.size();
        if (nums[realmid] == target)
            return realmid;
        else
            return -1;
    }
    
    // 4ms solution 1: this problem is so fucking tricky
    // I have got 7 fails before an AC
    // The train of thought is that you first locate the pivot, 
    // or the sorted array's beginning, and then you follow a common 
    // binary search routine but with extra caution about the range border
    // because the while loop uses left != right as loop condition.
    // For example, when mid == left, and nums[mid] > target, it should be illegal
    // to set right = mid - 1
    //
    // I happened to review my solution written two years ago,
    // I had used a very strange index conversion strategy to bypass 
    // the range border check.
    // Specifically, my border variables left and right are treated as if
    // the array is not rotated, so that left should always be less than right
    // but how to fill the index gap caused by rotation?
    // I re-calculated every index actually used to access elements in the rotated array 
    // by defining an index conversion routine: new_idx = (old_idx + pivot_idx) % array_length
    int search1(vector<int>& nums, int target) {
        if (nums.size() == 0)
            return -1;
        
        // find pivot
        int pivot, left=0, right=nums.size()-1, mid;
        if (nums[0] < nums[nums.size()-1])
            pivot = 0;
        else {
            while (left < right) {
                mid = (left+right)/2;
                if (mid > 0 && nums[mid] < nums[mid-1]) {
                    left = mid;
                    break;
                } else if (nums[mid] <= nums[nums.size()-1]) right = mid-1;
                else if (nums[mid] >= nums[0]) left = mid+1;
            }
            pivot = left;
        }
        //printf("pivot: %d\n", pivot);
        
        // find target
        int len = nums.size();
        left = pivot;
        right = (pivot+len-1)%len;
        while (left != right) {
            if (left > right) 
                mid = ((left+right+len)/2)%len;
            else
                mid = (left+right)/2;
            //printf("left: %d right: %d mid: %d\n", left, right, mid);
            if (nums[mid] == target)
                return mid;
            else if (nums[mid] < target) {
                if (mid == right) break;
                left = (mid+1)%len;
            } else {
                if (mid == left) break;
                right = (mid+len-1)%len;
            }
        }
        if (nums[left] == target)
            return left;
        else
            return -1;
    }
};
