class Solution {
public:
    // 20ms (95%) 8.5MB (100%) solution 2: dp
    //
    // Keep three vectors, all of which have a fixed length of n_col.
    // - height[col]: at column `col`, the number of consecutive '1's **upwards**
    // - left[col]: at column `col`, the index of the first column to its left
    //              whose `height` is less than `height[col]`, i.e.
    //              the first column to its left such that:
    //                      `height[left[col]]` < `height[col]`
    // - right[col]: similar to left[col], the index of the first column to its right
    //              such that:
    //                      `height[right[col]]` < `height[col]`
    //
    // For each `row`,
    // we update `left`, `right`, and `height`,
    // DP criterion:
    //     if matrix[row][col] is '1':
    //     - left[col] = max( left boundary at row `row`, left boundary at row `row-1` ) 
    //     - right[col] = min( right boundary at row `row`, right boundary at row `row-1` )
    //     - height[col] increases by 1
    // 
    // So for those cells that are '1', we have:
    //          `max_area` = `max( max_area, (right[col] - left[col] - 1) * height[col] )`
    //
    // This solution is inspired from:
    // https://leetcode.com/problems/maximal-rectangle/discuss/29054/Share-my-DP-solution
    //
    // Actually I think the dp solution is quite similar to my solution 1, which is based on
    // maximum rectangles in histogram (problem 84). It's just this solution uses dp to avoid
    // calculating `left` and `right` from scratch.
    //
    int maximalRectangle(vector<vector<char>>& matrix) {
        if (matrix.empty() || matrix[0].empty())
            return 0;
        
        int max_area = 0;
        int n_row = matrix.size();
        int n_col = matrix[0].size();
        vector<int> left(n_col, -1);
        vector<int> right(n_col, n_col);
        vector<int> height(n_col, 0);
        
        for (int row = 0; row < n_row; ++ row) {
            // from left -> right: update <left> and <height>
            height[0] = (matrix[row][0] == '1')?height[0]+1:0;
            int to_left = -1;
            
            for (int col = 1; col < n_col; ++ col) {
                
                if (matrix[row][col] == '1') {
                    ++ height[col];
                    
                    if (matrix[row][col-1] == '0') {
                        left[col] = to_left = col-1;
                    } else {
                        left[col] = max(left[col], to_left);
                    }
                } else {
                    left[col] = -1;
                    height[col] = 0;
                }
            }
            
            // from right -> left: update <right> and <max_area>
            int to_right = n_col;
            
            for (int col = n_col-1; col >= 0; -- col) {
                if (matrix[row][col] == '1') {
                    if (col == n_col-1) {
                        ; // right[n_col-1] = n_col;
                    } else if (matrix[row][col+1] == '0') {
                        right[col] = to_right = col+1;
                    } else {
                        right[col] = min(right[col], to_right);
                    }
                    
                    //printf(
                    //    "matrix[%d][%d] left: %d right: %d height: %d\n", 
                    //    row, col, left[col], right[col], height[col]);
                    
                    max_area = max(max_area, (right[col] - left[col] - 1) * height[col]);
                } else {
                    right[col] = n_col;
                }
            }
        }
        
        return max_area;
    }
    
    // 32ms (35%) 8.3MB (100%) solution 1: extend the solution of problem 84
    //
    // Iterate over rows. For each row, maintain an array of heights:
    // - if the j-th element is '1', then increase heights[j] by 1;
    // - otherwise the element must be '0', then reset heights[j] to 0.
    // In another word, if we look into this rectangle row by row, it becomes
    // finding the maximum rectangle in a histogram. So we can apply the solution
    // of problem 84 to finish up. Here I use the stack-based one-pass solution.
    // The overall time complexity should be O(N ^ 2).
    int maximalRectangle1(vector<vector<char>>& matrix) {
        if (matrix.empty() || matrix[0].empty())
            return 0;
        
        vector<int> heights(matrix[0].size(), 0);
        stack<int> st;
        int max_area = -1;
        int bar;
        st.push(-1); // flag bit
        
        for (int row = 0; row < matrix.size(); ++ row) {
            for (int col = 0; col < matrix[0].size(); ++ col) {
                if (matrix[row][col] == '0')
                    heights[col] = 0;
                else
                    ++ heights[col];
            }
            
            for (int i = 0; i < heights.size(); ++ i) {
                if (st.size() == 1 || heights[st.top()] <= heights[i])
                    st.push(i);
                else {
                    while (st.size() > 1 && heights[st.top()] > heights[i]) {
                        bar = heights[st.top()];
                        st.pop();
                        max_area = max( max_area, bar * ( i - st.top() - 1 ) );
                    }
                    st.push(i);
                }
            }
            
            while (st.size() > 1) {
                bar = heights[st.top()];
                while (st.size() > 1 && heights[st.top()] == bar) 
                    st.pop();
                max_area = max( max_area, bar * ( (int)heights.size() - st.top() - 1 ) );
            }
        }
        
        return max_area;
    }
};
