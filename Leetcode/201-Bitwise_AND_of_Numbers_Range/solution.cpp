/*
 * @Author: shawn233
 * @Date: 2020-07-31 12:29:03
 * @LastEditors: shawn233
 * @LastEditTime: 2020-07-31 12:29:24
 * @Description: 201. Bitwise AND of Numbers Range
 */ 

class Solution {
public:
    // 12ms (66.63%) 5.8MB (99.14%) solution 3
    // An optimization of solution 2, check the same bits by shifting m and n to the right.
    int rangeBitwiseAnd(int m, int n) {
        int shift = 0;
        while (n != m) {
            n = n >> 1;
            m = m >> 1;
            ++ shift;
        }
        return n << shift;
    }
    
    // 16ms (44.85%) 5.9MB (93.1%) solution 2: find the same high-positional bits
    // For lower bits, they must have changed to 0 in the process of increasing m to n.
    int rangeBitwiseAnd2(int m, int n) {
        int ans = 0, mask = 0x40000000;
        for (; mask && (mask & m) == (mask & n); mask = (mask >> 1))
            ans = ans | (mask & n);
        return ans;
    }
    
    // 16ms (44.85%) 5.9MB (85.34%) solution 1: least to most significant bit
    // Check every bit of `m`, when a bit is 1, check if it flips to 0 within the range
    // If it does, this bit becomes 0 in the result, otherwise, this bit is 1. 
    int rangeBitwiseAnd1(int m, int n) {
        int ans = 0;
        int diff = n - m;
        int mask = 1;
        
        while ((mask >> 1) < m) {
            int inc = (mask + 1) - (mask & m);
            if (inc > diff) {
                ans = (~(mask >> 1)) & m;
                break;
            }
            mask = (mask << 1) + 1;
        }
        
        return ans;
    }
};