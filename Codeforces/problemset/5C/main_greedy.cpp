#include<iostream>
#include<cstdio>
#include<cstdlib>

using namespace std;

// greedy algorithm, the solution is very specific I have to admit

int main() {
    string s;
    cin >> s;

    int max_len = -1;
    int cnt = 0; // count difference between left and right brackets
    int length = 0; // count length of substring that is a regular bracket sequence

    // in order find max_len
    for (int i = 0; i < (int)s.size(); ++ i) {
        ++ length;
        if (s[i] == '(') {
            ++ cnt;
        } else if (s[i] == ')') {
            -- cnt;
            if (cnt == 0) {
                max_len = max(max_len, length);
            } else if (cnt < 0) {
                cnt = 0;
                length = 0;
            }
        }
    }

    // in reversing order find max_len
    length = 0;
    cnt = 0;
    for (int i = (int)s.size()-1; i >= 0; -- i) {
        ++ length;
        if (s[i] == ')') {
            ++ cnt;
        } else if (s[i] == '(') {
            -- cnt;
            if (cnt == 0) {
                max_len = max(max_len, length);
            } else if (cnt < 0) {
                cnt = 0;
                length = 0;
            }
        }
    }

    if (max_len == -1) {
        printf("0 1\n");
        return 0;
    }

    //printf("max_len:%d\n", max_len);

    // now find n_max
    int n_max = 0;
    cnt = 0;
    length = 0;
    bool * flag = new bool [(int)s.size()+10]; // I hate ugly implementations
    for (int i = 0; i < (int)s.size(); ++ i) flag[i] = false;
    for (int i = 0; i < (int)s.size(); ++ i) {
        ++ length;
        if (s[i] == '(')
            ++ cnt;
        else {
            -- cnt;
            if (cnt == 0 and length == max_len and !flag[i]) {
                //printf("start:%d\tend:%d\n", i, i-max_len+1);
                flag[i] = flag[i-max_len+1] = true;
                ++ n_max;
                length = cnt = 0;
            } else if (cnt < 0) {
                cnt = length = 0;
            }
        }
    }
    length = cnt = 0;
    for (int i = (int)s.size()-1; i >= 0; -- i) {
        ++ length;
        if (s[i] == ')')
            ++ cnt;
        else {
            -- cnt;
            if (cnt == 0 and length == max_len and !flag[i]) {
                flag[i] = flag[i+max_len-1] = true;
                //printf("start:%d\tend:%d\n", i, i+max_len-1);
                ++ n_max;
                length = cnt = 0;
            } else if (cnt < 0) {
                cnt = length = 0;
            }
        }
    }

    printf("%d %d\n", max_len, n_max);

    return 0;
}