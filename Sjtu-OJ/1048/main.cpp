#include <iostream>
#include <cstdio>
#include <cstring>
#include <queue>
#define MAX 1000

using namespace std;

int main()
{
    int left[MAX], right[MAX];
    bool is_son[MAX];
    int n, tmp;

    freopen("in.txt", "r", stdin);

    scanf("%d", &n);
    for (int i = 1; i <= n; ++ i) {
        is_son[i] = false;
    }
    memset(left, 0, (n+1)*sizeof(int));
    memset(right, 0, (n+1)*sizeof(int));

    while (~scanf("%d", &tmp)) {
        scanf("%d %d", &left[tmp], &right[tmp]);
        is_son[left[tmp]] = true;
        is_son[right[tmp]] = true;
    }

    for (int i = 1; i <= n; ++ i) {
        if (!is_son[i]) {
            tmp = i;
            break;
        }
    }

    queue<int> q;
    q.push(tmp);
    while (!q.empty()) {
        tmp = q.front();
        q.pop();
        printf("%d\n", tmp);
        if (left[tmp] != 0) {
            q.push(left[tmp]);
            q.push(right[tmp]);
        }
    }

    fclose(stdin);

    return 0;
}
