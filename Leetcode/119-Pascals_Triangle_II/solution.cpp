class Solution {
public:
    // 0ms (100%) 6.4MB (100%) solution 1
    vector<int> getRow(int rowIndex) {
        vector<int> row (rowIndex+1, 1);
        for (int i = 1; i <= rowIndex; ++ i) {
            for (int j = i-1; j > 0; -- j)
                row[j] += row[j-1];
        }
        return row;
    }
};
