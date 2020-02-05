#include <iostream>
#include <cstdio>

using namespace std;

int main()
{
    int ans[9];
    int clk[9];
    int res[9];
    int sum;

    for (int i = 0; i < 9; ++ i)
        scanf("%d", &clk[i]);

    for (ans[0] = 0; ans[0] < 4; ++ ans[0])
    for (ans[1] = 0; ans[1] < 4; ++ ans[1])
    for (ans[2] = 0; ans[2] < 4; ++ ans[2])
    for (ans[3] = 0; ans[3] < 4; ++ ans[3])
    for (ans[4] = 0; ans[4] < 4; ++ ans[4])
    for (ans[5] = 0; ans[5] < 4; ++ ans[5])
    for (ans[6] = 0; ans[6] < 4; ++ ans[6])
    for (ans[7] = 0; ans[7] < 4; ++ ans[7])
    for (ans[8] = 0; ans[8] < 4; ++ ans[8]) {
        res[0] = (clk[0]+3*(ans[0]+ans[1]+ans[3]))%12;
        res[1] = (clk[1]+3*(ans[0]+ans[1]+ans[2]+ans[4]))%12;
        res[2] = (clk[2]+3*(ans[1]+ans[2]+ans[5]))%12;
        res[3] = (clk[3]+3*(ans[0]+ans[3]+ans[4]+ans[6]))%12;
        res[4] = (clk[4]+3*(ans[0]+ans[2]+ans[4]+ans[6]+ans[8]))%12;
        res[5] = (clk[5]+3*(ans[2]+ans[4]+ans[5]+ans[8]))%12;
        res[6] = (clk[6]+3*(ans[3]+ans[6]+ans[7]))%12;
        res[7] = (clk[7]+3*(ans[4]+ans[6]+ans[7]+ans[8]))%12;
        res[8] = (clk[8]+3*(ans[5]+ans[7]+ans[8]))%12;
        sum = 0;
        for (int i = 0; i < 9; ++ i)
            sum += res[i];

        if (!sum) {
            for (int i = 0; i < 9; ++ i)
            for (int j = 0; j < ans[i]; ++ j)
                printf("%d ", i+1);
            printf("\n");
            return 0;
        }
    }

    return 1;

}
