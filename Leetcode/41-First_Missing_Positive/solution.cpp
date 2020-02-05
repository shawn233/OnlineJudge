class Solution {
public:
    // 4ms solution 1
    // note that the problem requires constant *extra* memory space, instead of constant memory space. So by using the existing memory space, we get an O(n) space
    // use tmp2 to manually implement swap function in order to decrease memory usage
    int firstMissingPositive(vector<int>& nums) {
        int j, tmp1, tmp2;
    
        //cout << "nums: " << nums << endl;

        for (int i = 0; i < nums.size(); ++ i) {
            if (nums[i] <= 0 || nums[i] > nums.size() || nums[i] == i+1)
                continue;
            j = i;
            tmp1 = nums[j];
            while (tmp1 > 0 && tmp1 <= nums.size() && tmp1 != nums[tmp1-1]) {
                //cout << "nums: " << nums << endl;
                //cout << "j: " << j << " tmp1: " << tmp1 << endl;
                j = tmp1-1;
                //swap(tmp1, nums[j]);
                tmp2 = tmp1;
                tmp1 = nums[j];
                nums[j] = tmp2;
            }
        }
        
        //cout << "after processing: " << nums << endl;

        for (int i = 0; i < nums.size(); ++ i) {
            if (nums[i] != i+1)
                return i+1;
        }
        return nums.size()+1;
    }

    void swap(int& n1, int& n2) {
        int tmp = n1;
        n1 = n2;
        n2 = tmp;
    }
};
