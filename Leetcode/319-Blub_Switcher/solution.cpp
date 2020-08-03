/*
 * @Author: shawn233
 * @Date: 2020-08-03 13:17:32
 * @LastEditors: shawn233
 * @LastEditTime: 2020-08-03 13:17:44
 * @Description: 319. Bulb Switcher
 */ 

class Solution {
public:
    // 0ms (100%) 5.8MB (97.37%) solution 2: one-line solution
    // Key observation: Bulb i is toggled on its factor-th round
    // e.g. Bulb 6 is toggled on round 1, 2, 3, and 6.
    // So only numbers who have an odd number of factors are on after the last round,
    // which are **perfect squares**.
    int bulbSwitch(int n) {
        return sqrt(n);
    }
    
    // 0ms (100%) 6.2MB (5.26%) solution 1: count perfect squares
    // After the last round, all numbers except perfect squares are off.
    // So we only need to count how many square numbers are within the range [1...n].
    int bulbSwitch1(int n) {
        int ans = 0;
        for (; ans*ans <= n; ++ans);
        return ans-1;
    }
};