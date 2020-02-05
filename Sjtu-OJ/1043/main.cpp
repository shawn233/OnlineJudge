#include <iostream>
#include <cstdio>
#include <cmath>
#include <map>
#include <queue>
#include <cstring>
#define MAX 10000

using namespace std;

struct Node {
    int data;
    int depth;
    Node * left, * right;
    Node (int num, int dpt): data(num), depth(dpt), left(NULL), right(NULL) {}
};

class Tree {
private:
    Node * root;
    int max_dpt;
    void makeEmpty(Node * node) {
        if(node == NULL)
            return;
        makeEmpty(node->left);
        makeEmpty(node->right);
        delete node;
    }

    bool insert(int data, int parent_data, Node * node) {
        if(node == NULL)
            return false;
        if(node->data == parent_data) {
            Node * ptr = new Node (data, node->depth+1);
            if(node->left == NULL) {
                node->left = ptr;
            } else if(node->right == NULL) {
                if(node->left->data > data) {
                    node->right = node->left;
                    node->left = ptr;
                } else
                    node->right = ptr;
            } else {
                delete ptr;
                return false;
            }
            max_dpt = max(max_dpt, ptr->depth);
            return true;
        } else {
            if(insert(data, parent_data, node->left))
                return false;
            else
                return insert(data, parent_data, node->right);
        }
    }

public:
    Tree() {
        root = new Node (0, 1);
        max_dpt = 1;
    }
    ~Tree() {makeEmpty(root);}

    bool insert(int data, int parent_data) {
        return insert(data, parent_data, root);
    }

    bool complete() {
        queue<Node *> q;
        if(root == NULL)
            return false;
        if(max_dpt < 3)
            return true;
        q.push(root);
        while(!q.empty()) {
            Node * ptr = q.front();
            if(ptr->depth == max_dpt-1)
                break;
            q.pop();
            if(ptr->left == NULL)
                return false;
            q.push(ptr->left);
            if(ptr->right == NULL)
                return false;
            q.push(ptr->right);
        }
        //Now q has all nodes of depth max_dpt-1
        if (q.size() != pow(2, max_dpt-2))
            return false;
        bool flag = true;
        while(!q.empty()) {
            Node * ptr = q.front();
            q.pop();
            if(flag) {
                if(ptr->left == NULL) {
                    if(ptr->right != NULL)
                        return false;
                    flag = false;
                    continue;
                } else if(ptr->right == NULL) {
                    flag = false;
                    continue;
                }
            } else {
                if(ptr->left == NULL && ptr->right == NULL)
                    continue;
                else
                    return false;
            }
        }
        return true;
    }

    void show() {
        queue<Node *> q;
        int depth = 1;
        if(root == NULL)
            return;
        q.push(root);
        while(!q.empty()) {
            Node * ptr = q.front();
            q.pop();
            if(depth != ptr->depth) {
                depth = ptr->depth;
                printf("\n");
            }
            if(ptr->left != NULL)
                q.push(ptr->left);
            if(ptr->right != NULL)
                q.push(ptr->right);
            printf("%d|%d\t", ptr->depth, ptr->data);
        }
    }
};

//Time Limited when Tree is large
int main_t()
{
    Tree t;
    int nodes, tmp;

    freopen("in", "r", stdin);

    scanf("%d", &nodes);
    for (int i = 1; i < nodes; ++ i) {
        scanf("%d", &tmp);
        t.insert(i, tmp);
    }
    //t.show();
    if(t.complete())
        printf("true\n");
    else
        printf("false\n");

    fclose(stdin);

    return 0;
}

void show(int * tree, int n) {
    int lim = 0, cnt = 2;
    for (int i = 0; i < n; ++ i) {
        printf("%d", tree[i]);
        if (i == lim) {
            printf("\n");
            lim += cnt;
            cnt *= 2;
        } else
            printf("\t");
    }
}

//Correct Version | Use the belowing definition of MAX

/*
#include <iostream>
#include <cstdio>
#include <cstring>
#define MAX 1000000

using namespace std;
*/

int main () {
    int tree[MAX], index[MAX];
    int N, par, ind;

    freopen("in", "r", stdin);

    scanf("%d", &N);
    if(N < 2) {
        printf("true\n");
        return 0;
    }
    memset(tree, 0, sizeof(tree));
    memset(index, 0, sizeof(index));
    for (int tr = 1; tr < N; ++ tr) {
        scanf("%d", &par);
        ind = index[par] * 2 + 1;
        if (ind >= MAX) {
            printf("false\n");
            return 0;
        }
        if (tree[ind] == 0 || tr == 1) {
            tree[ind] = tr;
            index[tr] = ind;
        } else if (tree[ind+1] == 0){
            ++ ind;
            tree[ind] = tr;
            index[tr] = ind;
        } else {
            printf("false\n");
            return 0;
        }
    }
    //show(tree, N);

    for (int i = 1; i < N; ++ i)
        if(tree[i] == 0) {
            printf("false\n");
            return 0;
        }
    printf("true\n");

    fclose(stdin);

    return 0;
}

//Here is another correct version, using a bool array to represent the tree
/*
#include <iostream>
#include <cstdio>
#include <cstring>
#define MAX 1000005

using namespace std;

int main () {
    int index[MAX];
    bool tree[MAX];
    int N, tmp, ind;

    memset(index, 0, sizeof(index));

    cin >> N;

    for (int i =  1; i <= N; ++ i)
        tree[i] = false;
    index[0] = 1;
    tree[1] = true;
    for (int i = 1; i < N; ++ i) {
        cin >> tmp;
        ind = 2*index[tmp];
        if (ind > N) {
             printf("false\n");
             return 0;
         }
        if (tree[ind] == false) {
             index[tmp] = ind;
             tree[ind] = true;
         } else if (ind <= N && tree[ind+1] == false) {
             ++ind;
             index[tmp] = ind;
             tree[ind] = true;
         } else {
             printf("false\n");
             return 0;
         }
    }
    for (int i = 1; i <= N; ++ i)
        if (!tree[i]) {
            printf("false\n");
             return 0;
    }
    printf("true\n");
    return 0;
}
*/
