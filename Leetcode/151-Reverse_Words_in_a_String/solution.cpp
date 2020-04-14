class Solution {
public:
    // 8ms 7.7MB solution 3: in-place solution
    // shift words after reversing
    string reverseWords3(string s) {
        reverse(s.begin(), s.end());
        s.push_back(' ');
        
        int start, end, pos;
        start = 0;
        pos = 0;
        
        for (int i = 1; i < s.size(); ++ i) {
            if (s[i] != ' ' && s[i-1] == ' ')
                start = i;
            else if (s[i] == ' ' && s[i-1] != ' ') {
                end = i;
                // reverse
                reverse(s.begin()+start, s.begin()+end);
                
                // then shfit
                if (pos != 0)
                    s[pos++] = ' ';
                int dif = start - pos;
                for (int j = start; j < end; ++ j, ++pos)
                    s[pos] = s[j];
            }
        }
    
        s.resize(pos);    
        
        return s;
    }
    
    // 4ms 7.5MB solution 2: in-place solution
    // shift words while reversing
    string reverseWords(string s) {
        reverse(s.begin(), s.end());
        s.push_back(' '); // push a blank space to avoid tail checking
        
        int start, end, pos;
        start = pos = 0;
        
        for (int i = 1; i < s.size(); ++ i) {
            
            if (s[i] != ' ' && s[i-1] == ' ')
                start = i; // start of a word
            else if (s[i] == ' ' && s[i-1] != ' ') {
                end = i;   // end of a word
                // insert a blank space for the second and later words
                if (pos != 0) 
                    s[pos++] = ' ';
                
                my_reverse(s, start, end, pos);
                pos += (end-start);
            }
        }
        
        s.resize(pos);
        
        return s;
    }
    
    void my_reverse(string & s, int start, int end, int pos) {
        // shift words while reversing
        int dif = min( end - start, start - pos );
        int right;
        
        // move <dif> tail characters
        for (right = end-1; end-right <= dif; --right)
            s[pos + end - right - 1] = s[right];
        
        my_reverse_inplace(s, start, right+1);
    }
    
    void my_reverse_inplace(string & s, int start, int end) {
        if (end <= start) return;
        while ( (start != end) && (start != --end) ) {
            swap(s[start], s[end]);
            ++ start;
        }
    }
    
    // 4ms 8MB solution 1: stack-based on-pass solution
    // find word start and end positions,
    // and push them into a stack.
    string reverseWords1(string s) {
        if (s.empty()) return s;
        
        stack<int> word_st;
        
        // locate words
        if (s[0] != ' ')
            word_st.push(0);
        
        for (int i = 1; i < s.size(); ++ i) {
            if ( (s[i] == ' ' && s[i-1] != ' ') ||
                    (s[i] != ' ' && s[i-1] == ' ') )
                word_st.push(i);
        }
        
        if (s[s.size()-1] != ' ')
            word_st.push(s.size());
        
        string ret;
        while (!word_st.empty()) {
            int end_pos = word_st.top();
            word_st.pop();
            int start_pos = word_st.top();
            word_st.pop();
            
            ret.append(s, start_pos, end_pos-start_pos);
            
            if (!word_st.empty()) // don't insert for the last word
                ret.push_back(' ');
        }
        
        return ret;
    }
};
