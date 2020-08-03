/*
 * @Author: shawn233
 * @Date: 2020-08-03 15:03:28
 * @LastEditors: shawn233
 * @LastEditTime: 2020-08-03 15:05:07
 * @Description: 1375. Bulb Switcher III
 */

class Solution {
public:
    // 144ms (81.84%) 38.5MB (65.31%) solution 1: dp
    // By step i (0 <= i <= N-1), (i+1) bulbs have been turned on.
    // If all bulbs are blue at step i, then the lighted bulbs must be 1, 2, ..., i+1.
    // To check this, we store the maximum of `light[0...i]` at step i 
    // (or the right-most lighted bulb) as `max_on`.
    // If `max_on == i+1`, then we know all bulbs are blue.
    int numTimesAllBlue(vector<int>& light) {
        int max_on = 0, ans = 0;
        for (int i = 0; i < light.size(); ++ i) {
            max_on = max(max_on, light[i]);
            if (max_on == i+1)
                ++ ans;
        }
        return ans;
    }
};