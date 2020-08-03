/*
 * @Author: shawn233
 * @Date: 2020-07-31 17:31:54
 * @LastEditors: shawn233
 * @LastEditTime: 2020-07-31 17:32:11
 * @Description: 287. Find the Duplicate Number
 */ 

class Solution {
public:
    // 16ms (87.64%) 11MB (90.64%) solution 5: Floyd's Tortoise and Hare
    // or Cycle Detection algorithm
    // It's just beautiful.
    // Reference: official solution Approach 3
    int findDuplicate(vector<int>& nums) {
        int fast = nums[0], slow = nums[0];
        
        // round 1: `fast` moves 2 numbers per step, `slow` moves 1.
        do {
            fast = nums[nums[fast]];
            slow = nums[slow];
        } while (fast != slow);
        
        // round 2: `fast` re-starts from nums[0]
        fast = nums[0];
        while (fast != slow) {
            fast = nums[fast];
            slow = nums[slow];
        }
        
        return fast;
    }
    
    // 32ms (24.38%) 12.7MB (12.13%) tempting solution 4: hash set
    // *VIOLATION of Restrictions: the memory usage is O(N).
    int findDuplicate4(vector<int>& nums) {
        unordered_set<int> seen;
        for (int n: nums) {
            if (seen.find(n) == seen.end())
                seen.insert(n);
            else
                return n;
        }
        return 0;
    }
    
    // 24ms (48.14%) 13.3MB (5.2%) tempting solution 3: counting
    // *VIOLATION of Restrictions: the memory usage is O(N).
    int findDuplicate3(vector<int>& nums) {
        unordered_map<int, int> mp;
        int cnt;
        for (int i = 0; i < nums.size(); ++ i)
            ++ mp[nums[i]];
        for (auto& pr: mp)
            if (pr.second > 1)
                return pr.first;
        return 0;
    }
    
    // 28ms (34.48%) 10.9MB (98.51%) tempting solution 2: sorting
    // *VIOLATION of Restrictions: the array is modified.
    // After sorting, the duplicate numbers become neighbors and thus 
    // can be easily found.
    int findDuplicate2(vector<int>& nums) {
        sort(nums.begin(), nums.end());
        for (int i = 1; i < nums.size(); ++ i)
            if (nums[i] == nums[i-1])
                return nums[i];
        return 0;
    }
    
    // Time Limit Exceeded solution 1: brute force
    int findDuplicate1(vector<int>& nums) {
        for (int i = 0; i < nums.size(); ++ i) {
            for (int j = i+1; j < nums.size(); ++ j)
                if (nums[i] == nums[j])
                    return nums[i];
        }
        return 0;
    }
};