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
        Node * left, * right;
        Node (): data(0), left(NULL), right(NULL) {}
        Node (int dat, Node * lt = NULL, Node * rt = NULL): data(dat), left(lt), right(rt) {}

        int degree() {
            return int((left!=NULL)+(right!=NULL));
        }
    };
    Node * root;

public:
    BinaryTree (int rt) {
        root = new Node (rt);
    }

    ~BinaryTree() {
        clear(root);
    }

    void createTree(int * lt, int * rt) {
        linkQueue<Node *> q;
        Node * tmp;
        int n;

        q.enQueue(root);
        while(!q.isEmpty()) {
            tmp = q.deQueue();
            n = tmp->data;
            if (lt[n]) {
                tmp->left = new Node(lt[n]);
                q.enQueue(tmp->left);
            }
            if (rt[n]) {
                tmp->right = new Node (rt[n]);
                q.enQueue(tmp->right);
            }
        }
    }

    int height () {
        return height(root);
    }

    bool isComplete() {
        linkQueue<Node *> q;
        Node * tmp;
        int degree, ht, cnt; //ht means height
        bool start_check = false;

        ht = height();
        cnt = 0;

        q.enQueue(root);
        while (!q.isEmpty()) {
            tmp = q.deQueue();
            ++ cnt;
            degree = tmp->degree();
            if (start_check) {
                if (degree) {
                    return false;
                }
            } else if (degree < 2) {
                if (degree == 1 && tmp->left == NULL) {
                    return false;
                }
                if (cnt >= (pow(2, ht-2)) && cnt < pow(2, ht-1))
                    start_check = true;
                else {
                    return false;
                }
            }

            if (tmp->left)
                q.enQueue(tmp->left);
            if (tmp->right)
                q.enQueue(tmp->right);
        }
        return true;
    }

private:
    void clear (Node * node) {
        if (node == NULL)
            return;
        clear(node->left);
        clear(node->right);
        delete node;
    }

    int height (Node * t) {
        if (t == NULL)
            return 0;
        else
            return max(height(t->left), height(t->right)) + 1;
    }
};

int main()
{
    int N, left[MAX], right[MAX];
    int not_root[MAX], root;

    freopen("in.txt", "r", stdin);

    scanf("%d", &N);

    memset(not_root, 0, (N+1) * sizeof(int));

    for (int i = 1; i <= N; ++ i) {
        scanf ("%d %d", &left[i], &right[i]);

        if (left[i] == 0 && right[i] != 0) {
            printf("N\n");
            return 0;
        }

        not_root[left[i]] = not_root[right[i]] = 1;
    }

    for (root = 1; root <= N; ++ root) {
        if (! not_root[root])
            break;
    }

    BinaryTree btree (root);

    btree.createTree(left, right);

    if (btree.isComplete()) {
        printf("Y\n");
    } else {
        printf("N\n");
    }

    fclose (stdin);

    return 0;
}
