class Solution {
public:
    // There is another solution better in memeory cost
    // This solution only uses O(n) memeory space
    // It's quite obvious so I'll just leave it
    
    // 4ms solution 2: a very concise version
    // I especially likes the pre-processing step dp[0][1] = 1
    // It makes the whole code so simple!
    // reference: https://leetcode.com/problems/unique-paths-ii/discuss/23248/My-C%2B%2B-Dp-solution-very-simple!
    int uniquePathsWithObstacles(vector<vector<int>>& obstacleGrid) {
        int m = obstacleGrid.size(), n = obstacleGrid[0].size();
        vector<vector<long long>> dp(m+1, vector<long long>(n+1, 0));
        dp[0][1] = 1; // so cool!
        for (int i = 1; i <= m; ++ i)
            for (int j = 1; j <= n; ++ j) {
                if (!obstacleGrid[i-1][j-1])
                    dp[i][j] = dp[i-1][j]+dp[i][j-1];
            }
        return dp[m][n];
    }
    
    // 4ms solution 1: I'm just surprised that this problem
    // requires the usage of long long matrix
    int uniquePathsWithObstacles1(vector<vector<int>>& obstacleGrid) {
        if (obstacleGrid[0][0])
            return 0;
        int m = obstacleGrid.size();
        int n = obstacleGrid[0].size();
        bool unreachable = false;
        vector<vector<long long>> grid(m, vector<long long>(n, 0));
        for (int i = 0; i < m; ++ i) {
            if (unreachable) grid[i][0] = 0;
            else if (obstacleGrid[i][0]) {
                grid[i][0] = 0;
                unreachable = true;
            } else
                grid[i][0] = 1;
        }
        unreachable = false;
        for (int j = 1; j < n; ++ j) {
            if (unreachable) grid[0][j] = 0;
            else if (obstacleGrid[0][j]) {
                grid[0][j] = 0;
                unreachable = true;
            } else
                grid[0][j] = 1;
        }
        for (int i = 1; i < m; ++ i) {
            for (int j = 1; j < n; ++ j) {
                if (obstacleGrid[i][j])
                    grid[i][j] = 0;
                else
                    grid[i][j] = grid[i-1][j]+grid[i][j-1];
            }
        }
        /*
        for (int i = 0; i < m; ++ i) {
            for (int j = 0; j < n; ++ j)
                cout << grid[i][j] << " ";
            cout << endl;
        }
        */
        return grid[m-1][n-1];
    }
};
