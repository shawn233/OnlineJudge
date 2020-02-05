#include <iostream>
#include <cstdio>
#include <queue>
#include <cstring>
#define MAX 100

using namespace std;

struct Node {
    int x, y;
    Node (int xx, int yy): x(xx), y(yy) {}
};

int mvx[4] = {0, 1, 0, -1};
int mvy[4] = {1, 0, -1, 0};
bool vis[MAX][MAX];

bool findPath(int gp[MAX][MAX], int n, int low, int high) {
    queue<Node> q;
    Node s(0,0);
    int tmp_x, tmp_y;

    for (int i = 0; i < n; ++ i)
        for (int j = 0; j < n; ++ j)
            vis[i][j] = false;

    if (gp[0][0] >= low && gp[0][0] <= high)
        q.push(s);
    else
        return false;
    while(!q.empty()) {
        Node node = q.front();
        q.pop();

        //cout << "node x " << node.x << " y " <<node.y << " val " <<gp[node.x][node.y] << endl;

        if (node.x == n-1 && node.y == n-1)
            return true;

        for (int i = 0; i < 4; ++ i) {
            tmp_x = node.x + mvx[i];
            tmp_y = node.y + mvy[i];
            if (tmp_x < 0 || tmp_x >= n || tmp_y < 0 || tmp_y >= n || vis[tmp_x][tmp_y] || gp[tmp_x][tmp_y]
                    < low ||  gp[tmp_x][tmp_y] > high)
                continue;
            q.push(Node(tmp_x, tmp_y));
            vis[tmp_x][tmp_y] = true;
        }
    }
    return false;
}

int main()
{
    int gp[MAX][MAX], n, low = 120, high = -1, dif_left, dif_right , mid, ans;
    bool flag;

    freopen("in", "r", stdin);

    scanf("%d", &n);

    for (int i = 0; i < n; ++ i) {
        for (int j = 0; j < n; ++ j) {
            scanf("%d", &gp[i][j]);
            low = min(low, gp[i][j]);
            high = max(high, gp[i][j]);
        }
    }

    dif_right = high-low;
    dif_left = 0;
    while(dif_left <= dif_right) {
        mid = (dif_left+dif_right)/2;
        flag = true;
        for (int st = low; st <= high-mid; ++ st)  {
            if(findPath(gp, n, st, st+mid)) {
                flag = false;
                //cout << "pass -- | mid -- " << mid << " st -- " << st << endl;
                break;
            }
        }
        if (flag ) {
            dif_left = mid+1;
        } else {
            dif_right = mid-1;
            ans = mid;
        }
    }

    printf("%d\n", ans);

    fclose(stdin);

    return 0;
}
