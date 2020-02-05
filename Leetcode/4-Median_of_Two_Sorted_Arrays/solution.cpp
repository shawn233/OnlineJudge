class Solution {
public:
    // 16ms solution 2: standard binary search solution derived from strict mathematical analysis
    // find index i in array A (size M) and index j in array B (size N) (M <= N) such that
    // (1) i + j = (M + N)/2
    // (2) max(A[i-1], B[j-1]) <= min(A[i], B[j])
    // then the answer is
    // case 1: M+N is odd, then ans = min(A[i], B[j])
    // case 2: M+N is even, then ans = (max(A[i-1], B[j-1])+min(A[i], B[j]))/2.0
    //
    // Complexity: O(log(min(M, N)))
    double findMedianSortedArrays(vector<int>& nums1, vector<int>& nums2) {
        if (nums1.size() <= nums2.size()) return findMedianSortedArrays_(nums1, nums2);
        else return findMedianSortedArrays_(nums2, nums1);
    }
    
    double findMedianSortedArrays_(vector<int>& nums1, vector<int>& nums2) {
        // make sure nums1.size() <= nums2.size()
        const int M = nums1.size(), N = nums2.size();
        int left = 0, right = M;
        int i = 0;
        int j = (M+N)/2 - i;
        while (left <= right) {
            i = (left+right)/2;
            j = (M+N)/2 - i;
            //printf("i: %d j: %d left: %d right: %d\n", i, j, left, right);
            if ((i == 0 || j == N || nums1[i-1] <= nums2[j]) &&
                (j == 0 || i == M || nums2[j-1] <= nums1[i])) 
                break;
            else if (i > 0 && nums1[i-1] > nums2[j]) {
                right = i - 1;
            } else if (j > 0 && nums2[j-1] > nums1[i]) {
                left = i + 1;
            }
        }
        
        // obtain answer
        int max_left, min_right;

        if (i == M) min_right = nums2[j];
        else if (j == N) min_right = nums1[i];
        else min_right = min(nums1[i], nums2[j]);
        
        if ((M+N)%2) {
            return (double)min_right;
        } else {
            if (i == 0) max_left = nums2[j-1];
            else if (j == 0) max_left = nums1[i-1];
            else max_left = max(nums1[i-1], nums2[j-1]);
            
            return (double)(max_left+min_right)/2.0;
        }
    }
    
    // 20ms solution 1: my original solution, about 100 lines
    // find i in nums1 such that nums1[i] can be placed in nums2
    // at exactly position j = (nums1.size()+nums2.size())/2 - i
    //
    // Complexity: O(log(M+N))
    double findMedianSortedArrays1(vector<int>& nums1, vector<int>& nums2) {
        if (nums1.size() == 0)
            return simpleMedian(nums2);
        else if (nums2.size() == 0)
            return simpleMedian(nums1);
        
        if ((nums1.size()+nums2.size())%2)
            return findOdd(nums1, nums2);
        else {
            double mid1, mid2;
            if (nums1[0] < nums2[0]) {
                vector<int> nums1_1(nums1.begin()+1, nums1.end());
                mid1 = findOdd(nums1_1, nums2);
            } else {
                vector<int> nums2_1(nums2.begin()+1, nums2.end());
                mid1 = findOdd(nums1, nums2_1);
            }
            if (nums1[nums1.size()-1] > nums2[nums2.size()-1]) {
                vector<int> nums1_2(nums1.begin(), nums1.end()-1);
                mid2 = findOdd(nums1_2, nums2);
            } else {
                vector<int> nums2_2(nums2.begin(), nums2.end()-1);
                mid2 = findOdd(nums1, nums2_2);
            }
            //printf("mid1: %f mid2: %f\n", mid1, mid2);
            return (mid1+mid2)/2;
        }
    }
    
    double findOdd(vector<int>& nums1, vector<int>& nums2) {
        if (nums1.size() == 0) return simpleMedian(nums2);
        else if (nums2.size() == 0) return simpleMedian(nums1);
        int ans = medianIndex(nums1, nums2);
        //printf("ans: %d\n", ans);
        if (ans == -1) return (double)nums2[medianIndex(nums2, nums1)];
        else return (double)nums1[ans];
    }
    
    int medianIndex(vector<int>& nums1, vector<int>& nums2) {
        // find the index of median, return -1 if not in nums1
        // preliminary: m + n is odd
        int l = 0, r = nums1.size()-1;
        int mid, pos;
        int target_pos = (nums1.size()+nums2.size())/2;
        while (l <= r) {
            mid = (l+r)/2;
            pos = target_pos - mid;
            //printf("l: %d r: %d mid: %d pos: %d\n", l, r, mid, pos);
            switch(checkPos(nums2, pos, nums1[mid])) {
                case -1:
                    r = mid-1;
                    break;
                case 0:
                    return mid;
                    break;
                case 1:
                    l = mid+1;
                    break;
                default:
                    break;
            }
        }
        return -1;
    }
    
    int checkPos(vector<int>& nums, int pos, int val) {
        // check if val fits at pos in vector nums
        // return value:
        // * -1: search towards left
        // * 0 : you got it
        // * 1 : search towards right
        if (pos < 0)
            return -1;
        else if (pos == 0) {
            if (val <= nums[0])
                return 0;
            else
                return -1;
        } else if (pos == nums.size()) {
             if (val >= nums[nums.size()-1])
                 return 0;
            else
                return 1;
        } else if (pos > nums.size()) {
            return 1;
        } else {
            if (val < nums[pos-1])
                return 1;
            else if (val > nums[pos])
                return -1;
            return 0;
        }
    }
    
    double simpleMedian(vector<int>& nums) {
        // median of only one vector
        if (nums.size()%2)
            return (double)nums[(nums.size()-1)/2];
        else {
            return (double)(nums[(nums.size()-1)/2] + 
                    nums[nums.size()/2]) / 2.0;
        }
    }
};
