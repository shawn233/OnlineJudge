#include <iostream>
#include <cstdio>

using namespace std;

int main () {
    char board [3][3];
    int num_x = 0, num_o = 0;
    char x = 'X', o = '0';
    bool x_win = false, o_win = false;

    for (int i = 0; i < 3; ++ i) 
        for (int j = 0; j < 3; ++ j)
            cin >> board [i][j];
    
    // count markers
    num_x = num_o = 0; // I made a mistake here. If the initial value is 
                       // not set, results will be unreliable.
    for (int i = 0; i < 3; ++ i) {
        for (int j = 0; j < 3; ++ j) {
            num_x = (board[i][j] == x)?(num_x + 1): num_x;
            num_o = (board[i][j] == o)?(num_o + 1): num_o;
        }
    }

    if ((num_x != num_o) && (num_x - 1 != num_o)) {
        cout << "illegal" << endl;
        return 0;
    }

    for (int i = 0; i < 3; ++ i) {
        if (board[i][0] != '.' && board[i][0] == board[i][1] && board[i][1] == board[i][2]) {
            if (board[i][0] == x)
                x_win = true;
            else 
                o_win = true;
        }
    }
    
    for (int i = 0; i < 3; ++ i) {
        if (board[0][i] != '.' && board[0][i] == board[1][i] && board[1][i] == board[2][i]) {
            if (board[0][i] == x)
                x_win = true;
            else 
                o_win = true;
        }
    }

    if (board[1][1] != '.') {
        if (board[0][0] == board[1][1] && board[1][1] == board[2][2]) {
            if (board[1][1] == x)
                x_win = true;
            else 
                o_win = true;
        }
        if (board[2][0] == board[1][1] && board[1][1] == board[0][2]) {
            if (board[1][1] == x)
                x_win = true;
            else 
                o_win = true;
        }
    }

    if (!x_win && !o_win) {
        if (num_x == 5) {
            cout << "draw" << endl;
        } else if (num_x == num_o) {
            cout << "first" << endl;
        } else {
            cout << "second" << endl;
        }
        return 0;
    } else if (x_win && o_win) {
        cout << "illegal" << endl;
        return 0;
    } else {
        if (x_win && (num_x -1 == num_o)) {
            cout << "the first player won" << endl;
        } else if (o_win && (num_x == num_o)) {
            cout << "the second player won" << endl;
        } else {
            cout << "illegal" << endl;
        }
        return 0;
    }

    return 0;
}