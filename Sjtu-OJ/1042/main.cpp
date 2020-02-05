#include <iostream>
#include <cstdio>
#include <queue>
#define MAX 12500

using namespace std;

void dlr(int * left, int * sibling, int root) {
    printf("%d ", root);
    if (left[root] != 0) {
        root = left[root];
        dlr(left, sibling, root);
        for (; sibling[root] != 0; root = sibling[root]) {
            dlr(left, sibling, sibling[root]);
        }
    }
}

void lrd(int * left, int * sibling, int root) {
    int lc = left[root];
    if (lc != 0) {
        lrd(left, sibling, lc);
        for (; sibling[lc] != 0; lc = sibling[lc]) {
            lrd(left, sibling, sibling[lc]);
        }
    }
    printf("%d ", root);
}

void level(int * left, int * sibling, int root) {
    queue<int> q;
    q.push(root);
    while (!q.empty()) {
        int tmp = q.front();
        q.pop();
        printf("%d ", tmp);
        if (left[tmp] != 0) {
            tmp = left[tmp];
            q.push(tmp);
            for(; sibling[tmp] != 0; tmp = sibling[tmp]) {
                q.push(sibling[tmp]);
            }
        }
    }
}

int main()
{
    int left[MAX], sibling[MAX];
    bool is_left[MAX], is_sibling[MAX];
    int n, tmp, root;

    freopen("in.txt", "r", stdin);

    scanf("%d", &n);

    for (int i = 1; i < n; ++ i) {
        is_left[i] = is_sibling[i] = false;
    }

    for (int i = 0; i < n; ++ i) {
        scanf("%d", &tmp);
        scanf("%d %d", &left[tmp], &sibling[tmp]);
        is_left[left[tmp]] = true;
        is_sibling[sibling[tmp]] = true;
    }

    for (int i = 1; i <= n; ++ i) {
        if ((!is_left[i]) && (!is_sibling[i])) {
            root = i;
            break;
        }
    }

    dlr(left, sibling, root);
    cout << endl;
    lrd(left, sibling, root);
    cout << endl;
    level(left, sibling, root);
    cout <<endl;

    fclose(stdin);

    return 0;
}
