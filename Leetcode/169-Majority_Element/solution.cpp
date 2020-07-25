/*
 * @Author: shawn233
 * @Date: 2020-07-25 08:31:15
 * @LastEditors: shawn233
 * @LastEditTime: 2020-07-25 08:31:44
 * @Description: Leetcode 169: Majority Element
 */ 

class Solution {
public:
    // 36ms (97.34%) 19.8MB (40.71%) solution 5: randomization
    // The probability of picking the majority element is mpre than 1/2.
    // This is actually my first random-based solution in Leetcode.
    // O(inf)
    int majorityElement5(vector<int>& nums) {
        while (true) {
            int rand_ind = rand() % nums.size();
            
            int cnt = 0;
            for (int i = 0; i < nums.size(); ++ i)
                if (nums[i] == nums[rand_ind])
                    cnt += 1;
            
            if (cnt > (nums.size()/2))
                return nums[rand_ind];
        }
    }
    
    // 32ms (99.27%) 19.9MB (37.5%) solution 4: Boyer-Moore Voting Algorithm
    // This is a very clever algorithm and
    // the most concise solution for this problem.
    // O(N)
    int majorityElement(vector<int>& nums) {
        int votes = 0;
        int ans;
        for (int i = 0; i < nums.size(); ++ i) {
            if (votes == 0)
                ans = nums[i];
            votes += (nums[i] == ans)? 1 : -1;
        }
        return ans;
    }
    
    // 116ms (5.02%) 19.7MB (66.8%) solution 3: sorting
    // After sorting, the majority element locates at nums[nums.size()/2]
    // O(N logN)
    int majorityElement3(vector<int>& nums) {
        sort(nums.begin(), nums.end());
        return nums[nums.size()/2];
    }
    
    // 40ms (92.51%) 19.7MB (71.44%) solution 2: divide and conquer
    // Dividing phase: find the majority element in a sub-range
    // Conquering phase: If the left and right halves agree on the majority element,
    //   return it. Otherwise, count to get the result.
    // O(N logN)
    // I have no idea why this solution is even faster than hash map (O(N)).
    int majorityElement2(vector<int>& nums) {
        return majority_helper(nums, 0, nums.size());
    }
    
    int majority_helper(vector<int>& nums, int lo, int hi) {
        if (lo+1 == hi)
            return nums[lo];
        
        int mid = (lo + hi) / 2;
        int m1 = majority_helper(nums, lo, mid); // left half
        int m2 = majority_helper(nums, mid, hi); // right half
        
        if (m1 == m2)
            return m1;
        
        int m1_cnt = 0, m2_cnt = 0;
        for (int i = lo; i < hi; ++ i) {
            if (nums[i] == m1)
                m1_cnt += 1;
            else if (nums[i] == m2)
                m2_cnt += 1;
        }
        
        return (m1_cnt > m2_cnt)? m1 : m2;
    }
    
    // 56ms (52.62%) 19.9MB (21.22%) solution 1: scan with hash map
    // O(N)
    int majorityElement1(vector<int>& nums) {
        unordered_map<int, int> mp;
        int i;
        for (i = 0; i < nums.size(); ++ i) {
            if (!mp.count(nums[i]))
                mp.insert({nums[i], 1});
            else 
                mp[nums[i]] += 1;
        }
        
        int ret = nums[0], ret_count = 0;
        for (unordered_map<int, int>::iterator it = mp.begin(); it != mp.end(); ++ it) {
            if (it->second > ret_count) {
                ret = it->first;
                ret_count = it->second;
            }
        }
        
        return ret;
    }
};
