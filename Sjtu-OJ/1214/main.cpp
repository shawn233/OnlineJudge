#include <iostream>
#include <cstdio>
#include <cstring>
#define MAX 100020

using namespace std;

class OutOfBound {};

/**
 * class definition of link queue
**/
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

/**
 * class definition of link stack
**/

template <class elemType>
class linkStack {
private:
    struct node {
        elemType data;
        node * next;
        node (const elemType & x, node * N = NULL) {
            data = x;
            next = N;
        }
        node (): next(NULL) {}
        ~node (){}
    };

    node * head;

public:
    linkStack();
    ~linkStack();

    bool isEmpty() const ;
    elemType top () const;
    elemType pop ();
    void push (const elemType & x);
};

template <class elemType>
linkStack<elemType>::linkStack():head(NULL) {}

template <class elemType>
linkStack<elemType>::~linkStack() {
    node * ptr = head, *tmp;
    while (ptr != NULL) {
        tmp = ptr;
        ptr = ptr->next;
        delete tmp;
    }
}

template <class elemType>
bool linkStack<elemType>::isEmpty() const {
    return (head == NULL);
}

template <class elemType>
elemType linkStack<elemType>::top () const {
    if (head == NULL)
        throw OutOfBound();
    return head->data;
}


template <class elemType>
elemType linkStack<elemType>::pop () {
    if (head == NULL)
        throw OutOfBound();
    node * ptr = head;
    elemType ans = ptr->data;
    head = head->next;
    delete ptr;
    return ans;
}

template <class elemType>
void linkStack<elemType>::push (const elemType & x) {
    head = new node (x, head); //watch out for the head argument here
}

/**
 * class definition of Tree
**/

class Tree {
private:
    struct Node {
        int data, id;
        Node * lchild, * rsib;
        Node (): data(0), id(0), lchild(NULL), rsib(NULL) {}
        Node (int idd, int dt, Node * lc = NULL, Node * rs = NULL): id(idd), data(dt), lchild(lc), rsib(rs) {}
    };

    Node * root;

public:
    Tree(int rtid, int rtdata) {
        root = new Node (rtid, rtdata, NULL, NULL);
    }

    void createTree(int * lc, int * rs, int * val) {
        linkQueue<Node *> q;
        Node * tmp;
        int tmp_id;

        q.enQueue(root);
        while (!q.isEmpty()) {
            tmp = q.deQueue();
            tmp_id = lc[tmp->id];
            if (tmp_id) {
                tmp->lchild = new Node (tmp_id, val[tmp_id]);
                q.enQueue(tmp->lchild);
            }
            tmp_id = rs[tmp->id];
            if (tmp_id) {
                tmp->rsib = new Node (tmp_id, val[tmp_id]);
                q.enQueue(tmp->rsib);
            }
        }
    }

    void postOrder() {
        linkStack<Node *> st;
        linkStack<int> cnt_st;
        Node * node;
        int cnt;

        st.push(root);
        cnt_st.push(0);

        while (! st.isEmpty()) {
            node = st.top();
            cnt = cnt_st.pop();
            if (cnt) {
                st.pop();
                printf("%d ", node->data);
                if (node->rsib) {
                    st.push(node->rsib);
                    cnt_st.push(0);
                }
            } else {
                cnt_st.push(1);
                if (node->lchild) {
                    node = node->lchild;
                    st.push(node);
                    cnt_st.push(0);
                }
            }
        }
    }

    void preOrder() {
        linkStack<Node *> st;
        Node * node;

        st.push(root);
        while (!st.isEmpty()) {
            node = st.pop();
            printf("%d ", node->data);
            if (node->rsib)
                st.push(node->rsib);
            if (node->lchild)
                st.push(node->lchild);
        }
    }

    void levelOrder() {
        linkQueue<Node *> q;
        Node * node;

        q.enQueue(root);
        while(!q.isEmpty()) {
            node = q.deQueue();
            printf("%d ", node->data);
            node = node->lchild;
            if (node) {
                q.enQueue(node);
                while (node->rsib) {
                    node = node->rsib;
                    q.enQueue(node);
                }
            }
        }
    }
};

int main()
{
    int N, lchild[MAX], rsib[MAX], value[MAX];
    int is_not_root[MAX], root;

    freopen("in.txt", "r", stdin);

    scanf("%d", &N);

    memset(is_not_root, 0, (N+1)*sizeof(int));

    for (int i = 1; i <= N; ++ i) {
        scanf("%d %d %d", &lchild[i], &rsib[i], &value[i]);
        is_not_root[lchild[i]] = is_not_root[rsib[i]] = 1;
    }

    for (root=1; root <= N; ++ root) {
        if (!is_not_root[root]) {
            break;
        }
    }

    Tree tree (root, value[root]);
    tree.createTree(lchild, rsib, value);

    tree.preOrder();
    printf("\n");
    tree.postOrder();
    printf("\n");
    tree.levelOrder();
    printf("\n");

    fclose(stdin);

    return 0;
}
