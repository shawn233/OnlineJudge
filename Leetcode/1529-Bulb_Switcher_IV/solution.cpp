/*
 * @Author: shawn233
 * @Date: 2020-08-03 15:18:38
 * @LastEditors: shawn233
 * @LastEditTime: 2020-08-03 15:18:54
 * @Description: 1529. Bulb Switcher IV
 */

class Solution {
public:
    // 48ms (65.65%) 9.4MB (75.02%) solution 1: count flips
    // Flip operations are commutable, so we try to construct `target`
    // from the beginning (`target[0]`).
    // Whenver there occurs a discontinuity, we need one flip operation.
    // P.S. for `target[0]`, if it is `1`, we need an additional flip.
    int minFlips(string target) {
        int flips = (target[0] == '0')? 0 : 1;
        for (int i = 1; i < target.size(); ++ i)
            if (target[i] != target[i-1])
                ++ flips;
        return flips;
    }
};