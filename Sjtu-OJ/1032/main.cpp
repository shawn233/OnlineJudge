#include <iostream>
#include <cstdio>
#define MAX 10000

using namespace std;

int main()
{
    int m, n;
    int A[4][MAX];

    scanf("%d %d", &m, &n);
    for (int i = 0; i < MAX; ++ i)
        A[0][i] = i+1;

    for (int i = 1; i <=m; ++ i) {
        A[i][0] = A[i-1][1];
        for (int j = 1; j <MAX; ++ j) {
            A[i][j] = A[i-1][A[i][j-1]];
        }
    }

    printf("%d\n", A[m][n]);

    return 0;
}
