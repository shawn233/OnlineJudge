class Solution {
public:
    // 0ms solution 1
    vector<vector<int>> generate(int numRows) {
        if (numRows == 0)
            return {};
        vector<vector<int>> triangle = {{1}};
        for (int i = 1; i < numRows; ++ i) {
            triangle.push_back(triangle[i-1]);
            triangle[i].push_back(1);
            for (int j = 1; j < i; ++ j)
                triangle[i][j] += triangle[i-1][j-1];
        }
        
        return triangle;
    }
};
