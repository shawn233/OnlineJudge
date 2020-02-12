class Solution {
public:
    // 20ms (96.45%) 10MB (100.00%) solution 2
    // replace the visited matrix in solution to in-place markers
    bool exist(vector<vector<char>>& board, string word) {
        if (board.empty()) return false;
        for (int i = 0; i < board.size(); ++ i)
            for (int j = 0; j < board[0].size(); ++ j)
                if (dfs(board, i, j, word, 0))
                    return true;
        return false;
    }
    
    bool dfs(vector<vector<char>>& board, int i1, int j1, string& word, int str_idx) {
        if (i1 < 0 || i1 >= board.size() || j1 < 0 || j1 >= board[0].size())
            return false;
        else if (word[str_idx] != board[i1][j1])
            return false;
        else if (str_idx == word.size()-1)
            return true;
        else {
            char c = board[i1][j1];
            board[i1][j1] = '\0';
            ++ str_idx;
            bool ret = false;
            ret = ret || dfs(board, i1+1, j1, word, str_idx);
            ret = ret || dfs(board, i1-1, j1, word, str_idx);
            ret = ret || dfs(board, i1, j1+1, word, str_idx);
            ret = ret || dfs(board, i1, j1-1, word, str_idx);
            board[i1][j1] = c;
            return ret;
        }
    }
    
    // 32ms (71.33%) 11MB (67.65%) solution 1
    // an intuitive dfs solution
    // This solution can be further optimized. The visited matrix is not
    // necessary. An alternative method of making marks for visited elements
    // is to change their values to some char that is not likely to appear in 
    // the given word. For example, you may change a visited element to '\0' or ' '.
    // The optimized code is presented in solution 2
    bool exist1(vector<vector<char>>& board, string word) {
        if (board.empty()) return false;
        //else if (word.size() == 0) return true;
        int m = board.size(), n = board[0].size();
        vector<vector<bool>> visited(m, vector<bool>(n, false));
        for (int i = 0; i < m; ++ i)
            for (int j = 0; j < n; ++ j)
                if (dfs1(board, visited, i, j, word, 0))
                    return true;
        return false;
    }
    
    bool dfs1(vector<vector<char>>& board, vector<vector<bool>>& visited, int i1, int j1, string& word, int str_idx) {
        if (i1 < 0 || i1 >= board.size() || j1 < 0 || j1 >= board[0].size()) return false;
        else if (visited[i1][j1]) return false;
        else if (board[i1][j1] != word[str_idx]) return false;
        else if (str_idx == word.size()-1) return true;
        else {
            bool ret = false;
            visited[i1][j1] = true;
            ++ str_idx;
            ret = ret || dfs1(board, visited, i1+1, j1, word, str_idx);
            ret = ret || dfs1(board, visited, i1-1, j1, word, str_idx);
            ret = ret || dfs1(board, visited, i1, j1+1, word, str_idx);
            ret = ret || dfs1(board, visited, i1, j1-1, word, str_idx);
            visited[i1][j1] = false;
            return ret;
        }
    }
};
