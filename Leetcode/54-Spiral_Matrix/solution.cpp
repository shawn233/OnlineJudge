class Solution {
public:
    // 0ms (100.00%) 8.5MB (100.00%) solution
    vector<int> spiralOrder(vector<vector<int>>& matrix) {
        vector<int> ans;
        if (matrix.empty()) return ans;
        int iside = matrix.size()-1;
        int jside = matrix[0].size()-1;
        vector<int> dir = {1, -1};
        int i1 = 0, j1 = 0;
        while (iside > 0 && jside > 0) {
            for (int d = 0; d < 2; ++ d) {
                for (int i = 0; i < jside; ++ i) {
                    ans.push_back(matrix[i1][j1]);
                    j1 += dir[d];
                }
                for (int i = 0; i < iside; ++ i) {
                    ans.push_back(matrix[i1][j1]);
                    i1 += dir[d];
                }
            }
            ++ i1;
            ++ j1;
            iside -= 2;
            jside -= 2;
        }
        if (iside == 0) {
            for (int i = 0; i <= jside; ++ i)
                ans.push_back(matrix[i1][j1+i]);
        } else if (jside == 0) {
            for (int i = 0; i <= iside; ++ i)
                ans.push_back(matrix[i1+i][j1]);
        }

        //cout << matrix << endl;
        return ans;
    }
};
