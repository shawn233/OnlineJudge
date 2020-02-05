#include <iostream>
#include <cstdio>
#define MAX 300005

using namespace std;

struct Girl {
    int charm;
    Girl * left, * right;
    explicit Girl (int c): charm(c), left(NULL), right(NULL) {}
    Girl ():charm(-1), left(NULL), right(NULL) {}
};

Girl * merge1(Girl * h1, Girl * h2);

Girl * merge (Girl * h1, Girl * h2) {
    if (h2 == NULL)
        return h1;
    if (h1 == NULL) {
        return h2;
    }
    if (h1->charm > h2->charm)
        return merge1(h2, h1);
    else
        return merge1(h1, h2);
}

Girl * merge1(Girl * h1, Girl * h2) {
    if (h1->left == NULL) {
        h1->left = h2;
        return h1;
    }
    Girl * tmp = h1->left;
    h1->left = merge(h1->right, h2);
    h1->right = tmp;
    return h1;
}

void mergeTo(Girl ** girls, int from, int dest) {
    if (girls[from] == NULL)
        return;
    if (girls[dest] == NULL) {
        girls[dest] = girls[from];
        girls[from] = NULL;
        return;
    }
    girls[dest] = merge(girls[from], girls[dest]);
}

void percolateDown(Girl * & node) {
    if (node->left != NULL || node->right != NULL) {
        if (node->right == NULL ) {
            node->charm = node->left->charm;
            percolateDown(node->left);
        } else if (node->left == NULL) {
            node->charm = node->right->charm;
            percolateDown(node->right);
        } else if (node->right->charm > node->left->charm) {
            node->charm = node->left->charm;
            percolateDown(node->left);
        }else {
            node->charm = node->right->charm;
            percolateDown(node->right);
        }
    } else {
        delete node;
        node = NULL;
    }
}

void deleteMin(Girl * & root) {
    printf("%d\n", (root->charm));
    percolateDown(root);
}

void deleteMin(Girl ** girls, int ind) {
    if (girls[ind] == NULL) {
        printf("-1\n");
        return;
    }
    deleteMin(girls[ind]);
}

void insert(Girl ** girls, int ind, int ch) {
    Girl * tmp = new Girl (ch);
    girls[ind] = merge(girls[ind], tmp);
}

int main()
{
    Girl * girls[MAX];
    int N, M, tmp, h1, h2;

    freopen("in.txt", "r", stdin);

    scanf("%d %d", &N, &M);

    for (int i = 0; i < N; ++ i) {
        scanf("%d", &tmp);
        girls[i] = new Girl(tmp);
    }

    for (int i = 0; i < M; ++ i) {
        scanf("%d", &tmp);
        switch(tmp) {
        case 0:
            scanf("%d %d", &h1, &h2);
            mergeTo(girls, h2, h1);
            break;
        case 1:
            scanf("%d", &tmp);
            deleteMin(girls, tmp);
            break;
        case 2:
            scanf("%d %d", &h1, &tmp);
            insert(girls, h1, tmp);
            break;
        default:
            printf("<error> unknown command <%d>\n", tmp);
        }
    }

    fclose(stdin);

    return 0;
}
