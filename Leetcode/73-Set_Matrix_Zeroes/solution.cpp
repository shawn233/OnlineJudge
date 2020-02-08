class Solution {
public:
    // 44ms (94.28%) 11.5MB (81.48%) solution 3
    // O(1) space
    // This beatiful solution
    // postpones updating rows and cols by taking
    // the first row and column as flags, avoiding 
    // repeatedly setting rows and columns as in solution 2
    //
    // reference: official solution approach 3
    void setZeroes(vector<vector<int>>& matrix) {
        int m = matrix.size(), n = matrix[0].size();
        int mark_first_col = 1; // 0 indicates a mark
        for (int i = 0; i < m; ++ i)
            if (matrix[i][0] == 0) {
                mark_first_col = 0;
                break;
            }
        for (int j = 0; j < n; ++ j)
            if (matrix[0][j] == 0) {
                matrix[0][0] = 0; // use matrix[0][0] to mark the first row
                break;
            }
        for (int i = 1; i < m; ++ i)
            for (int j = 1; j < n; ++ j)
                if (matrix[i][j] == 0) {
                    matrix[i][0] = 0;
                    matrix[0][j] = 0;
                }
        for (int i = 1; i < m; ++ i)
            if (matrix[i][0] == 0)
                for (int j = 1; j < n; ++ j)
                    matrix[i][j] = 0;
        for (int j = 1; j < n; ++ j)
            if (matrix[0][j] == 0)
                for (int i = 1; i < m; ++ i)
                    matrix[i][j] = 0;
        if (matrix[0][0] == 0)
            for (int j = 1; j < n; ++ j)
                matrix[0][j] = 0;
        if (mark_first_col == 0)
            for (int i = 0; i < m; ++i)
                matrix[i][0] = 0;
    }
    
    // 48ms (71.33%) 11.4MB (100.00%) solution 2
    // O(1) space
    void setZeroes2(vector<vector<int>>& matrix) {
        int flag = (1 << 16);
        int m = matrix.size();
        int n = matrix[0].size();
        for (int i = 0; i < m; ++ i)
            for (int j = 0; j < n; ++ j)
                if (matrix[i][j] == 0)
                    matrix[i][j] = flag;
        for (int i = 0; i < m; ++ i)
            for (int j = 0; j < n; ++ j)
                if (matrix[i][j] == flag) {
                    for (int i1 = 0; i1 < m; ++ i1)
                        if (matrix[i1][j] != flag)
                            matrix[i1][j] = 0;
                    for (int j1 = 0; j1 < n; ++ j1)
                        if (matrix[i][j1] != flag)
                            matrix[i][j1] = 0;
                }
        for (int i = 0; i < m; ++ i)
            for (int j = 0; j < n; ++ j)
                if (matrix[i][j] == flag)
                    matrix[i][j] = 0;
    }
    
    // 44ms (94.28%) 11.5MB (70.37%) solution 1
    // using O(m+n) space
    void setZeroes1(vector<vector<int>>& matrix) {
        // O(m+n) space
        int m = matrix.size(), n = matrix[0].size();
        vector<int> rows(m, 0);
        vector<int> cols(n, 0);
        for (int i = 0; i < m; ++ i)
            for (int j = 0; j < n; ++ j)
                if (matrix[i][j] == 0) {
                    rows[i] = 1;
                    cols[j] = 1;
                }
        for (int i = 0; i < m; ++ i)
            if (rows[i])
                for (int j = 0; j < n; ++ j)
                    matrix[i][j] = 0;
        for (int j = 0; j < n; ++ j)
            if (cols[j])
                for (int i = 0; i < m; ++ i)
                    matrix[i][j] = 0;
    }
};
