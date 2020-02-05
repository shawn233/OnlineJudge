#include <iostream>
#include <cstdio>
#define MAX 100000

using namespace std;

int main()
{
    int cols[MAX], rows[MAX], nums[MAX];
    int n, M, op, num1, num2;

    freopen("in.txt", "r", stdin);

    scanf("%d", &n);
    for (int i = 0; i < n; ++ i) {
        scanf("%d %d %d", &rows[i], &cols[i], &nums[i]);
    }

    scanf("%d", &M);

    for (int i = 0; i < M; ++ i) {
        scanf("%d %d %d", &op, &num1, &num2);
        switch(op) {
        case 0:
            for (int j = 0; j < n; ++ j) {
                if (rows[j] == num1)
                    rows[j] = num2;
                else if (rows[j] == num2)
                    rows[j] = num1;
            }
            break;
        case 1:
            for (int j = 0; j < n; ++ j) {
                if (cols[j] == num1)
                    cols[j] = num2;
                else if(cols[j] == num2)
                    cols[j] = num1;
            }
            break;
        case 2:
            for (int j = 0; j < n; ++ j)
                if (rows[j] == num1 && cols[j] == num2) {
                    printf("%d\n", nums[j]);
                    break;
                }
            break;
        default:
            printf("<error> unknown command\n");
        }
    }

    fclose(stdin);
    return 0;
}
