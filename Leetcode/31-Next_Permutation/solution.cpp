class Solution {
public:
    // 8ms solution 1: search from the end, find the first decreased number,
    // and rearrange the sub-array starting from it
    void nextPermutation(vector<int>& nums) {
        if (nums.size() < 2) return;
        
        int dec_pos;
        for (dec_pos = nums.size()-2; dec_pos >= 0; -- dec_pos)
            if (nums[dec_pos] < nums[dec_pos+1]) break;
        
        // case when no greater permutation exists
        //printf("dec_pos: %d\n", dec_pos);
        if (dec_pos == -1) {
            reverse(nums.begin(), nums.end());
            return;
        }
        
        // generate next greater permutation
        int next_pos;
        reverse(nums.begin()+dec_pos+1, nums.end());
        // if dec_pos is very close to the end, then O(n) search
        //if (nums.size() - dec_pos > 7)
        next_pos = search_next(nums, dec_pos);
        /*
        else {
            for (next_pos = dec_pos+1; next_pos < nums.size(); ++ next_pos) {
                if (nums[next_pos] > nums[dec_pos]) break;
            }
        }*/
        swap(nums, dec_pos, next_pos);    
    }
    
    void swap(vector<int>& nums, int i, int j) {
        int tmp = nums[i];
        nums[i] = nums[j];
        nums[j] = tmp;
    }
    
    int search_next(vector<int>& nums, int pos) {
        // return the index of next larger number than nums[pos]
        int left = pos+1, right = nums.size()-1;
        int mid;
        while (left <= right) {
            mid = (left+right)/2;
            //printf("left: %d mid: %d right: %d\n", left, mid, right);
            if (nums[mid] <= nums[pos]) left = mid+1;
            else right = mid-1;
        }
        return left;
    }
};
