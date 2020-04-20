class Solution {
public:
    // 4ms (97%) 7.8MB (100%) solution 1: three-pass solution
    // pass 1: from left to right, from_left[i] is the max profit 
    //         of one transcation, within the range [0, i]
    // pass 2: from right to left, from_right[i] is the max profit
    //         of one trascation, within the range [i, N-1]
    // pass 3: from left to right, 
    //         - one-trasaction max profit: 
    //                      max(from_left[N-1], from_right[0])
    //         - two-transaction max profit:
    //           max(from_left[i] + from_right[i+1], i=1, 2, .., N-2)
    //         - answer = max(one-trans max, two-trans max)
    // SPECIAL NOTE:
    // - actually my answer takes 12ms (19%) to finish,
    //   but with one optimization its runtime reduces to 4ms:
    //   In my third loop, I used to write
    //      ```
    //      int ans = max(from_left[N-1], from_right[0]);
    //      for (int i = 1; i < prices.size()-2; ++ i) {
    //          ans = max(ans, from_left[i] + from_right[i+1]);
    //      }
    //      ```
    //   The repeated calculation of prices.size()-2 drags down the performance.
    //   But in fact, since from_left[0] and from_right[N-1] are both 0,
    //   and day i can't be both the sell day for transaction 1 and the buy day
    //   for transaction 2 (think about why), then it's ok to write
    //          ans = max(ans, from_left[i] + from_right[i]);
    //   And now it runs much faster.
    int maxProfit(vector<int>& prices) {
        if (prices.empty())
            return 0;
        
        // let's look at two transactions from two directions
        vector<int> from_left(prices.size(), 0);
        vector<int> from_right(prices.size(), 0);
        int min_from_left, max_from_right;
        
        // calculate max_profit of the first transcation,
        // ranging from 0 to i
        min_from_left = prices[0];
        for (int i = 1; i < prices.size(); ++ i) {
            min_from_left = min(min_from_left, prices[i]);
            from_left[i] = max(from_left[i-1], prices[i] - min_from_left);
        }
        
        // calculate max_profit of the second transcation,
        // ranging from i to n-1
        max_from_right = prices[prices.size()-1];
        for (int i = prices.size()-2; i >= 0; -- i) {
            max_from_right = max(max_from_right, prices[i]);
            from_right[i] = max(from_right[i+1], max_from_right - prices[i]);
        }
        
        // calculate the final result
        int ans = 0;
        for (int i = 0; i < prices.size(); ++ i) {
            ans = max(ans, from_left[i] + from_right[i]);
        }
        
        return ans;
    }
};
