#include <iostream>
#include <cstdio>
#include <cstring>
#include <queue>
#define MAX 1000002

using namespace std;

int main()
{
    int left[MAX], right[MAX];
    int n, ind;
    queue<int> q;

    freopen("in.txt", "r", stdin);

    memset(left, 0, sizeof(left));
    memset(right, 0, sizeof(right));

    scanf("%d", &n);
    for (int i = 1; i < n; ++ i) {
        scanf("%d", &ind);
        if (left[ind] == 0) {
            left[ind] = i;
        } else {
            right[ind] = i;
        }
    }

    q.push(0);
    while (!q.empty()) {
        ind = q.front();
        q.pop();
        printf("%d ", ind);
        if (left[ind] != 0) {
            q.push(left[ind]);
            if (right[ind] != 0) {
                q.push(right[ind]);
            }
        }
    }

    printf("\n");

    fclose(stdin);

    return 0;
}
