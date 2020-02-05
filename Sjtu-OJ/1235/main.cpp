#include <iostream>
#include <cstdio>
#define INF 0x7FFFFFFF

using namespace std;

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
class BinomialHeap {
private:
    struct Node {
        T data;
        Node * ns, * fc;
        Node ():ns(NULL), fc(NULL) {}
        Node (const T & dat, Node * fcc=NULL, Node * nss=NULL):
            fc(fcc), ns(nss) {data = dat;}
    };

    Node ** arr;
    int currentSize, maxlen;

    void doubleSpace();
    void relen(int len);
    struct Node * combineTrees(Node * n1, Node * n2);
    int findMinIndex() const;
    void clearTree(Node * node);
    int convertSize2Len(int sz) const; // given a size, calculate the sufficient length of array

public:
    BinomialHeap(int initlen=8);
    ~BinomialHeap();

    void insert(const T & x);
    void deleteMin ();
    T getMin() const;

    void merge(BinomialHeap & x);

    void test();
};

class adjListGraph {
private:
    struct edgeNode {
        int end, weight;
        edgeNode * next;
        edgeNode (int e, int w, edgeNode *n=NULL):
            end(e), weight(w), next(n) {}
    };

    struct verNode {
        int ver;
        edgeNode * head;
        verNode (int v=-1, edgeNode * h=NULL):
            ver(v), head(h) {}
    };

    struct dijikstraNode {
        int ver, prev, dist, cnt;
        bool operator < (const dijikstraNode & x) {
            return dist < x.dist;
        }

        dijikstraNode (int v=-1, int p=-1, int d=INF, int ct=-1):
            ver(v), prev(p), dist(d), cnt(ct) {}

        void value(int v, int p, int d, int ct) {
            ver = v;
            prev = p;
            dist = d;
            cnt = ct;
        }
    };

    int vers, edges;
    verNode * verList;

    void printPath(int start, int end, dijikstraNode * dj) const {
        if (start == end) {
            printf("%d", dj[start].ver+1);
            return;
        }
        printPath(start, dj[end].prev, dj);
        printf(" %d", dj[end].ver+1);
    }

    void OutputDj(dijikstraNode * dj) const {
        cout << endl;
        for (int i = 0; i < vers; ++ i) {
            cout << "i -- " << i << " ver -- " << dj[i].ver << endl;
            cout << "i -- " << i << " prev -- " << dj[i].prev << endl;
            cout << "i -- " << i << " dist -- " << dj[i].dist << endl;
        }
        cout << endl;
    }

public:
    adjListGraph (int v):vers(v), edges(0) {
        verList = new verNode [v];
    }

    ~adjListGraph () {
        edgeNode * tmp;
        for (int i = 0; i < vers; ++ i) {
            tmp = verList[i].head;
            while (tmp) {
                verList[i].head = tmp->next;
                delete tmp;
                tmp = tmp->next;
            }
        }
        delete [] verList;
    }

    bool insert(int u, int v, int w) {
        if (u < 0 || u >= vers || v < 0 || v >= vers)
            return false;
        verList[u].head = new edgeNode(v, w, verList[u].head);
        ++ edges;
    }

    void dijikstra(int start, int end) const {
        BinomialHeap<dijikstraNode> q;
        dijikstraNode * dj = new dijikstraNode[vers];
        dijikstraNode dnode;
        int node_cnt = 1, cur_node = start, tmp_dis, tmp_cnt;
        bool * known = new bool [vers];
        edgeNode * edge;

        for (int i = 0; i < vers; ++ i)
            known[i] = false;

        dj[start].value(start, start, 0, 0);
        known[start] = true;

        while (node_cnt < vers) {
            //cout << "cur_node -- " << cur_node << endl;
            edge = verList[cur_node].head;
            while (edge) {
                tmp_dis = dj[cur_node].dist + edge->weight;
                tmp_cnt = dj[cur_node].cnt + 1;
                if (!known[edge->end] && (tmp_dis < dj[edge->end].dist || ( tmp_dis == dj[edge->end].dist && tmp_cnt < dj[edge->end].cnt))) {
                    dj[edge->end].value(edge->end, cur_node, tmp_dis, tmp_cnt);
                    q.insert(dj[edge->end]);
                }
                edge = edge->next;
            }
            //OutputDj(dj);
            do {
                dnode = q.getMin();
                q.deleteMin();
            } while (known[dnode.ver]);
            known[dnode.ver] = true;
            cur_node = dnode.ver;
            ++ node_cnt;
            if (cur_node == end)
                break;
        }

        printf("%d\n", dj[end].dist);
        printPath (start, end, dj);
        printf("\n");

        delete [] known;
        delete [] dj;
    }
};

// ----------------------------------------------------

int main()
{
    int n, m, start, end;
    int a, b, p;

    freopen("in.txt", "r", stdin);

    scanf("%d %d %d %d", &n, &m, &start, &end);

    adjListGraph g(n);

    for (int i = 0; i < m; ++ i) {
        scanf("%d %d %d", &a, &b, &p);
        g.insert(a-1, b-1, p);
    }

    g.dijikstra(start-1, end-1);

    fclose(stdin);

    return 0;
}

// --------------------------------------------------------

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

template <class T>
void BinomialHeap<T>::doubleSpace() {
    Node ** tmp = new Node * [maxlen * 2];
    for (int i = 0; i < maxlen; ++ i)
        tmp[i] = arr[i];
    delete [] arr;
    for (int i = maxlen; i < 2 * maxlen; ++ i) {
        tmp[i] = NULL;
    }
    maxlen *= 2;
    arr = tmp;
}

template <class T>
void BinomialHeap<T>::relen(int len) {
    Node * tmp = new Node * [len];
    for (int i = 0; i < maxlen; ++ i)
        tmp[i] = arr[i];
    delete [] arr;
    for (int i = maxlen; i < len; ++ i)
        tmp[i] = NULL;
    maxlen = len;
    arr = tmp;
}

template <class T>
struct BinomialHeap<T>::Node * BinomialHeap<T>::combineTrees(Node * n1, Node * n2) {
    if (n1 == NULL)
        return n2;
    if (n2 == NULL)
        return n1;

    if (n2->data < n1->data)
        return combineTrees(n2, n1);
    n2->ns = n1->fc;
    n1->fc = n2;
    return n1;
}

template <class T>
int BinomialHeap<T>::findMinIndex() const {
    if (currentSize == 0)
        return -1; // -1 represents exception
    int ans;
    for (ans = 0; !arr[ans]; ++ ans);
    for (int i = ans; i < maxlen; ++ i)
        if (arr[i] && arr[i]->data < arr[ans]->data) {
            ans = i;
        }
    return ans;
}

template<class T>
void BinomialHeap<T>::clearTree(Node * node) {
    if (!node)
        return;

    seqQueue<Node *> q;
    Node * tmp;

    q.enQueue(node);
    while (!q.isEmpty()) {
        tmp = q.deQueue();
        if (tmp->fc)
            q.enQueue(tmp->fc);
        if (tmp->ns)
            q.enQueue(tmp->ns);
        delete tmp;
    }
}

template <class T>
int BinomialHeap<T>::convertSize2Len (int sz) const {
    int ans, cnt;
    for (ans = 0, cnt = 1; sz; ++ cnt, sz = (sz >> 1)) {
        if (sz & 1)
            ans = cnt;
    }
    return ans;
}

template <class T>
BinomialHeap<T>::BinomialHeap(int initlen):
    maxlen(initlen), currentSize(0) {
    arr = new Node * [maxlen];
    for (int i = 0; i < maxlen; ++ i)
        arr[i] = NULL;
}

template <class T>
BinomialHeap<T>::~BinomialHeap() {
    for (int i = 0; i < maxlen; ++ i) {
        clearTree(arr[i]);
    }
    delete [] arr;
}

template <class T>
void BinomialHeap<T>::merge(BinomialHeap & x) {
    int res_len, case_opt;
    Node * carry = NULL, * xarri_prox;

    currentSize = currentSize + x.currentSize;
    x.currentSize = 0;
    res_len = convertSize2Len(currentSize);
    while (maxlen < res_len)
        doubleSpace();

    for (int i = 0; i < res_len; ++ i) {
        case_opt = 0;
        if (i < x.maxlen)
            xarri_prox = x.arr[i];
        else
            xarri_prox = NULL;
        if (arr[i])
            ++ case_opt;
        if (xarri_prox)
            ++ case_opt;
        if (carry)
            ++ case_opt;
        //cout << "i -- " << i << " case_opt -- " << case_opt << endl;
        switch (case_opt) {
        case 0:
            break;
        case 1:
            arr[i] = combineTrees(combineTrees(arr[i], xarri_prox), carry);
            carry = NULL;
            if (i < x.maxlen)
                x.arr[i] = NULL;
            break;
        case 2:
            carry = combineTrees(combineTrees(arr[i], xarri_prox), carry);
            arr[i] = NULL;
            if (i < x.maxlen)
                x.arr[i] = NULL;
            break;
        case 3:
            x.arr[i] = combineTrees(x.arr[i], arr[i]);
            arr[i] = carry;
            carry = x.arr[i];
            x.arr[i] = NULL;
            break;
        default:
            printf("[error] exception in case_opt: case_opt = %d\n", case_opt);
        }
    }
}

template <class T>
void BinomialHeap<T>::insert(const T & x) {
    BinomialHeap<T> tmp(1);
    tmp.currentSize = 1;
    tmp.arr[0] = new Node (x);
    merge(tmp);
}

template <class T>
void BinomialHeap<T>::deleteMin() {
    //cout << "currentSize -- " << currentSize << endl;
    int ind = findMinIndex();
    BinomialHeap<T> tmp (ind);
    tmp.currentSize = (1 << ind) - 1;
    currentSize -= (1<<ind);

    //cout << "ind -- " << ind << "curreutSize -- " << currentSize << " min = " << arr[ind]->data << endl;

    Node * node = arr[ind]->fc;
    delete arr[ind];
    arr[ind] = NULL;

    for (int i = ind-1; i >= 0; -- i) {
        tmp.arr[i] = node;
        node = node->ns;
        tmp.arr[i]->ns = NULL;
    }

    merge(tmp);
}

template <class T>
T BinomialHeap<T>::getMin() const {
    return arr[findMinIndex()]->data;
}

template <class T>
void BinomialHeap<T>::test() {
    cout << "currentSize -- " << currentSize << " maxlen -- " << maxlen << endl;
    for (int i = 0; i < maxlen; ++ i) {
        if (arr[i])
            cout << arr[i]->data;
        cout << " | ";
    }
    cout << endl;
 }
