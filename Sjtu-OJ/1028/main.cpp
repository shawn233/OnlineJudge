#include <iostream>
#include <cstdio>
#include <cstring>
#define MAX 100

using namespace std;

/*
 *if    1
 *then  2
 *else  3
 *begin 4
 *end   5
*/
int strToInt(const string & str) {
    if (str == "if")
        return 1;
    if (str == "then")
        return 2;
    if(str == "else")
        return 3;
    if (str == "begin")
        return 4;
    if (str == "end")
        return 5;

    cout << "[error] invalid input | " << str << endl;

    return 0;
}

int main()
{
    int n, ind, in[MAX], num;
    string tmp;

    freopen("in", "r", stdin);

    scanf("%d", &n);

    ind = 0;
    for (int i = 0; i < n; ++ i) {
        cin >> tmp;
        num = strToInt(tmp);
        switch(num) {
        case 1:
            in[ind] = 1;
            ++ ind;
            break;
        case 2:
            if(ind > 0 && in[ind-1] == 1) {
                in[ind] = 2;
                ++ ind;
            } else  {
                printf("NO\n");
                return 0;
            }
            break;
        case 3:
            if(ind > 0 && in[ind-1] == 2) {
                in[ind] = 3;
                ++ ind;
            } else {
                printf("NO\n");
                return 0;
            }
            break;
        case 4:
            if (ind > 0 && in[ind-1] == 1) {
                printf("NO\n");
                return 0;
            } else {
                in [ind] = 4;
                ++ ind;
            }
            break;
        case 5:
            while(ind > 0 && in[ind-1] != 4)
                -- ind;
            if (ind == 0) {
                printf("NO\n");
                return 0;
            }
            -- ind;
            break;
        default:
            ;//pass
        }
    }
    if (in[ind-1] == 2 || in[ind-1] == 3)
        printf("YES\n");
    else
        printf("NO\n");

    fclose(stdin);
    return 0;
}
