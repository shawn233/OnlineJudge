/*
 * @Author: shawn233
 * @Date: 2020-08-03 14:20:19
 * @LastEditors: shawn233
 * @LastEditTime: 2020-08-03 14:20:35
 * @Description: 672. Bulb Switcher II
 */

class Solution {
public:
    // 0ms (100%) 5.8MB (100%) solution 1: math
    // Key observation: the first 3 bulbs determine the remaining bulbs.
    // Proof:
    // (1) Every operation modifies bulb i and bulb (i+6) at the same time.
    // (2) Operations are commutable, so m arbitary operations can be sorted.
    // (3) Assume 4 operations are performed a, b, c and d times, respectively.
    //     Say 1 represents ON and 0 represents OFF:
    //     - Light 1 = 1 + a + c + d mod 2
    //     - Light 2 = 1 + a + b     mod 2
    //     - Light 3 = 1 + a + c     mod 2
    //     - Light 4 = 1 + a + b + d mod 2 = (Light 1) + (Light 2) + (Light 3)
    //     - Light 5 = 1 + a + c     mod 2 = (Light 3)
    //     - Light 6 = 1 + a + b     mod 2 = (Light 2)
    //
    // Solution: enumeration of 16 possible operation combinations
    // (1) When n = 0, output = 1;
    // (2) When n = 1, if m = 0, output = 1; else output = 2;
    // (3) When n = 2, if m = 0, output = 1; else if m = 1, output = 3; else output = 4;
    // (4) When n >= 3, if m = 0, output = 1; else if m = 1, output = 4; 
    //                  else if m = 2, output = 7; else output = 8;
    int flipLights(int n, int m) {
        if (n == 0 || m == 0)
            return 1;
        else if (n == 1 || m == 1)
            return min(n+1, 4);
        else if (n == 2)
            return 4;
        else 
            return (m == 2)? 7: 8;
    }
};