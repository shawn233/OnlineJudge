#include <iostream>
#include <cstdio>

using namespace std;

class OutOfBound {};

class DisjSets {
public:
	explicit DisjSets(int numElements) ;

	int find (int x) const;
	int find (int x) ;

	void unionSets(int root1, int root2);

private:
	int * arr;
	int length;
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
    const T & getMin() const;

    void merge(BinomialHeap & x);

    void test();
};

template <class TypeOfVer, class TypeOfEdge>
class adjListGraph {
private:
	struct edgeNode {
		int end; // the index of the terminal
		TypeOfEdge weight;
		edgeNode * next;
		edgeNode (int e, TypeOfEdge w, edgeNode* n= NULL):
			end(e), weight(w), next(n) {}
	};

	struct verNode {
		TypeOfVer ver;
		edgeNode * head;
		verNode (edgeNode * h=NULL): head(h) {}
	};

	struct kruskalEdge {
		int beg, end;
		TypeOfEdge w;
		bool operator < (const kruskalEdge & rp) {
			return w < rp.w;
		}
	};

	verNode * verList;
	int vers, edges;

public:
	adjListGraph(int vSize, const TypeOfVer * d);
	~adjListGraph();

	bool insertSingleDirection(int u, int v, TypeOfEdge w);
	bool insertBothDirections(int u, int v, TypeOfEdge w);

    int kruskal() const;
};

// ------------------------------------------------

int main()
{
    int n, m;
    int * arr;

    int a, b, p;

    freopen("in.txt", "r", stdin);

    scanf("%d %d", &n, &m);

    arr = new int [n];
    for (int i = 0; i < n; ++ i)
        arr[i] = i;

    adjListGraph<int, int> g(n, arr);
    for (int i = 0; i < m; ++ i) {
        scanf("%d %d %d", &a, &b, &p);
        g.insertBothDirections(a-1, b-1, p);
    }

    cout << g.kruskal() << endl;

    delete [] arr;

    fclose(stdin);

    return 0;
}

// -----------------------------------------

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
const T & BinomialHeap<T>::getMin() const {
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

DisjSets::DisjSets(int numElements):
	length(numElements) {
	arr = new int [length];
	for (int i = 0; i < length; ++ i)
		arr[i] = -1;
}

/**
 * union sets by size
 **/
void DisjSets::unionSets(int root1, int root2) {
	if (arr[root1] < arr[root2]) {
		// the tree of root1 is larger than that of root2
		arr[root1] += arr[root2];
		arr[root2] = root1;
	} else {
		arr[root2] += arr[root1];
		arr[root1] = root2;
	}
}

int DisjSets::find(int x) const {
	while (! (arr[x] < 0)) {
		// x is not a root
		x = arr[x];
	}
	return x;
}

/**
 * find with path compression
 **/
int DisjSets::find(int x) {
	seqStack<int> st;
    while (!(arr[x] < 0 )) {
		st.push(x);
		x = arr[x];
    }
    while (!st.isEmpty()) {
		arr[st.pop()] = x;
    }
    return x;
}

template <class TypeOfVer, class TypeOfEdge>
adjListGraph<TypeOfVer, TypeOfEdge>::
	adjListGraph(int vSize, const TypeOfVer * d):
		vers(vSize), edges(0) {
	verList = new verNode [vers];
	for (int i = 0; i < vers; ++ i) {
		verList[i].ver = d[i];
	}
}

template <class TypeOfVer, class TypeOfEdge>
adjListGraph<TypeOfVer, TypeOfEdge>::~adjListGraph() {
	edgeNode * ptr;
	for (int i = 0; i < vers; ++ i) {
		ptr = verList[i].head;
		while (ptr) {
			verList[i].head = ptr->next;
			delete ptr;
			ptr = verList[i].head;
		}
	}
	delete [] verList;
}

template <class TypeOfVer, class TypeOfEdge>
bool adjListGraph<TypeOfVer, TypeOfEdge>::insertSingleDirection(int u, int v, TypeOfEdge w) {
	if (u < 0 || u >= vers || v < 0 || v >= vers)
		return false;
	verList[u].head = new edgeNode (v, w, verList[u].head);
	++ edges;
	return true;
}

template <class TypeOfVer, class TypeOfEdge>
bool adjListGraph<TypeOfVer, TypeOfEdge>::insertBothDirections(int u, int v, TypeOfEdge w) {
	return insertSingleDirection(u, v, w) && insertSingleDirection(v, u, w);
}

template <class TypeOfVer, class TypeOfEdge>
int adjListGraph<TypeOfVer, TypeOfEdge>::kruskal() const {
	BinomialHeap<kruskalEdge> pq;
	DisjSets ds (vers);
	kruskalEdge e;
	edgeNode * edge_node;
	int edgeAc = 0; // the number of accepted edges
	int u, v; // to record the find reset of disjoint sets
	int ans=0;

	for (int i = 0; i < vers; ++ i) {
		edge_node = verList[i].head;
		while (edge_node) {
			if (i < edge_node->end) {
				e.beg = i;
				e.end = edge_node->end;
				e.w = edge_node->weight;
				pq.insert(e);
			}
			edge_node = edge_node->next;
		}
	}

	while (edgeAc < vers-1) {
		e = pq.getMin();
		pq.deleteMin();
		u = ds.find(e.end);
		v = ds.find(e.beg);
		if (u != v) {
			++ edgeAc;
			ds.unionSets(u, v);
			ans += e.w;
		}
	}

	return ans;
}
