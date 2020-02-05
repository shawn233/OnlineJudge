#include <iostream>
#include <cstdio>
#define MAX 1010

using namespace std;

int main () {
    int heights[MAX];
    int N, tmp;
    long long ans = 0;
    char ch;
    int left[MAX], right[MAX];

    scanf("%d", &N);
    do {
        scanf("%c", &ch);
    } while (ch == ' ' || ch == '\n');

    tmp=-1;

    for (int i = 0; i < N; ++ i) {
        scanf("%d", &heights[i]);
        scanf("%c", &ch);
    }

    for (int i = 0; i < N; ++ i) {
        tmp = max(tmp, heights[i]);
        left[i] = tmp-heights[i];
    }

    tmp = -1;

    for (int i = N-1; i >= 0; -- i) {
        tmp = max(tmp, heights[i]);
        right[i] = tmp-heights[i];
    }

    for (int i = 0; i < N; ++ i) {
        ans += min(left[i], right[i]);
    }

    cout << ans << endl;

    return 0;
}
