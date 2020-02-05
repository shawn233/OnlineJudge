#include <iostream>
#include <cstdio>

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

    void makeEmpty(Node * node);

    Node * findMin(Node * node) const;
    Node * findMax(Node * node) const;
    void insert(const T & x, Node * & node);
    void remove(const T & x, Node * & node);
    bool find (const T & x, Node * node) const;

    void removeLessThan(const T & x, Node * & node);
    void removeGreaterThan(const T & x, Node * & node);
    void removeInterval(const T & a, const T & b, Node * & node);

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

    void removeLessThan(const T & x);
    void removeGreaterThan(const T & x);
    void removeInterval(const T & a, const T & b);
    bool findIth(int i, int & res) const;
};

// ------------------------------------------------------

int main()
{
    BinarySearchTree<int> tree;
    int tmp1, tmp2, n;
    char cmd[50];
    char ch;
    bool debug = false;

    freopen("in.txt", "r", stdin);

    cin >> n;
    for (int i = 0; i < n; ++ i) {
        cin >> cmd;
        switch(cmd[0]) {
        case 'i':
            cin >> tmp1;
            tree.insert(tmp1);
            break;
        case 'f':
            if (cmd[4] == '\0') {
                // cmd: find
                cin >> tmp1;
                if (tree.find(tmp1))
                    printf("Y\n");
                else
                    printf("N\n");
            } else {
                // cmd: find_ith
                cin >> tmp1;
                int res;
                if (tree.findIth(tmp1, res)) {
                    printf("%d\n", res);
                } else {
                    printf("N\n");
                }
            }
            break;
        case 'd':
            if (cmd[6] == '\0') {
                // cmd: delete
                cin >> tmp1;
                tree.remove(tmp1);
            } else {
                // cmd: delete_?
                cin >> tmp1;
                switch(cmd[7]) {
                case 'l':
                    // cmd: delete_less_than
                    tree.removeLessThan(tmp1);
                    break;
                case 'g':
                    // cmd: delete_greater_than
                    tree.removeGreaterThan(tmp1);
                    break;
                case 'i':
                    cin >> tmp2;
                    tree.removeInterval(tmp1, tmp2);
                    break;
                default:
                    printf("[error] unexpected deletion operation with indication character [%c]\n", cmd[7]);
                }
            }
            break;
        default:
            printf("[error] unexpected cmd [%c]\n", cmd[0]);
        }
        if (debug) {
            printf("[note] after operation line %d | cmd[0] %c | Then tree becomes:\n", i, cmd[0]);
            tree.traverse();
            printf("\n\n");
        }
    }

    fclose(stdin);

    return 0;
}

// ------------------------------------------------------

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

template <class T>
void BinarySearchTree<T>::makeEmpty(Node * node) {
    if (node == NULL)
        return;
    seqQueue<Node *> q;
    Node * tmp;

    q.enQueue(node);
    while (!q.isEmpty()) {
        tmp = q.deQueue();
        if (tmp->left)
            q.enQueue(tmp->left);
        if (tmp->right)
            q.enQueue(tmp->right);
        delete tmp;
    }
}

template <class T>
void BinarySearchTree<T>::makeEmpty() {
    makeEmpty(root);
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
    else
            insert(x, node->left);
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

template <class T>
void BinarySearchTree<T>::removeLessThan(const T & x, Node * & node) {
    if (node == NULL)
        return;
    if (node->data < x) {
        remove(node->data, node);
        removeLessThan(x, node);
    } else
        removeLessThan(x, node->left);
}

template <class T>
void BinarySearchTree<T>::removeLessThan(const T & x) {
    removeLessThan(x, root);
}

template <class T>
void BinarySearchTree<T>::removeGreaterThan(const T & x, Node * & node) {
    if (node == NULL)
        return;
    if (x < node->data) {
        remove(node->data, node);
        removeGreaterThan(x, node);
    } else
        removeGreaterThan(x, node->right);
}

template <class T>
void BinarySearchTree<T>::removeGreaterThan(const T & x) {
    removeGreaterThan(x, root);
}

template <class T>
void BinarySearchTree<T>::removeInterval(const T & a, const T & b, Node * & node) {
    if (node == NULL)
        return;
    if (node->data < a || node->data == a)
        removeInterval(a, b, node->right);
    else if (b < node->data || node->data == b)
        removeInterval(a, b, node->left);
    else {
        // a < node->data < b
        remove(node->data, node);
        removeInterval(a, b, node);
    }
}

template <class T>
void BinarySearchTree<T>::removeInterval(const T & a, const T & b) {
    if (a < b)
        removeInterval(a, b, root);
}

template <class T>
bool BinarySearchTree<T>::findIth(int i, int & res) const {
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
            -- i;
            if (i == 0) {
                res = node->data;
                return true;
            }
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
    return false;
}
