class Solution {
public:
    // 0ms (100.00%) 9MB (97.56%) solution 1
    // for a image with centroid at (io, jo)
    // rotate (i1, j1) by 90 degrees and get (i2, j2)
    // it holds that
    // i2 = j1
    // j2 = io + jo - i1
    // Observation: image can be divided into four parts, 
    // we can separately rotate them by 90 degrees
    void rotate(vector<vector<int>>& matrix) {
        int i_bound = matrix.size()/2;
        int j_bound = (matrix.size()+1)/2;
        int saved, i1, j1, i2, j2;
        int sum_iojo = matrix.size()-1;
        for (int i = 0; i < i_bound; ++ i)
            for (int j = 0; j < j_bound; ++ j) {
                saved = matrix[i][j];
                i1 = i;
                j1 = j;
                for (int t = 0; t < 3; ++ t) {
                    i2 = sum_iojo - j1;
                    j2 = i1;
                    matrix[i1][j1] = matrix[i2][j2];
                    i1 = i2;
                    j1 = j2;
                }
                matrix[i1][j1] = saved;
            }
    }
};
