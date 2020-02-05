# General

In this file I will list programming tricks that do not relate to any specific algorithms. 

## Trick 1: Integer Overflow

Example problems: [1A](https://codeforces.com/problemset/problem/1/A)

The first trick is about overflows of `int` type. As we know, `int`-typed variables are stored as a 32-bit value in memory, so they are bound by maximum value `INT_MAX=0111 1111 1111 1111 1111 1111 1111 1111b=7FFFFFFFh` which equals $2^31-1$, or 2147483647. Any value larger than `INT_MAX`, if stored in an `int` variable, will overflow to a meaningless value. For example, `INT_MAX+1` overflows to -2147483648.

In problems that do not mention the upper bound of input values, we should use `long long` as variable types, to tackle possible inputs that are larger than `INT_MAX`.

## Trick 2: File IO

Example problems: [5B](https://codeforces.com/problemset/problem/5/B)

The File IO trick is about how to read characters from the standard input stream. I am used to read `stdin` with functions in C libararies, such as `cstdio`. Below I'll explain typical IO functions and provide useful samples codes.

**scanf** function supports formatted reading from stdin using the format string. When it reaches `EOF`, it returns an `int` value which equals to `EOF` defined in `cstdio`.

```c++
while (~scanf("%c", &tmp)) {
    // loop body
}

while(true) {
    if (scanf("%c", &tmp) == EOF)
        break;
   	// loop body
}
```

**fgets** function supports reading a line from a file input stream, which can be specified as `stdin`.

- fgets only returns when reading reaches a `\n` or `EOF`. 
- The return value is the string address (type `char *`) if reading is successful, otherwise the value is `NULL`.
- An important feature is that fgets appends a `\0` character to the end of what it reads, which means the `\n` is kept. In contrast, its corresponding function, `gets`, removes the terminating `\n` or `EOF`. 

```c++
while (fgets(arr, MAX, stdin) != NULL) {
    //loop body
}
```

## Trick 3: String IO

Example problem: [7D](https://codeforces.com/problemset/problem/7/D)

When the problem inputs a very long string ($5\times 10^6$ in problem 7D), some normal ways of reading input may cause a TLE (time limit exceeded), such as the `cin >> <string variable>` (TLE on test case 12), and `while(~scanf("%c", &ch))` (TLE on test case 17). A rather fast way is

```c++
#define MAX 5000005
char s[MAX];
scanf("%s", s);

for (int i = 0; s[i]; ++ i) { // a cool string loop header
    ;
}
```

