#include <iostream>
#include <cstdio>
#define ROWMAX 3000
#define COLMAX 200

using namespace std;

class Text {
private:
    char text[COLMAX][ROWMAX];
    int row_length[COLMAX], current_row;

    void outputrow(int row) const;

public:
    Text():current_row(0) {}
    ~Text() {}

    void getrow(int row, char start_char);
    void listrows(int n1, int n2) const;
    void insert(int row, int j, char * str, int n);
    void remove(int row, int j, int num);
    void outputall() const;
    void showstatus() const {
        cout << "----" << endl;
        for (int i = 0; i < current_row; ++ i) {
            cout << "row " << i << " : " << row_length[i] << endl;
        }
        cout << "----" << endl;
    }

    bool checkLastRow(); //specificly defined for this exercise, delete last line if it is ******
};

void Text::getrow(int row, char start_char) {
    if (row < 0 || row > current_row) {
        printf("[error] getrow out of bound with index %d\n", row);
        return;
    }
    if (row == current_row)
        ++ current_row; //add a new row

    char tmp;

    row_length[row] = 1;
    text[row][0] = start_char; //initialize with a start char
    while (1) {
        scanf("%c", &tmp);
        if (tmp == '\n')
            break;
        text[row][row_length[row]] = tmp;
        ++ row_length[row];
    }
}

void Text::listrows(int n1, int n2) const {
    if (n1 > n2 || n1 < 0  || n2 >= current_row) {
        printf("Error!\n");
        return;
    }
    for (int i = n1; i <= n2; ++ i)
        outputrow(i);
}

void Text::insert(int row, int j, char * str, int n) {
    if ((row < 0 || row >= current_row) || (j < 0 || j > row_length[row])) {
        printf("Error!\n");
        return;
    }
    for (int i = row_length[row] - 1; i >= j; -- i)
        text[row][i+n] = text[row][i];
    for (int i = 0; i < n; ++ i)
        text[row][i+j] = str[i];
    row_length[row] += n;
}

void Text::remove(int row, int j, int num) {
    if ((row < 0 || row >= current_row) || (j < 0 || j >= row_length[row]) || (num < 0 || j + num > row_length[row])) {
        printf("Error!\n");
        return;
    }
    if (j + num != row_length[row]) {
        int cnt = row_length[row] - num - j + 1;
        for (int i = 0; i < cnt; ++ i)
            text[row][i+j] = text[row][i+j+num];
    }
    row_length[row] -= num;
}

void Text::outputall() const {
    for (int i = 0; i < current_row; ++ i)
        outputrow(i);
}

void Text::outputrow(int row) const {
    //because the validity is already made sure in function listrows,
    //so this function omits the argument check step
    for (int i = 0; i < row_length[row]; ++ i)
        printf("%c", text[row][i]);
    printf("\n");
}

bool Text::checkLastRow() {
    //check for ******
    int row = current_row - 1;
    if (row_length[row] != 6)
        return false;
    for (int i = 0; i < 6; ++ i)
        if (text[row][i] != '*')
            return false;
    current_row -= 1;
    return true;
}

void getchars(int n) {
    for (int i = 0; i < n; ++ i)
        cin.get();
}

int main()
{
    freopen("in.txt", "r", stdin);
    Text tx;

    char ch, cmd;
    char ins[105];
    bool stay;
    int n1, n2, ind;

    for (int i = 0; ; ++ i) {
        scanf("%c", &ch);
        if (ch == '*') {
            break;
        }
        else
            tx.getrow(i, ch);
    }

    //tx.outputall();

    stay = true;
    while (stay) {
        do {
            scanf("%c", &cmd);
        } while (cmd == '\n' || cmd == '*' || cmd == ' ');
        switch(cmd) {
        case 'l':
            getchars(4); //4: ist_
            scanf("%d %d", &n1, &n2);
            tx.listrows(n1-1, n2-1);
            break;
        case 'i':
            getchars(3); //3: ns_
            scanf("%d %d", &n1, &n2);
            cin.get();
            for (ind = 0; ; ++ ind) {
                scanf("%c", &ch);
                if (ch == '\n')
                    break;
                ins[ind] = ch;
            }
            //cout << "ind -- " << ind << endl;
            tx.insert(n1-1, n2-1, ins, ind);
            break;
        case 'd':
            getchars(3); //3: el_
            scanf("%d %d %d", &n1, &n2, &ind);
            tx.remove(n1-1, n2-1, ind);
            break;
        case 'q':
            stay = false;
            tx.outputall();
            break;
        default:
            printf("[error] Unknown command [%c]", cmd);
        }
    }

    fclose(stdin);
    return 0;
}
