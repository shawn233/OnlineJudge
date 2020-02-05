#include<iostream>
#include<cstdio>
#include<cstdlib>
#include <cstring>
#define MAX 1000010

using namespace std;

void visualize(int * r, int * l, int * c, int * height, int n) {
    cout << "h: ";
    for (int i = 0; i < (n+1); ++ i) cout << height[i] << " ";
    cout << endl;

    cout << "r: ";
    for (int i = 0; i < (n+1); ++ i) cout << r[i] << " ";
    cout << endl;

    cout << "c: ";
    for (int i = 0; i < (n+1); ++ i) cout << c[i] << " ";
    cout << endl;

    cout << "l: ";
    for (int i = 0; i < (n+1); ++ i) cout << l[i] << " ";
    cout << endl;
}

int main() {
    int n;
    int input_height[MAX];
    int height[MAX];

    //freopen("in.txt", "r", stdin);

    cin >> n;
    for (int i = 0;i < n; ++ i) scanf("%d", &input_height[i]);

    // sequence of height where the maximal height goes first
    int max_ind, max_height;
    max_ind = max_height = -1;
    for (int i = 0; i < n; ++ i) {
        if (input_height[i] > max_height) {
            max_height = input_height[i];
            max_ind = i;
        }
    }

    for (int i = 0; i < n; ++ i) height[i] = input_height[(max_ind+i)%n];
    height[n] = max_height;

    // the key idea is for a pair of visible hills, we consider the lower one
    // (or the one with the lower index) as responsible for adding this pair to the answer
    // with this specification, we utilize three arrays to find the answer
    int r[MAX], l[MAX], c[MAX]; // three arrays that represent different information
    // check out https://codeforces.com/blog/entry/213 for detailed description
    // say x is a hill
    // r[x] is the first hill to the right of the x, which is strictly higher than x
    // l[x] is the ...               left ...
    // c[x] is all hills that are as high as x and are located between x and dr[x] (corresponding to the specification above)

    // key code piece: estimate r and c under O(n) bound: refer to https://codeforces.com/blog/entry/213
    memset(c, 0, sizeof(int)*(n+1));
    memset(r, 0, sizeof(int)*(n+1));
    for (int i = n-1; i >= 0; -- i) {
        // find r[i] and c[i]
        r[i] = i+1;
        while (r[i] < n && height[i] > height[r[i]]) r[i] = r[r[i]];
        if (r[i] < n && height[i] == height[r[i]]) {
            c[i] = c[r[i]] + 1;
            r[i] = r[r[i]];
        }
    }

    // O(n) to estimate l
    memset(l, 0, sizeof(int)*(n+1));
    for (int i = 1; i <= n; ++ i) {
        l[i] = i-1;
        while(l[i] > 0 && height[i] >= height[l[i]]) l[i] = l[l[i]];
    }

    //visualize(r, l, c, height, n);

    int ans = 0;
    for (int i = 0; i <= n; ++ i) {
        ans += c[i];
        if (i != 0 && i != n) {
            if (r[i] == n && l[i] == 0) ans += 1;
            else ans += 2;
        }
    }

    printf("%d\n", ans);

    //fclose(stdin);

    return 0;
}