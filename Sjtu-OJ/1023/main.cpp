#include <iostream>
#include <cstdio>

using namespace std;

int main()
{
    int arr[600][600];
    int n, a, b;

    freopen("in", "r", stdin);

    scanf("%d", &n);
    for (int cnt = 0; cnt < n; ++ cnt) {
        scanf("%d %d", &a, &b);
        for (int i = 0; i < a; ++ i) {
            for (int j = 0; j < a; ++ j)
                scanf("%d", &arr[i][j]);
        }
        switch(b) {
        case 0:
            for (int i = 0; i < a; ++ i) {
                for (int j = a-1; j > 0; -- j)
                    printf("%d ", arr[i][j]);
                printf("%d\n", arr[i][0]);
            }
            break;
        case 1:
            for (int i = a-1; i >= 0; -- i) {
                for (int j = 0; j < a-1; ++ j)
                    printf("%d ", arr[i][j]);
                printf("%d\n", arr[i][a-1]);
            }
            break;
        case 2:
            for (int i = 0; i < a; ++ i) {
                for (int j = 0; j < a-1; ++ j)
                    printf("%d ", arr[j][i]);
                printf("%d\n", arr[a-1][i]);
            }
            break;
        }
    }

    fclose(stdin);

    return 0;
}
