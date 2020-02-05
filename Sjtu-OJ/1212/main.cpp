#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>
#define MAX 100010

using namespace std;


template <class elemType>
class linkQueue {
private:
    struct node {
        elemType data;
        node * next;

        node (const elemType & x, node * N = NULL) {
            data = x;
            next = N;
        }
        node (): next(NULL) {}
        ~node () {}
    };

    node * front, * rear;

public:
    linkQueue(): front(NULL), rear(NULL) {}
    ~linkQueue();

    void enQueue (const elemType & x);
    elemType getHead () const {return front->data;}
    elemType deQueue ();
    bool isEmpty() const {return front == NULL;}
};


template <class elemType>
linkQueue<elemType>::~linkQueue() {
    while (front != NULL) {
        rear = front;
        front = front->next;
        delete rear;
    }
}

template <class elemType>
void linkQueue<elemType>::enQueue(const elemType & x) {
    if (front == NULL)
        front = rear = new node (x);
    else {
        rear->next = new node (x);
        rear = rear->next;
    }
}

template <class elemType>
elemType linkQueue<elemType>::deQueue() {
    node * tmp = front;
    front = front->next;
    elemType ans = tmp->data;
    delete tmp;
    if (front == NULL)
        rear = NULL;
    return ans;
}


class BinaryTree {
private:
    struct Node {
        int data;
        int id;
        Node * left, * right;
        Node (): id(0), data(0), left(NULL), right(NULL) {}
        Node (int iid, int dat, Node * lt = NULL, Node * rt = NULL):
            id(iid), data(dat), left(lt), right(rt) {}
    };
    Node * root;

public:
    BinaryTree (int rt, int rt_val) {
        root = new Node (rt, rt_val);
    }

    ~BinaryTree() {
        clear(root);
    }

    void createTree(int * lt, int * rt, int * val) {
        linkQueue<Node *> q;
        Node * tmp;
        int n;

        q.enQueue(root);
        while(!q.isEmpty()) {
            tmp = q.deQueue();
            n = tmp->id;
            if (lt[n]) {
                tmp->left = new Node(lt[n], val[lt[n]]);
                q.enQueue(tmp->left);
            }
            if (rt[n]) {
                tmp->right = new Node (rt[n], val[rt[n]]);
                q.enQueue(tmp->right);
            }
        }
    }

    void layerTraverse() {
        linkQueue<Node *> q;
        Node * tmp;

        q.enQueue(root);
        while (!q.isEmpty()) {
            tmp = q.deQueue();
            printf("%d ", tmp->data);
            if (tmp->left)
                q.enQueue(tmp->left);
            if (tmp->right)
                q.enQueue(tmp->right);
        }
    }

private:
    void clear (Node * node) {
        if (node == NULL)
            return;
        clear(node->left);
        clear(node->right);
        delete node;
    }
};

int main()
{
    int N, val[MAX], left[MAX], right[MAX];
    int not_root[MAX], root;

    scanf("%d", &N);

    memset(not_root, 0, (N+1)*sizeof(int));

    for (int i = 1; i <= N; ++ i) {
        scanf("%d %d %d", &left[i], &right[i], &val[i]);
        not_root[left[i]] = not_root[right[i]] = 1;
    }

    root = 1;
    for (; root <= N; ++ root)
        if (!not_root[root])
        break;

    //printf("%d\n", root);

    BinaryTree btree(root, val[root]);
    btree.createTree(left, right, val);
    btree.layerTraverse();

    return 0;
}
