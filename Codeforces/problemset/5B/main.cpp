#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#define MAX 1010

using namespace std;

void print_chars(char ch, int n_space) {
    for (int i = 0; i < n_space; ++ i)
        printf("%c", ch);
}

int main() {
    char text[MAX][MAX];
    int ind = 0;
    int max_len = -1;

    //freopen("in.txt", "r", stdin);

    while (fgets(text[ind], MAX, stdin) != NULL) {
        text[ind][strlen(text[ind]) - 1] = '\0'; 
        max_len = max(max_len, (int)strlen(text[ind]));
        ++ ind;
    }

    int left_close = 1; // left_close is 1 when imperfect line should be aligned closed to left edge
    int length, n_space;
    
    print_chars('*', max_len + 2);
    printf("\n");
    for (int i = 0; i < ind; ++ i) {
        printf("*");
        length = strlen(text[i]);
        if (length % 2 != max_len % 2) {
            // imperfect line
            n_space = (max_len-length) / 2;
            if (left_close) {
                left_close = 0;
            } else {
                left_close = 1;
                n_space += 1;
            }
            print_chars(' ', n_space);
            printf("%s", text[i]);
            print_chars(' ', max_len-length-n_space);
        } else {
            // perfect line
            n_space = (max_len-length) / 2;
            print_chars(' ', n_space);
            printf("%s", text[i]);
            print_chars(' ', n_space);
        }
        printf("*\n");
    }
    print_chars('*', max_len + 2);
    printf("\n");

    //fclose(stdin);

    return 0;
}