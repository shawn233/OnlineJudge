# Hashing

## Trick 1: Simple Manual Hashing

In C/C++ a simple hash function can be implemented utilizing the **integer overflow**. For example, in problem [7D](https://codeforces.com/problemset/problem/7/D), the hash value of every substring from 0 to $i$ is required, so hash values are accumulated in the following way:

```c++
#define MAX 1000
char s[MAX];
scanf("%s", s);
int hash_val = 0;
for (int i = 0; s[i]; ++ i) {
    hash_val = hash_val * 137 + (int)s[i];
}
```

I'm not sure if the integer overflow operation is acceptable on other OJ websites, but on Codeforces, this hash function is one that is robust enough to hash collisions, because the range of hash values are very large (from INT_MIN ti INT_MAX).

**[warning]** This trick may not be accepted by some other verdict, so use it with caution.