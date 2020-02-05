#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>

using namespace std;

int main() {
    //char chess[8][8];
    char ch;
    int N = 8;
    int rows[8], cols[8];

    memset(rows, 0, sizeof(rows));
    memset(cols, 0, sizeof(cols));

    for (int i = 0; i < N; ++ i) {
        for (int j = 0; j < N; ++ j) {
            scanf("%c", &ch);
            if (ch == 'B') {
                ++ rows[i];
                ++ cols[j];
            }
        }
        getchar();
    }

    int ans = 0;
    for (int i = 0; i < N; ++ i) {
        if (rows[i] == N) ++ ans;
    }
    if (ans != N) {
        for (int j = 0; j < N; ++ j) {
            if (cols[j] == N) ++ ans;
        }
    }
    printf("%d\n", ans);

    return 0;
}