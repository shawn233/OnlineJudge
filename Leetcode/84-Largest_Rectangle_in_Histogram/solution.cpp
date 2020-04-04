class Solution {
public:
    // 24ms solution 5
    // use segment tree to optimize my solution 1, which exceeded the time limit
    struct SegTree;

    int largestRectangleArea5(vector<int>& heights) {
        if (heights.empty())
            return 0;
        
        SegTree seg;
        seg.construct(heights);
        
        return largestRectangleArea5_util(heights, seg, 0, heights.size()-1);
    }
    
    int largestRectangleArea5_util(vector<int>& heights, SegTree& seg, int l, int r) {
        //printf("in  [ %d : %d ]\n", l, r);
        if (l > r)
            return -1;

        int min_ind = seg.query_min(heights, l, r);
        int ret = heights[min_ind] * (r - l + 1); // largest area of rectangles that contain the shortest bar
        //printf("mid [ %d : %d ] is %d * %d = %d\n", l, r, heights[min_ind], r-l+1, ret);
        
        ret = max(ret, largestRectangleArea5_util(heights, seg, l, min_ind-1));
        ret = max(ret, largestRectangleArea5_util(heights, seg, min_ind+1, r));
        //printf("out [ %d : %d ] with %d\n", l, r, ret);
        
        return ret;
    }
    
    struct SegTree {
        // RANGE MINIMUM INDEX QUERY
        //vector<int> tree;
        vector<int> index_tree;
        // int length; // length of the original array
        
        int get_mid(int l, int r) { return l + (r - l) / 2; }
        
        int construct_util(vector<int>& arr, int l, int r, int n) {
            // Process `arr [l : r]` at node `n`
            // Returns the index of the minimum element
            //printf("in  [ %d : %d ] at %d\n", l, r, n);
            if (l == r) {
                //tree[n] = arr[l];
                index_tree[n] = l;
            } else {
                int mid = get_mid(l, r);
                
                // save the smaller element in node n
                int ind1 = construct_util(arr, l, mid, n*2);
                int ind2 = construct_util(arr, mid+1, r, n*2+1);
                //printf("ind1 %d ind2 %d\n", ind1, ind2);
                if (arr[ind1] < arr[ind2])
                    index_tree[n] = ind1;
                else
                    index_tree[n] = ind2;
                // tree[n] = arr[index_tree[n]];
            }
            //printf("out [ %d : %d ] at %d\n", l, r, n);
            return index_tree[n];
        }
        
        int query_util(vector<int>& arr, int l, int r, int n, int tl, int tr) {
            // At node `n`: range `arr [tl : tr]`. Query `arr [l : r]`
            //   Returns the index of minimum element, its value can be 
            // retrieved from `arr[ ind ]`
            if (l <= tl && r >= tr)
                return index_tree[n];
            else if (r < tl || l > tr)
                return -1;
            else {
                int mid = get_mid(tl, tr);
                int ret = query_util(arr, l, r, n*2, tl, mid);
                int ind2 = query_util(arr, l, r, n*2+1, mid+1, tr);
                
                //printf("query [%d:%d] at [%d:%d]: arr[%d] %d, arr[%d] %d\n",
                // l, r, tl, tr, ret, arr[ret], ind2, arr[ind2]);

                if (ind2 == -1)
                    return ret;
                else if (ret == -1 || arr[ind2] < arr[ret])
                    ret = ind2;
                return ret;
            }
        }
        
        void construct(vector<int>& arr) {
            //length = arr.size();
            int height = ceil( log2( (double)arr.size() ) ) + 1;
            //printf("height: %d\n", height);
            index_tree.resize( (int)pow(2, height) );
            
            construct_util(arr, 0, arr.size()-1, 1);
        }
        
        int query_min(vector<int>& arr, int l, int r) {
            // Returns the index of the minimum element
            if (l < 0 || r >= arr.size())
                return -1;
            return query_util(arr, l, r, 1, 0, arr.size()-1);
        }
    };
    
    // 12 ms, 7.9 MB (100%) solution 4
    // divide and conquer O( N log N )
    //   The conquer phase uses two-pointers to get the largest rectangle area
    // that crosses the division point
    int largestRectangleArea4(vector<int>& heights) {
        // I'll be back in a few days (actually it's a few months)
        if (heights.empty()) return 0;
        return largestRectangleArea4_util(heights, 0, heights.size()-1);
    }
    
    int largestRectangleArea4_util(vector<int>& heights, const int l, const int r) {
        // l: sub-array left border, r: sub-array right border
        //printf("entering sub-array [ %d : %d ]\n", l, r);
        
        // terminating case
        if (l == r)
            return heights[l];
        
        int mid = (l + r) / 2;
        
        // solve two sub-problems
        int ret = largestRectangleArea4_util(heights, l, mid);
        ret = max(ret, largestRectangleArea4_util(heights, mid+1, r));
        
        // evaluate the largest rectangle across the division point
        int left = mid, right = mid+1;
        int h = min(heights[left], heights[right]);
        
        // TRICKY: must use do ... while ... to ensure the rectangle across
        // division point is checked at least once, e.g. for array [1, 1],
        // if I use while ..., then the crossing case will be skipped
        do {
            // fix the rectangle height as `h`
            // move pointers to expand the rectangle as large as possible
            //printf("[1] left %d right %d h %d\n", left, right, h);
            while (left > l && heights[left-1] >= h)
                -- left;
            while (right < r && heights[right+1] >= h)
                ++ right;
            //printf("[2] left %d right %d h %d\n", left, right, h);
            ret = max(ret, h * (right - left + 1));
            
            // change `h` to the higher boundary and repeat
            if (left != l && right != r)
                h = max(heights[left-1], heights[right+1]);
            else if (left != l)
                h = heights[left-1];
            else if (right != r)
                h = heights[right+1];
            // repeat until both pointers reach array boundaries
        } while (left != l || right != r);
        
        //printf("exiting sub-array [ %d : %d ]\n", l, r);
        return ret;
    }
    
    // 8ms solution 3
    // stack-based one-pass solution
    // the trick is to ensure that heights in the stack are monotonically increasing
    // such that for the element at the stack top i,
    // its next element in the stack is i's left boundary
    int largestRectangleArea3(vector<int>& heights) {
        //if (heights.empty()) return 0;
        stack<int> st;
        st.push(-1);
        int i=0, ans=0;
        while (i < heights.size() || st.size() > 1) {
            //cout << "i: " << i << " st.top(): " << st.top() << endl;
            if (i < heights.size() && (st.size() == 1 || heights[st.top()] <= heights[i])) {
                st.push(i++);
                //if (st.size() > 1 && heights[st.top()] == heights[i]) st.top() = (i++);
                //else st.push(i++);
            } else {
                int cur = st.top();
                st.pop();
                ans = max(ans, (i-st.top()-1)*heights[cur]);
            }
        }
        return ans;
    }
    
    // 12ms solution 2
    // The idea is that for each bar[i], find the first index to_left[i] to its left, that is shorter than bar[i],
    // and do the same for the first index to_right[i] to its right.
    // The answer then yields max_i(heights[i]*(to_right[i]-to_left[i]-1)).
    // Finding to_left and to_right only requires an overall O(N) complexity (think about how to get this)
    // with a clever trick:
    //     while (to_left[i] >= 0 && heights[to_left[i]] >= heights[i])
    //         to_left[i] = to_left[to_left[i]]; // kind of dp style
    // So totally this solution has O(N) time complexity
    // Reference: https://leetcode.com/problems/largest-rectangle-in-histogram/discuss/28902/5ms-O(n)-Java-solution-explained-(beats-96)
    int largestRectangleArea(vector<int>& heights) {
        if (heights.empty()) return 0;
        // to_left[i] represents the first index to the left of i
        // that has smaller height than heights[i]
        // i.e. to_left[i] = argmax_j(heights[j] < heights[i]) s.t. j < i
        vector<int> to_left(heights.size()); 
        // Similarly, to_right[i] = argmax_j(heights[j] < heights[i]) s.t. j > i 
        vector<int> to_right(heights.size());
        to_left[0] = -1;
        for (int i = 1; i < heights.size(); ++ i) {
            to_left[i] = i-1;
            while (to_left[i] >= 0 && heights[to_left[i]] >= heights[i])
                to_left[i] = to_left[to_left[i]];
        }
        to_right[heights.size()-1] = heights.size();
        for (int i = heights.size()-2; i >= 0; -- i) {
            to_right[i] = i+1;
            while (to_right[i] < heights.size() && heights[to_right[i]] >= heights[i])
                to_right[i] = to_right[to_right[i]];
        }
        int ans = -1;
        for (int i = 0; i < heights.size(); ++ i)
            ans = max(ans, heights[i]*(to_right[i]-to_left[i]-1));
        return ans;
    }
    
    // Time Limit Exceeded solution 1
    // divide-and-conquer: best O(NlogN), worst O(N^2)
    // so I guess this problem requires an O(N) solution
    // Remark: Actually O(NlogN) can get accepted. My problem is the exceedingly slow worst case.
    // To clarify, I read about a post about a divide-and-conquer solution to this problem,
    // which also has an O(NlogN) time complexity.
    // Reference: https://leetcode.com/problems/largest-rectangle-in-histogram/discuss/28910/Simple-Divide-and-Conquer-AC-solution-without-Segment-Tree
    // The aforementioned solution passes with 44ms time cost.
    // So I guess it outperforms my answer mainly because its worst case complexity
    // maintains O(NlogN) and does not degrade to O(N^2). The main difference lies in
    // the dividing strategy. The accepted solution simply divides the array at the middle,
    // yielding two sub-arrays with equal length, so as to guarantee the O(NlogN) runtime.
    int largestRectangleArea1(vector<int>& heights) {
        if (heights.empty()) return 0;
        return largestArea_1(heights, 0, heights.size()-1);
    }
    
    int largestArea_1(vector<int>& heights, int left, int right) {
        //cout << "left: " << left << " right: " << right << endl;
        if (left == right) return heights[left];
        int min_ind;
        for (int i = min_ind = left; i <= right; ++ i) {
            if (heights[i] <= heights[min_ind])
                min_ind = i;
        }
        //cout << "min_ind: " << min_ind << endl;
        int ret = (right-left+1)*heights[min_ind];
        if (min_ind > left)
            ret = max(ret, largestArea_1(heights, left, min_ind-1));
        if (min_ind < right)
            ret = max(ret, largestArea_1(heights, min_ind+1, right));
        return ret;
    }
};
