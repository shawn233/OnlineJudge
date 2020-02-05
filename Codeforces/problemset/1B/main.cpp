#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <ctype.h>
#define MAX 200

using namespace std;

int main () {
    int n;
    char buffer [MAX];
    int row, col;
    int j;

    cin >> n;
    for (int i = 0; i < n; ++ i) {
        cin >> buffer;
        col = 0;
        // start with chars
        for (j = 0; buffer[j] != '\0'; ++ j) {
            if (isdigit (buffer[j])) 
                break;
            col *= 26;
            col += (1 + buffer[j] - 'A');
        }
        // then numbers
        row = 0;
        for (; buffer[j] != '\0'; ++ j) {
            if (!isdigit (buffer[j]))
                break;
            row *= 10;
            row += (buffer[j] - '0');
        }
        if (buffer[j] == '\0') {
            // CR format, output RXCX format
            printf ("R%dC%d\n", row, col);
        } else if (buffer[j] == 'C') {
            // RXCX format, output CR format
            col = 0;
            for (++j; buffer[j] != '\0'; ++ j) {
                col *= 10;
                col += (buffer[j] - '0');
            }
            j = 0;
            while (col) {
                col -= 1; // this is based on the fact that alphabet system
                          // does not have counterpart for 0, it always starts from 1
                buffer[j++] = 'A' + (col % 26);
                //printf ("%d-%c ", col%26, buffer[j-1]);
                col /= 26;
            }
            buffer[j] = '\0';
            char tmp;
            for (int t = 0; t < j/2; ++ t) {
                tmp = buffer[t];
                buffer[t] = buffer[j - t - 1];
                buffer[j - t - 1] = tmp;
            }
            printf ("%s%d\n", buffer, row);
        } else {
            printf ("error\n");
        }
    }
    return 0;
}