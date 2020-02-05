class Solution {
public:
    // 16ms solution 2: two pointers
    // greedy pointer movement strategy:
    // start from the widest container
    // move the pointer of the smaller line until find a longer line
    int maxArea(vector<int>& height) {
        int left = 0, right = height.size()-1;
        int ans = -1;
        while (left < right) {
            ans = max((right-left)*min(height[left], height[right]), ans);
            if (height[left] < height[right]) {
                do {++left;} while (left < right && height[left-1] >= height[left]);
            } else {
                do {--right;} while (left < right && height[right+1] >= height[right]);
            }
        }
        return ans;
    }
    
    // Time Limit Exceeded solution 1: brute force, fix i, iterate j
    // return maximum (j-i)*min(height[i], height[j])
    int maxArea1(vector<int>& height) {
        int ans = -1;
        for (int i = 0; i < height.size(); ++ i)
            for (int j = i+1; j < height.size(); ++ j) 
                ans = max(ans, (j-i)*min(height[i], height[j]));
        return ans;
    }
};
