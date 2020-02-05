#include <iostream>
#include <cstdio>
#define MAX 500010

using namespace std;

struct node {
    node * up, * down;
    int data;
    node (): up(NULL), down(NULL), data(0) {}
    node (int val, node * u, node * d): data(val), up(u), down(d) {}
};

struct Candibox {
    node box[MAX];
    int num[MAX];
    node * cand[MAX];
    bool exst[MAX];
    int node_list[MAX], node_list_cnt;
    int N;

    Candibox(int n):N(n) {
        num[0] = n;
        for (int i = 1; i <= n; ++ i) {
            box[i].down = new node (i, &box[i], NULL);
            cand[i] = box[i].down;
            exst[i] = true;
            num[i] = 1;
        }
    }

    virtual ~Candibox() {
        for (int i = 0; i < N; ++ i)
            clearbox(i);
    };

    int getbox(node * ptr) const {
        while (ptr->data != 0)
            ptr = ptr->up;
        return ptr - box; //doubtful!!
    }

    void clearbox(int m) {
        node * ptr = box[m].down, * tmp;
        while (ptr!=NULL) {
            tmp = ptr;
            ptr = ptr->down;
            delete tmp;
        }
        num[m] = 0;
    }

    node * traversebox(int m) {
        node * ptr = box[m].down;
        node_list_cnt = 0;
        while (ptr->down != NULL) {
            node_list[node_list_cnt] = ptr->data;
            ++ node_list_cnt;
            ptr = ptr->down;
        }
        node_list[node_list_cnt] = ptr->data;
        ++ node_list_cnt;
        return ptr;
    }

    node * boxbottom(int m) {
        node * ptr = box[m].down;
        while (ptr->down != NULL) {
            ptr = ptr->down;
        }
        return ptr;
    }

    void cat(int x, int y) {
        if (exst[x] && exst[y]) {
            int box_x = getbox(cand[x]);
            int box_y = getbox(cand[y]);

            -- num[0];

            node * x_bottom = boxbottom(box_x), * ptry = &box[box_y];

            traversebox(box_y);

            ptry->down->up = x_bottom;
            x_bottom->down = ptry->down;
            ptry->down = NULL;
            num[box_x] += num[box_y];
            num[box_y] = 0;

            for (int i = 0; i < node_list_cnt; ++ i) {
                cand[node_list[i]] = &box[box_x];
            }
        }
    }

    void del(int x) {
        if (exst[x]) {
            int box_x = getbox(cand[x]);
            clearbox(box_x);
            -- num[0];
        }
    }

    int query(int p) {
        if (p > num[0])
            return 0;
        return 1;
    }

    void test_output() {
        for (int i = 1; i <=N; ++ i)
            printf("%d - %d\n", i, num[i]);
    }
};

int main()
{
    int N, M, x, y;
    char cmd;
    scanf("%d %d", &N, &M);
    Candibox cad(N);

    freopen("in.txt", "r", stdin);

    for (int i = 0; i < M; ++ i) {
        while (1) {
            scanf("%c", &cmd);
            if (cmd != '\n' && cmd != ' ')
            break;
        }
        switch (cmd) {
        case 'C':
            scanf("%d %d", &x, &y);
            cad.cat(x, y);
            break;
        case 'D':
            scanf("%d", &x);
            cad.del(x);
            break;
        case 'Q':
            scanf("%d", &x);
            printf("%d\n", cad.query(x));
            break;
        case 'T':
            cad.test_output();
            break;
        default:
            printf("[error] unknown command\n");
        }
    }

    fclose(stdin);

    return 0;
}
