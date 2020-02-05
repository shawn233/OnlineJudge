#include <iostream>
#include <cstdio>
#include <cstring>
#define MAX_SET 105
#define MAX_INT 205

using namespace std;

void outputSets(int sets[MAX_SET][MAX_INT], int N) {
    for (int i = 1; i <= N; ++ i) {
        for (int j = 0; j < MAX_INT; ++ j) {
            for (int t = 0; t < sets[i][j]; ++ t)
                printf("%d ", j);
        }
        printf("\n");
    }
}

int main() {
    int sets[MAX_SET][MAX_INT];
    int set_num[MAX_SET];
    int N, M, tmp, num1, num2;
    char op;

    freopen("in.txt", "r", stdin);

    scanf("%d", &N);
    for (int i = 1; i <= N; ++ i) {
        scanf("%d", &set_num[i]);
    }

    for (int i = 1; i <= N; ++ i) {
        memset(sets[i], 0, sizeof(sets[i]));
        for (int j = 0; j < set_num[i]; ++ j) {
            scanf("%d", &tmp);
            sets[i][tmp] = 1;
        }
    }

    //outputSets(sets, N);

    scanf("%d", &M);

    for (int i = 0; i < M; ++ i) {
        do {
            scanf("%c", &op);
        } while (op == ' ' || op == '\n');
        scanf("%d %d", &num1, &num2);
        switch(op) {
        case '+':
            for (int i = 0; i < MAX_INT; ++ i)
                sets[num1][i] = max(sets[num1][i], sets[num2][i]);
            break;
        case '-':
            for (int i = 0; i < MAX_INT; ++ i) {
                if (sets[num2][i] > 0)
                    sets[num1][i] = 0;
            }
            break;
        case '*':
            for (int i = 0; i < MAX_INT; ++ i) {
                sets[num1][i] = min(sets[num1][i], sets[num2][i]);
            }
            break;
        default:
            printf("<error> unknown command\n");
        }
    }

    outputSets(sets, N);

    fclose(stdin);

    return 0;
}
