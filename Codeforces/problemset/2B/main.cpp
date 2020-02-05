#include <iostream>
#include <cstdio>
#define MAX_N 1005

using namespace std;

void find_path (int path[MAX_N][MAX_N], int n) {
    int i, j, ind;
    char ans[2*MAX_N];
    i = j = n;
    ind = 2 * n;
    ans[ind --] = '\0';
    while (i != 0 || j != 0) {
        if (i == 0) {
            while (j != 0) {
                ans[ind --] = 'R';
                -- j;
            }
        } else if (j == 0) {
            while (i != 0) {
                ans[ind --] = 'D';
                -- i;
            }
        } else if (path[i-1][j] < path[i][j-1]) {
            ans[ind --] = 'D';
            -- i;
        } else {
            ans[ind --] = 'R';
            -- j;
        }
    }
    printf ("%s\n", ans);
}

int main () {
    int n, x;
    int a2[MAX_N][MAX_N]; // num of 2 in a
    int a5[MAX_N][MAX_N]; // num of 5 in a
    bool zero_flag = false;
    int zero_i, zero_j;

    cin >> n;
    for (int i = 0; i < n; ++ i) {
        for (int j = 0; j < n; ++ j) {
            scanf ("%d", &x);
            if (x == 0) {
                // TRAP HERE!!!! non-negative inputs, meaning 0's may occur
                // if 0 occurs, the loops below will not quit !!!
                if (!zero_flag) {
                    zero_i = i;
                    zero_j = j;
                }
                zero_flag = true;
                a2[i][j] = a5[i][j] = 1;
                continue;
            }
            a2[i][j] = a5[i][j] = 0;

            while ((x & 1) == 0) {
                x = (x >> 1);
                ++ a2[i][j];
            }

            while (x % 5 == 0) {
                ++ a5[i][j];
                x /= 5;
            }
        }
    }

    for (int i = 1; i < n; ++ i) {
        a2[0][i] += a2[0][i-1];
    }
    for (int i = 1; i < n; ++ i) {
        a2[i][0] += a2[i-1][0];
    }

    for (int i = 1; i < n; ++ i) {
        for (int j = 1; j < n; ++ j) {
            a2[i][j] += min (a2[i-1][j], a2[i][j-1]);
        }
    }

    for (int i = 1; i < n; ++ i) {
        a5[0][i] += a5[0][i-1];
    }
    for (int i = 1; i < n; ++ i) {
        a5[i][0] += a5[i-1][0];
    }
    for (int i = 1; i < n; ++ i) {
        for (int j = 1; j < n; ++ j) {
            a5[i][j] += min (a5[i-1][j], a5[i][j-1]);
        }
    }

    n -= 1;
    if (zero_flag && (min(a2[n][n], a5[n][n]) != 0)) {
        cout << 1 << endl;
        for (int t = 0; t < zero_j; ++ t)
            printf ("%c", 'R');
        for (int t = 1; t <= n; ++ t)
            printf ("%c", 'D');
        for (int t = zero_j+1; t <= n; ++ t) 
            printf ("%c", 'R');
        printf ("\n");
    } else {
        if (a2[n][n] < a5[n][n]) {
            cout << a2[n][n] << endl;
            find_path (a2, n);
        } else {
            cout << a5[n][n] << endl;
            find_path (a5, n);
        }
    }


    return 0;
}
