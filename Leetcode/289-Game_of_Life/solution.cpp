/*
 * @Author: shawn233
 * @Date: 2020-08-03 17:35:49
 * @LastEditors: shawn233
 * @LastEditTime: 2020-08-03 17:36:10
 * @Description: 289. Game of Life
 */

class Solution {
public:
    // 0ms (100%) 6.9MB (94.44%) solution 1: in-place
    // Use intermediate states to represent cells to be changed.
    void gameOfLife(vector<vector<int>>& board) {
        if (board.empty())
            return;
        
        int left, right, up, down, one_cnt;
        int m = board.size(), n = board[0].size();
        for (int row = 0; row < m; ++ row) {
            for (int col = 0; col < n; ++ col) {
                // find neighbors
                left = max(0, col-1);
                right = min(n-1, col+1);
                up = max(0, row-1);
                down = min(m-1, row+1);
                
                // count ones
                one_cnt = 0;
                for (int i = up; i <= down; ++ i) {
                    for (int j = left; j <= right; ++ j) {
                        if (i == row && j == col)
                            continue;
                        if (board[i][j] > 0)
                            ++ one_cnt;
                    }
                }
                
                // intermediate status:
                // * 1 -> 0: 2
                // * 0 -> 1: -1
                if (board[row][col] && (one_cnt < 2 || one_cnt > 3)) {
                    board[row][col] = 2; // 1 -> 0
                } else if (!board[row][col] && one_cnt == 3)
                    board[row][col] = -1; // 0 -> 1
            }
        }
        
        for (int row = 0; row < m; ++ row) {
            for (int col = 0; col < n; ++ col) {
                if (board[row][col] == 2)
                    board[row][col] = 0;
                else if (board[row][col] == -1)
                    board[row][col] = 1;
            }
        }
    }
};