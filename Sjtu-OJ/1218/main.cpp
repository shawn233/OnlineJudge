#include <iostream>
#include <cstdio>

#define MAX 110

using namespace std;

class OutOfBound{};

template <class elemType>
class seqStack {
private :
    elemType * elem;
    int tp;
    int maxSize;

    void doubleSpace();

public:
    seqStack (int initSize = 10);
    ~seqStack();

    bool isEmpty() const ;
    elemType top() const ;
    elemType pop();
    void push (const elemType & x);
};

template <class elemType>
class seqQueue {
private:
    elemType * data;
    int maxSize;
    int front, rear;

    void doubleSpace();

public:
    seqQueue (int initsize = 10);
    ~seqQueue () {delete [] data;}

    bool isEmpty() const {return front == rear;}
    void enQueue(const elemType & x);
    elemType deQueue();
    elemType getHead() const;
};

template <class T>
class BinarySearchTree {
private:
    struct Node {
        T data;
        Node * left, * right;
        Node (const T & x, Node * l=NULL, Node * r=NULL):
            data(x), left(l), right(r) {}
    };

    Node * root;

    Node * findMin(Node * node) const;
    Node * findMax(Node * node) const;
    void insert(const T & x, Node * & node);
    void remove(const T & x, Node * & node);
    bool find (const T & x, Node * node) const;

public:
    BinarySearchTree(): root (NULL) {}
    BinarySearchTree(const T & x) {
        root = new Node (x);
    }

    ~BinarySearchTree() {makeEmpty();}

    bool isEmpty() {
        return root == NULL;
    }

    void makeEmpty();

    bool find(const T & x) const;
    void insert(const T & x);
    void remove(const T & x);
    void traverse() const;
};

class MySet {
private:
    BinarySearchTree<int> * tree_ptr;

public:
    MySet () {
        tree_ptr = new BinarySearchTree<int>;
    }

    ~MySet() {
        if (tree_ptr)
            delete tree_ptr;
    }

    void output() {
        if (tree_ptr)
            tree_ptr->traverse();
        printf("\n");
    }

    void unionMySet(int * x, int n) {
        for (int i = 0; i < n; ++ i) {
            if (!tree_ptr->find(x[i]))
                tree_ptr->insert(x[i]);
        }
    }

    void intersectionMySet(int * x, int n) {
        BinarySearchTree<int> * tmp = new BinarySearchTree<int>;
        for (int i = 0; i < n; ++ i) {
            if (tree_ptr->find(x[i]))
                tmp->insert(x[i]);
        }
        delete tree_ptr;
        tree_ptr = tmp;
    }

    void subtructMySet(int* x, int n) {
        for (int i = 0 ; i < n ; ++ i) {
            if (tree_ptr->find(x[i]))
                tree_ptr->remove(x[i]);
        }
    }

};

// ------------------------------------------------------

int main()
{
    int m, n;
    int arr[MAX];
    char ch;
    MySet s;

    freopen("in.txt", "r", stdin);

    scanf("%d", &n);
    for (int i = 0; i < n; ++ i) {
        do {
            scanf("%c", &ch);
        } while (ch == '\n' || ch == ' ');
        scanf("%d", &m);
        for (int j = 0; j < m; ++ j)
            scanf("%d", &arr[j]);
        //cout << "Operation line " << i << " [" << ch << "] starts" << endl;
        switch(ch) {
        case '+':
            s.unionMySet(arr, m);
            break;
        case '-':
            s.subtructMySet(arr, m);
            break;
        case '*':
            s.intersectionMySet(arr, m);
            break;
        default:
            printf("[error] unexpected operation [%c]\n", ch);
        }
        //cout << "Operation ends | ";
        s.output();
    }

    fclose(stdin);

    return 0;
}

// ------------------------------------------------------

template <class T>
void BinarySearchTree<T>::makeEmpty() {
    if (root == NULL)
        return;
    seqQueue<Node *> q;
    Node * tmp;

    q.enQueue(root);
    while (!q.isEmpty()) {
        tmp = q.deQueue();
        if (tmp->left)
            q.enQueue(tmp->left);
        if (tmp->right)
            q.enQueue(tmp->right);
        delete tmp;
    }
    root = NULL;
}

template <class T>
void BinarySearchTree<T>::insert(const T & x) {
    insert(x, root);
}

template <class T>
void BinarySearchTree<T>::insert(const T & x, Node * & node) {
    if (node == NULL)
        node = new Node (x);
    else if (node->data < x)
        insert(x, node->right);
    else if (x < node->data)
            insert(x, node->left);
    else {
        printf("[warning] repitition occurred in data insertion\n");
    }
}

template <class T>
void BinarySearchTree<T>::remove(const T & x) {
    remove(x, root);
}

template <class T>
void BinarySearchTree<T>::remove(const T & x, Node * & node) {
    if (node == NULL)
        return;
    if (node->data < x) {
        remove(x, node->right);
    } else if (x < node->data) {
        remove(x, node->left);
    } else {
        if (node->left == NULL && node->right == NULL) {
            Node * tmp = node;
            node = NULL;
            delete tmp;
        } else if (node->left && node->right) {
            Node * alter = findMin(node->right);
            node->data = alter->data;
            remove(node->data, node->right);
        } else {
            Node * tmp = node;
            node = (node->left)?node->left:node->right;
            delete tmp;
        }
    }
}

template <class T>
bool BinarySearchTree<T>::find(const T &x) const {
    return find(x, root);
}

template <class T>
bool BinarySearchTree<T>::find(const T & x, Node * node ) const {
    if (node == NULL)
        return false;
    if (node->data < x)
        return find(x, node->right);
    else if (x < node->data)
        return find(x, node->left);
    else
        return true;
}

template <class T>
struct BinarySearchTree<T>::Node * BinarySearchTree<T>::findMin(Node * node) const {
    if (node == NULL)
        return NULL;
    while (node->left)
        node = node->left;
    return node;
}

template <class T>
struct BinarySearchTree<T>::Node * BinarySearchTree<T>::findMax(Node * node) const {
    if (node == NULL)
        return NULL;
    while (node->right)
        node = node->right;
    return node;
}

template <class T>
void BinarySearchTree<T>::traverse() const {
    if (root == NULL)
        return;
    seqStack<Node *> node_st;
    seqStack<int> cnt_st;
    Node * node;
    int cnt;

    node_st.push(root);
    cnt_st.push(0);
    while (!node_st.isEmpty()) {
        node = node_st.top();
        cnt = cnt_st.pop();
        if (cnt) {
            // cnt == 1
            cout << node->data << " ";
            node_st.pop();
            if (node->right) {
                node_st.push(node->right);
                cnt_st.push(0);
            }
        } else {
            // cnt == 0
            cnt_st.push(1);
            if (node->left) {
                node_st.push(node->left);
                cnt_st.push(0);
            }
        }
    }
}

template <class elemType>
void seqQueue<elemType>::doubleSpace() {
    elemType * tmp = new elemType [2 * maxSize];
    for (int i = 1; i < maxSize; ++ i) {
        tmp [i] = data[(front + i)%maxSize];
    }
    front = 0;
    rear = maxSize - 1;
    maxSize *= 2;
    delete [] data;
    data = tmp;
}

template <class elemType>
seqQueue<elemType>::seqQueue(int initsize):
    maxSize(initsize), front(0), rear(0) {
    data = new elemType[initsize];
}

template <class elemType>
void seqQueue<elemType>::enQueue(const elemType & x) {
    if ((rear+1)%maxSize == front)
        doubleSpace();
    rear = (rear+1)%maxSize;
    data[rear] = x;
}

template <class elemType>
elemType seqQueue<elemType>::deQueue() {
    front = (front+1)%maxSize;
    return data[front];
}

template <class elemType>
elemType seqQueue<elemType>::getHead() const {
    return data[(front+1)%maxSize];
}

template <class elemType>
void seqStack<elemType>::doubleSpace() {
    maxSize *= 2;
    elemType * tmp = new elemType[maxSize];
    for (int i = 0; i <= tp; ++ i)
        tmp[i] = elem[i];
    delete [] elem;
    elem = tmp;
}

template <class elemType>
seqStack<elemType>::seqStack (int initSize):
    maxSize(initSize), tp(-1) {
    elem = new elemType [maxSize];
}

template <class elemType>
seqStack<elemType>::~seqStack() {
    delete [] elem;
}

template <class elemType>
bool seqStack<elemType>::isEmpty() const {
    return (tp == -1);
}

template <class elemType>
elemType seqStack<elemType>::top() const {
    if (tp  < 0)
        throw OutOfBound();
    return elem[tp];
}

template <class elemType>
elemType seqStack<elemType>::pop() {
    if (tp < 0)
        throw OutOfBound();
    return elem[tp --];
}

template <class elemType>
void seqStack<elemType>::push (const elemType & x) {
    if (tp == maxSize - 1)
        doubleSpace();
    elem[++ tp] = x;
}
