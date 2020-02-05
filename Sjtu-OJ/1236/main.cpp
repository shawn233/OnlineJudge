#include <iostream>
#include <cstdio>
#define INF 0x7FFFFFFF

using namespace std;

class OutOfBound {};

template <class elemType>
class seqQueue{
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
class seqStack  {
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

	verNode * verList;
	int vers, edges;

public:
	adjListGraph(int vSize, const TypeOfVer * d);
	~adjListGraph();

	bool insertSingleDirection (int u, int v, TypeOfEdge w);
    void negativeWeightedShortestDistance (TypeOfVer start, TypeOfVer end) const;
};

// ------------------------------------------------------

int main()
{
    int n, m, start, end, a, b, p;
    int * arr;

    freopen("in.txt", "r", stdin);

    scanf("%d %d %d %d", &n, &m, &start, &end);
    arr = new int [n];
    for (int i = 0; i < n; ++ i)
        arr[i] = i;
    adjListGraph<int, int> g(n, arr);

    for (int i = 0; i < m; ++ i) {
        scanf("%d %d %d", &a, &b, &p);
        g.insertSingleDirection(a-1, b-1, p);
    }

    g.negativeWeightedShortestDistance(start-1, end-1);

    fclose(stdin);

    delete [] arr;

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
void adjListGraph<TypeOfVer, TypeOfEdge>::negativeWeightedShortestDistance(TypeOfVer start, TypeOfVer end) const {
    // here i present the most trivial algorithm for this problem: search based algorithm
    int start_node, end_node;

    for (start_node = 0; start < vers; ++ start_node)
        if (verList[start_node].ver == start)
            break;
    if (start_node == vers) {
        cout << "[warning] start node (" << start << ") does not exist in function negativeWeightedShortestDistance" << endl;
		return;
    }

    for (end_node = 0; end_node < vers; ++ end_node)
        if (verList[end_node].ver == end)
            break;

    seqQueue <int> q;
    int tmp, tmp_dis;
    int * distance = new int [vers];
    int * prev = new int [vers];
    edgeNode * edge;

    for (int i = 0; i < vers; ++ i)
        distance[i] = INF;

    distance[start_node] = 0;
    prev[start_node] = start_node;

    q.enQueue(start_node);
    while (!q.isEmpty()) {
        tmp = q.deQueue();
        edge = verList[tmp].head;
        while (edge) {
            tmp_dis = distance[tmp] + edge->weight;
            if (tmp_dis < distance[edge->end]) {
                distance[edge->end] = tmp_dis;
                prev[edge->end] = tmp;
                q.enQueue(edge->end);
            }
            edge = edge->next;
        }
    }

    printf("%d\n", distance[end_node]);

    delete [] distance;
    delete [] prev;
}
