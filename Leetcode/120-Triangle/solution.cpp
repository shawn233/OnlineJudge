class Solution {
public:
    // 4ms (95%) 7.6MB (100%) solution 1: in-place dp
    int minimumTotal(vector<vector<int>>& triangle) {
        if (triangle.empty())
            return 0;
        
        for (int row = 1; row < triangle.size(); ++ row) {
            triangle[row][0] += triangle[row-1][0];
            triangle[row][row] += triangle[row-1][row-1];
            
            for (int col = 1; col < row; ++ col) {
                triangle[row][col] += min(
                                        triangle[row-1][col-1], 
                                        triangle[row-1][col]);
            }
        }
        
        int last_row = triangle.size()-1;
        int ans = triangle[last_row][0];
        
        for (int i = 1; i <= last_row; ++ i)
            ans = min(ans, triangle[last_row][i]);
        
        return ans;
    }
};
