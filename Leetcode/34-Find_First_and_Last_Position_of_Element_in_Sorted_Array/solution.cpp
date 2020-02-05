class Solution {
public:
    // 4ms solution 3: optimize findLowerBound function, using a better search strategy
    // I suggest remembering this implementation of finding lower boundary
    vector<int> searchRange(vector<int> &nums, int target) {
        int left = findLowerBound(nums, target);
        int right = findLowerBound(nums, target+1) - 1;
        if (left < nums.size() && nums[left] == target)
            return {left, right};
        else
            return {-1, -1};
    }
    
    int findLowerBound(vector<int>& nums, int target) {
        int left = 0, right = nums.size()-1;
        int mid = 0;
        
        while (left <= right) {
            mid = (left+right)/2;
            if (nums[mid] < target) left = mid+1;
            else right = mid-1;
        }
        return left;
    }
    
    // 8ms solution 2: two rounds of searching lower bound
    vector<int> searchRange2(vector<int> &nums, int target) {
        vector<int> ans = {-1, -1};
        if (nums.empty()) return ans;
        
        ans[0] = findLowerBound1(nums, target);
        ans[1] = findLowerBound1(nums, target+1) - 1;
        if (ans[0] > ans[1]) {
            ans[0] = -1;
            ans[1] = -1;
        }
        
        return ans;
    }
    
    int findLowerBound1(vector<int>& nums, int target) {
        int left = 0, right = nums.size()-1;
        int mid = 0;
        
        while (left+1 < right) {
            mid = (left+right)/2;
            if (nums[mid] < target) left = mid;
            else right = mid-1;
        }
        //printf("left: %d right: %d\n", left, right);
        if (nums[right] < target)
            return right+1;
        else if (nums[left] < target)
            return left+1;
        else
            return left;
    }
    
    // 8ms solution 1: three rounds of binary search, locate lower and upper bound respectively
    vector<int> searchRange1(vector<int>& nums, int target) {
        if (nums.size() == 0) return {-1, -1};
        
        int left = 0, right = nums.size()-1;
        int mid, pivot = 0;
        
        // find any target
        while (left < right) {
            mid = (left+right)/2;
            if (nums[mid] == target) {
                pivot = mid;
                break;
            } else if (nums[mid] < target)
                left = mid+1;
            else right = mid-1;
        }
        
        //printf("left: %d right: %d mid: %d\n", left, right, mid);
        
        if (nums[pivot] != target) {
            if (left > right || nums[left] != target)
                return {-1, -1};
            else
                pivot = left;
        }
        
        vector<int> ans;
        
        // find left boundary
        if (pivot == 0)
            ans.push_back(0);
        else {
            left = 0;
            right = pivot-1;
            while (left+1 < right) {
                mid = (left+right)/2;
                if (nums[mid] == target) right = mid-1;
                else left = mid;
            }
            if (nums[right] != target)
                ans.push_back(right+1);
            else if (nums[left] != target)
                ans.push_back(left+1);
            else
                ans.push_back(0);
        }
        
        //printf("mid: %d ans[0]: %d\n", mid, ans[0]);
        
        // find right boundary
        if (pivot == nums.size()-1)
            ans.push_back(nums.size()-1);
        else {
            left = pivot+1;
            right = nums.size()-1;
            while (left+1 < right) {
                mid = (left+right)/2;
                if (nums[mid] == target) left = mid+1;
                else right = mid;
            }
            if (nums[left] != target)
                ans.push_back(left-1);
            else if (nums[right] != target)
                ans.push_back(right-1);
            else
                ans.push_back(nums.size()-1);
        }
            
        return ans;
    }
};
