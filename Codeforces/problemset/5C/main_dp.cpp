#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#define MAX 1000005

// dp algorithm with self-implemented stack, this solution is much more elegant than the greedy one

using namespace std;

struct myStack {
    int arr[MAX];
    int ind;

    myStack() {
        ind = 0;
    }

    bool isEmpty() {
        return ind == 0;
    }

    void push(int i) {
        arr[ind++] = i;
    }

    int pop() {
        if (ind != 0) {
            return arr[--ind];
        } else
            return -1;
    }
};

typedef struct myStack mStack;

int main() {
    string s;
    cin >> s;
    int dp[MAX];
    mStack stack;
    int tmp;
    int max_len, n_max;

    memset(dp, 0, MAX*sizeof(int));

    max_len = -1;
    n_max = 0;
    for (int i = 0; i < (int)s.size(); ++ i) {
        if (s[i] == '(') {
            stack.push(i);
        } else {
            if (!stack.isEmpty()) {
                tmp = stack.pop();
                dp[i] = i - tmp + 1 + ((tmp==0)?0:dp[tmp-1]);
                //printf("i:%d tmp:%d dp[i]:%d\n", i, tmp, dp[i]);
                if (dp[i] == max_len) {
                    ++ n_max;
                }
                else if (dp[i] > max_len) {
                    max_len = dp[i];
                    n_max = 1;
                }
            }
        }
    }

    if (max_len == -1)
        printf("0 1\n");
    else
        printf("%d %d\n", max_len, n_max);

    return 0;
}