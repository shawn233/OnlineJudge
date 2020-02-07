class Solution {
public:
    // 4ms solution 1
    vector<vector<int>> generateMatrix(int n) {
        vector<vector<int>> ans(n);
        for(int i = 0; i < n; ++ i)
            ans[i].assign(n, 0);
        int side = n-1;
        int i1=0, j1=0;
        int num = 1;
        vector<int> dir = {1, -1};
        while (side > 0) {
            for (int d = 0; d < 2; ++ d) {
                for (int i = 0; i < side; ++ i) {
                    ans[i1][j1] = (num++);
                    j1 += dir[d];
                }
                for (int i = 0; i < side; ++ i) {
                    ans[i1][j1] = (num++);
                    i1 += dir[d];
                }
            }
            side -= 2;
            ++ i1;
            ++ j1;
        }
        if (side == 0) ans[i1][j1] = num;
        return ans;
    }
};
