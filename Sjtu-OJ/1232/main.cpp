#include <iostream>
#include <cstdio>

#define MAX 50000

using namespace std;

class DisjSets {
public:
	explicit DisjSets(int numElements) ;

	int find (int x) ;
	void unionSets(int root1, int root2);

private:
	int * arr;
	int length;
};

class adjListGraph {
private:
	struct edgeNode {
		int end; // the index of the terminal
		edgeNode * next;
		edgeNode (int e, edgeNode* n= NULL):
			end(e), next(n) {}
	};

	struct verNode {
		int ver;
		edgeNode * head;
		verNode (edgeNode * h=NULL): head(h) {}
	};

	verNode * verList;
	int vers, edges;
	bool showPath(int u, int v, bool * visited) const;

public:
	adjListGraph(int vSize);
	~adjListGraph();

	void insert (int u, int v);
	void showPath(int u, int v) const;
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

class OutOfBound {};

int getInd(int ind, int dir, int * line_num) {
	int res;
	switch (dir) {
	case 0:
		res = ind -line_num[ind];
		break;
	case 1:
		res = ind - line_num[ind] + 1;
		break;
	case 2:
		res = ind + line_num[ind];
		break;
	case 3:
		res = ind + line_num[ind] + 1;
		break;
	}
	return res;
}

int main()
{
    int N, A, B;
    int tmp1, tmp2, tmp3;
    int line_num[MAX]; // save the line number for each element
	int length;

    freopen("in.txt", "r", stdin);
    scanf("%d %d %d", &N, &A, &B);

	length =  (N+1) * N/2;
    tmp1 = 1;
    tmp2 = 1;
    for (int i = 1; i <= length; ++ i) {
        if (tmp1 < i) {
			++ tmp2;
			tmp1 += tmp2;
        }
        line_num[i] = tmp2;
    }

    DisjSets ds(1 + length);
    adjListGraph graph(length);

    while (~scanf("%d %d", &tmp1, &tmp2)) {
		tmp3 = getInd(tmp1, tmp2, line_num);
		if (tmp3 > 0 && tmp3 <= length) {
			graph.insert(tmp1-1, tmp3-1);
			ds.unionSets(ds.find(tmp1), ds.find(tmp3));
			if (ds.find(A) == ds.find(B))
				break;
		}
    }

	graph.showPath(A-1, B-1);
	printf("\n");

    fclose(stdin);

    return 0;
}

// ---------------------------------------

bool debug = true;

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

// ------------------------------

adjListGraph::adjListGraph(int vSize):
	vers(vSize), edges(0) {
	verList = new verNode[vSize];
	for (int i = 0; i < vSize; ++ i)
		verList[i].ver = i+1;
}

adjListGraph::~adjListGraph() {
	edgeNode * ptr;
	for (int i = 0; i < vers; ++ i) {
		ptr = verList[i].head;
		while(ptr) {
			verList[i].head = ptr->next;
			delete ptr;
			ptr = verList[i].head;
		}
	}
	delete [] verList;
}

void adjListGraph::insert(int u, int v) {
	verList[u].head = new edgeNode(v, verList[u].head);
	verList[v].head = new edgeNode(u, verList[v].head);
	++ edges;
}

void adjListGraph::showPath(int u, int v) const {
	bool visited [MAX];
	for (int i = 0; i < vers; ++ i)
		visited[i] = false;
	showPath(u, v, visited);
}

bool adjListGraph::showPath(int u, int v, bool * visited) const {
	if (u == v) {
		printf("%d ", verList[v].ver);
		return true;
	}
	visited[v] = true;
    for (edgeNode * ptr = verList[v].head; ptr; ptr = ptr->next) {
		//cout << "u -- " << u << " v -- " << v << "ptr->end -- " << ptr->end << endl;
		if (!visited[ptr->end] && showPath(u, ptr->end, visited)) {
			printf("%d ", verList[v].ver);
			return true;
		}
    }
    visited[v] = false;
    return false;
}

// ------------------------------

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
