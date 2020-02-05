class Solution {
public:
    // 0ms (100.00%) 9.1MB (88.61%) solution 2
    // optimize solution 1 with a critical observation,
    // (cropped from official solution approach 4: Two Pointers)
    // "1
    // So, we can say that if there is a larger bar at one end (say right),
    // we are assured that the water trapped would be dependant on
    // height of bar in current direction (from left to right).
    // As soon as we find the bar at other end (right) is smaller,
    // we start iterating in opposite direction (from right to left).
    // "
    // So we only need two pointers to iterate over the height array,
    // and two integer variables to hold the maximum height from the
    // left end or the right end.
    int trap(vector<int>& height) {
        if (height.empty()) return 0;
        
        int ans = 0, left = 1, right = height.size()-2;
        int left_max = height[0], right_max = height[height.size()-1];
        while (left <= right) {
            if (left_max < right_max) {
                ans += max(0, left_max-height[left]);
                left_max = max(left_max, height[left]);
                ++ left;
            } else {
                ans += max(0, right_max-height[right]);
                right_max = max(right_max, height[right]);
                -- right;
            }
        }
        return ans;
    }

    // 8ms (61.8%) 9.3MB (26.58%) solution 1
    // for each bar, evluate max left and eight edges to hold water,
    // take the smaller edge as water height, so this bar contains 
    // water of volume max(water_height-bar_height, 0)
    //
    // As the official solution calls it, this is a dynamic programming approach,
    // optimized from a brute force solution.
    int trap1(vector<int>& height) {
        if (height.empty())
            return 0;
        vector<int> left_max(height.size(), 0);
        vector<int> right_max(height.size(), 0);
        int max_height = height[0];
        for (int i = 0; i < left_max.size(); ++ i) {
            left_max[i] = max_height;
            max_height = max(max_height, height[i]);
        }
        max_height = height[height.size()-1];
        for (int i = right_max.size()-1; i >= 0; -- i) {
            right_max[i] = max_height;
            max_height = max(max_height, height[i]);
        }
        
        //cout << "height:    " << height << endl;
        //cout << "left_max:  " << left_max << endl;
        //cout << "right_max: " << right_max << endl;

        int ans = 0;
        for (int i = 1; i < height.size()-1; ++ i) {
            ans += max(0, min(left_max[i], right_max[i])-height[i]);
        }

        return ans;
    }
};
