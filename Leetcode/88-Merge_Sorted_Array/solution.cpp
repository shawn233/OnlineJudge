class Solution {
public:
    // 4ms (80%) solution 1: back-to-front traverse
    void merge(vector<int>& nums1, int m, vector<int>& nums2, int n) {
        int ind1 = m-1;
        int ind2 = n-1;
        int pos = m+n-1;
        
        while (ind1 != -1 || ind2 != -1) {
            while (ind1 != -1 && (ind2 == -1 || nums1[ind1] > nums2[ind2])) {
                nums1[pos--] = nums1[ind1--];
            }
            while (ind2 != -1 && (ind1 == -1 || nums2[ind2] >= nums1[ind1])) {
                nums1[pos--] = nums2[ind2--];
            }
        }
    }
};
