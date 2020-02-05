# Regular Expression

This summary discusses typical tricks in problems related to regular expressions. This file does not correspond to any tag used by Codeforces, but the tricks in this topic seem rarely compatible with problems in other topics, so I specifically summarize them here.

## Trick 1: Valid Condition of a Bracket String

Example problem: [3C](https://codeforces.com/problemset/problem/3/D)

The valid condition of a bracket string $s$ is

- The number of left and right brackets in $s$ are equal.
- In every position $i$ of $s$, the sub-bracket string $s[:i]$ has no less left (open) brackets than right (close) brackets.

These two conditions can be expressed as a piece of code.

```c++
// given bracket string s, it is valid if and only if
bool isValidBracketString(string s) {
    int cnt = 0;
    
    // enumerate the bracket string, check condition 2 for every position
    for (int i = 0; i < (int)s.size(); ++ i) {
        if (s[i] == '(') {
            ++ cnt; // an open bracket is fine
        } else if (s[i] == ')') {
            -- cnt; // a close bracket may violate condition 2, so we do some test
            if (cnt < 0) {
                return false; // violate condition 2
            }
        }
    }
    
    // if you get here, then condition 2 is satisfied, now we check condition 1
    // return (cnt == 0)?true:false;
    if (cnt == 0) {
        return true; // valid string 
    } else {
        return false; // violate condition 1
    }
}
```
