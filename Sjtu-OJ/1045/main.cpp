#include <iostream>
#include <cstdio>
#include <cstring>
#define MAX 200005

using namespace std;

int main()
{
    int sons[MAX], father[MAX];
    bool is_alive[MAX] = {false};
    int fam = 1, n, tmp1, tmp2;
    char cmd;

    freopen("in.txt", "r", stdin);

    sons[1] = 0;
    father[1] = 0;
    is_alive[1] = true;

    scanf("%d", &n);
    for (int i = 0; i < n; ++ i) {
        while (1) {
            scanf("%c", &cmd);
            if (cmd == 'B' || cmd == 'D') {
                break;
            }
        }
        if (cmd == 'B') {
            scanf("%d %d", &tmp1, &tmp2);
            sons[tmp1] += 1;
            sons[tmp2] = 0;
            is_alive[tmp2] = true;
            father[tmp2] = tmp1;
        } else if (cmd == 'D') {
            scanf("%d", &tmp1);
            fam += sons[tmp1];
            if (!is_alive[father[tmp1]])
                fam -= 1;
            else
                sons[father[tmp1]] -= 1;
            is_alive[tmp1] = false;
            printf("%d\n", fam);
        } else {
            printf("<error> unknown command-%c-\n", cmd);
        }
    }

    fclose(stdin);

    return 0;
}
