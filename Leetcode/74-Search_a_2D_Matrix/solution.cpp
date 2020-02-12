class Solution {
public:
    // 12ms (55.81%) 9.8MB (75.76%) solution 3
    // O(M+N) now I don't understand why solution 1 and 2 take 12ms,
    // which should be the runtime of a O(M+N) solution
    // This solution is an enumerating version of solution 2
    bool searchMatrix(vector<vector<int>>& matrix, int target) {
        if (matrix.empty()) return false;
        else if (matrix[0].empty()) return false;
        int m = matrix.size(), n = matrix[0].size();
        int i = 0, j = 0;
        while (i < m && j < n) {
            if (matrix[i][j] == target) return true;
            else if (matrix[i][n-1] < target) ++ i;
            else ++ j;
        }
        return false;
    }
    
    // 12ms (55.81%) 9.8MB (87.88%) solution 2
    // O(log MN): that's why this solution takes the same time as the first one
    // divide the search to two phases
    // 1) find in which row the target may appear
    // 2) find the target along this row
    bool searchMatrix(vector<vector<int>>& matrix, int target) {
        if (matrix.empty()) return false;
        else if (matrix[0].empty()) return false;
        int left = 0, right = matrix.size()-1;
        int mid;
        while (left <= right) {
            mid = (left+right)/2;
            if (matrix[mid][0] == target) return true;
            else if (matrix[mid][0] < target) left = mid+1;
            else right = mid-1;
        }
        int row = left-1;
        if (row < 0) return false;
        left = 0;
        right = matrix[0].size()-1;
        while (left <= right) {
            mid = (left+right)/2;
            if (matrix[row][mid] == target) return true;
            else if (matrix[row][mid] < target) left = mid+1;
            else right = mid-1;
        }
        return false;
    }
    
    // 12ms (55.44%) 9.9MB (36.36%) solution 1
    // O(log MN)
    // converting a search in a 2-D matrix to a search in an 1-D array
    bool searchMatrix1(vector<vector<int>>& matrix, int target) {
        if (matrix.empty()) return false;
        int m = matrix.size(), n = matrix[0].size();
        int left = 0, right = m*n-1;
        int mid, ele_mid;
        while (left <= right) {
            mid = (left+right)/2;
            ele_mid = matrix[mid/n][mid%n];
            if (ele_mid == target) return true;
            else if (ele_mid < target) left = mid+1;
            else right = mid-1;
        }
        return false;
    }
};
