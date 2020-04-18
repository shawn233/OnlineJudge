class Solution {
public:
    // 4ms (97%) 7.4MB (100%) solution 1:
    // one-pass traversal: just skip all falls
    int maxProfit(vector<int>& prices) {
        int ans = 0;
        for (int i = 1; i < prices.size(); ++ i)
            ans += max(0, prices[i]-prices[i-1]);
        return ans;
    }
};
