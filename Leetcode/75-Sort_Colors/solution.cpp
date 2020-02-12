class Solution {
public:
    // 0ms solution 3
    // O(N) two pointers
    // improved solution 2, having the value of i incremented after
    // swapping with left, but unchanged after swapping with right
    void sortColors(vector<int>& nums) {
        int left = 0, right = nums.size()-1;
        for (int i = 0; i <= right; ++ i) {
            if (nums[i] == 0)
                swap(nums[i], nums[left++]);
            else if (nums[i] == 2)
                // i-- to counteract the automatic increment of i,
                // keeping the value of i unchanged after swapping
                // nums[i] with nums[right]
                swap(nums[i--], nums[right--]);
        }
    }
    
    // 4ms solution 2
    // O(N) two pointers
    // a one-pass solution, easy to implement but a little hard to comprehend
    // reference: https://blog.csdn.net/mine_song/article/details/70473583
    //    Use two pointers left and right, left pointing at the first non-zero element ,
    // right pointing at the last element that is not two
    //    Use another pointer i, when it encounters a 0, swap it with left, and when it encounters a
    // 2, swap it with right
    //    This solution relies on the exact number of colors, which is three, so it can use
    // two pointers to solve it in O(N) time. And make it a even better solution than the
    // bucket sort (solution 1)
    void sortColors2(vector<int>& nums) {
        int left = 0, right = nums.size()-1;
        while (left <= right && nums[left] == 0) ++ left;
        while (left <= right && nums[right] == 2) -- right;
        int i = left;
        // note: the loop body is still not in the best format
        // The best solution will be presented in solution 3
        while (i <= right) {
            if (i < left) ++ i;
            else if (nums[i] == 1) ++ i;
            else if (nums[i] == 0) {
                // if nums[i] == 0
                // then the value of nums[left] has two cases
                // 1) 1, then ok, i could increment
                // 2) 2, not possible, because any 2 to on left side of i
                //    has already been swapped to the right
                // i.e., on the left side of i, there are only 0's and 1's
                //       but on the right side of i, there may be 0, 1, and 2
                // Therefore, i could increment if nums[i] swaps with nums[left]
                // but not if nums[i] swaps with nums[right], because nums[right]
                // may be 0 but nums[left] can't be 2
                swap(nums[i], nums[left]);
                ++ left;
            } else {
                swap(nums[i], nums[right]);
                -- right;
            }
        }
     }
    
    // 4ms solution 1
    // O(N)
    // a straight-forward two-pass solution
    // count colors in the first pass
    // and then assign colors according to the counter
    void sortColors1(vector<int>& nums) {
        vector<int> colors(3, 0);
        for (int i: nums)
            ++ colors[i];
        int ind = 0;
        for (int i = 0; i < 3; ++ i)
            for (int j = 0; j < colors[i]; ++ j) {
                nums[ind] = i;
                ++ ind;
            }
    }
};
