class Solution {
public:
    // 8ms solution: love its concise style!
    // with reference to my solution 2 of problem 63 unique paths ii
    int minPathSum(vector<vector<int>>& grid) {
        int m = grid.size(), n = grid[0].size();
        vector<vector<int>> dp(m+1, vector<int>(n+1, (1 << 16)));
        dp[0][1] = 0;
        for (int i = 1; i <= m; ++ i)
            for (int j = 1; j <= n; ++ j)
                dp[i][j] = min(dp[i-1][j], dp[i][j-1])+grid[i-1][j-1];
        return dp[m][n];
    }
};
