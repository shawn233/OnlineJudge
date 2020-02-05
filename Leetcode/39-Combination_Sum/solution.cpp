class Solution {
public:
    // actually, the essence of my solution is a Depth-first search, so it can be further optimized with better terminating conditions and less if-conditions. The best solution according to this thought achieves 4ms
    
    // 8ms solution 3: strictly follow the pattern of DFS. At index i, expand the node to index [i, i+, ..., n-1]
    void solve3(int target, int i, vector<int>& c, vector<int>& prev, vector<vector<int>>& ans) {
        if (target == 0) {
            ans.push_back(prev);
            return;
        } else {
            while (i < c.size() && target-c[i] >= 0) {
                prev.push_back(c[i]);
                solve3(target-c[i], i, c, prev, ans);
                prev.pop_back();
                ++ i;
            }
        }
    }

    // 12ms solution 1: sorted array, start from the first element, using greedy search.
    // - use only one vector prev to hold the varying partial solutions during the search process
    // - use prev.erase(prev.end()+1-j, prev.end()) to restore prev back to the state when the function is invoked, as to keep prev consistent during the search process
    // - prev.end()+1-j avoids potential pointer overflow error: add 1 first before minus j; If j is subtracted first, when prev.end() = 0x0, and j = 1, prev-j gets 0xffffff..., which triggers a pointer overflow on Leetcode Judge (my local environment tolerates this overflow)
    vector<vector<int>> combinationSum(vector<int>& candidates, int target) {
        vector<vector<int>> ans = {};
        vector<int> prev = {};
        sort(candidates.begin(), candidates.end());
        solve3(target, 0, candidates, prev, ans);
        return ans;
    }

    void solve(int target, int i, vector<int>& c, vector<int>& prev, vector<vector<int>>& ans) {
        //cout << "target: " << target << " i: " << i << " prev: " << prev << endl;

        if (i < 0 || i >= c.size()) return;
        else if (target < c[i]) return;
        else {
            if ((target % c[i]) == 0) {
                ans.push_back(prev);
                for (int j = 0; j < target/c[i]; ++ j)
                    ans[ans.size()-1].push_back(c[i]);
            }
            int j;
            for (j = 0; c[i]*j < target; ++ j) {
                if (j != 0) prev.push_back(c[i]);
                solve(target - c[i]*j, i+1, c, prev, ans);
            }
            prev.erase(prev.end()+1-j, prev.end()); // restore prev
        }
    }
    
    // 16ms solution 2: better in space but worse in time comparing to solution 1
    void solve2(int target, int i, vector<int>& c, vector<int>& prev, vector<vector<int>>& ans) {
        //cout << target << " " << i << " " << prev << endl;
        if (i >= c.size() || target < 0) return;
        else if (target == 0) {
            ans.push_back(prev);
            return;
        } else {
            while (i < c.size()) {
                prev.push_back(c[i]);
                solve2(target-c[i], i, c, prev, ans);
                ++ i;
                prev.pop_back();
            }
        }
    }
};
