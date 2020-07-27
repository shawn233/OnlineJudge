/*
 * @Author: shawn233
 * @Date: 2020-07-27 17:50:24
 * @LastEditors: shawn233
 * @LastEditTime: 2020-07-27 17:50:38
 * @Description: 216. Combination Sum III
 */ 

class Solution {
public:
    // 0ms (100%) 6.2MB (100%) solution 1: dfs-based backtracing
    // This solution largely refers to my solution to problem 39. Combination Sum.
    // In a dfs-based solution, key elements are
    // - ending condition (target == 0 && path.size() == k)
    // - node expansion:
    //   - state transition (target -= i, i += 1)
    //   - completeness (while (i < 10 && i <= target) {...;++ i;})
    vector<vector<int>> combinationSum3(int k, int n) {
        vector<int> path;
        vector<vector<int>> ans;
        dfs(path, ans, n, 1, k);
        return ans;
    }
    
    void dfs(vector<int>& path, vector<vector<int>>& ans, int target, int i, int k) {
        if (target == 0 && path.size() == k) {
            ans.push_back(path);
        }
        else if (path.size() < k) {
            while (i < 10 && i <= target) {
                path.push_back(i);
                dfs(path, ans, target-i, i+1, k);
                path.pop_back();
                ++ i;
            }
        }
    }
};