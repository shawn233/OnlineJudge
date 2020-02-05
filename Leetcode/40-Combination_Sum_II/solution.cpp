class Solution {
public:
    // 8ms solution 1: almost the same as problem 39 Combination Sum DFS solution.
    // The additional trick for this problem is to 
    // avoid expanding a node with repeated partial solution vector
    // (avoid passing prev vectors with the same content).
    // By doing that we have unqiue partial solutions to guarantee that 
    // all repeated searches are eliminated.
    vector<vector<int>> combinationSum2(vector<int>& candidates, int target) {
        sort(candidates.begin(), candidates.end());        
        vector<vector<int>> ans = {};
        vector<int> prev = {};
        dfs(target, 0, candidates, prev, ans);
        return ans;
    }

    void dfs(int target, int i, vector<int>& c, vector<int>& prev, vector<vector<int>>& ans) {
        if (target == 0) {
            ans.push_back(prev);
            return;
        } else {
            for (int j = i; j < c.size() && target-c[j] >= 0; ++ j) {
                if (j != i && c[j] == c[j-1]) continue; // crucial trick
                prev.push_back(c[j]);
                dfs(target-c[j], j+1, c, prev, ans);
                prev.pop_back();
            }
        }
    }
};
