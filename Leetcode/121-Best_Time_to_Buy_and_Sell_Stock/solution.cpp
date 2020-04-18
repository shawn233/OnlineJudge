class Solution {
public:
    // 4ms (97%) 7.3MB (100%) solution 1: dp-based one-pass traversal 
    int maxProfit(vector<int>& prices) {
        int ans = 0;
        int buy_price = (1 << 16);
        for (int i = 0; i < prices.size(); ++ i) {
            if (prices[i] < buy_price)
                buy_price = prices[i];
            else
                ans = max(ans, prices[i]-buy_price);
        }
        return ans;
    }
};
