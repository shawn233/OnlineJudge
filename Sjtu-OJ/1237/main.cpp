#include <iostream>
#include <cstdio>

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


class adjListGraph {
private:
	int vers, edges;

	struct edgeNode {
		int end;
		edgeNode * next;
		edgeNode (int e, edgeNode * n=NULL):
			end(e), next(n) {}
	};

	struct verNode {
        int ver;
        edgeNode * head;
        verNode (int v=0, edgeNode * h=NULL):
        	ver(v), head(h) {}
	};

	verNode * verList;

public:
	adjListGraph (int v): vers(v), edges(0) {
		verList = new verNode [v];
	}

	~adjListGraph() {
		edgeNode * tmp;
		for (int i = 0; i < vers; ++ i) {
			while (verList[i].head) {
				tmp = verList[i].head;
				verList[i].head = tmp->next;
				delete tmp;
			}
		}
		delete [] verList;
	}

	void insert (int u, int v) {
		verList[u].head = new edgeNode(v, verList[u].head);
		++ edges;
	}

	int topo() {
		int * in_degree;
		int tmp, ans;
		bool * visited;
		edgeNode * edge;
		seqQueue <int> q;

		visited = new bool [vers];
		in_degree = new int[vers];

		for (int i = 0; i < vers; ++ i) {
			in_degree[i] = 0;
			visited[i] = false;
		}

		for (int i = 0; i < vers; ++ i) {
			edge = verList[i].head;
			while (edge) {
				++ in_degree[edge->end];
				edge = edge->next;
			}
		}

		for (int i = 0; i < vers; ++ i) {
			if (in_degree[i] == 0) {
				q.enQueue(i);
			}
		}

		ans = 0;
		while (!q.isEmpty()) {
			tmp = q.deQueue();
			edge = verList[tmp].head;
			visited [tmp] = true;
			while (edge) {
				-- in_degree[edge->end];
				edge = edge->next;
			}
			// This is critical, for that this ensures the semester is determined
			// only after the in-degree becomes 0.
			// If you attempt to determine the in-degree using the minimal path,
			// then you will encounter fault.
			if (q.isEmpty()) {
				++ ans;
				for (int i = 0; i < vers; ++ i) {
					if (!visited[i] && in_degree[i] == 0)
						q.enQueue(i);
				}
			}
		}

		delete [] in_degree;
		delete [] visited;

		return ans;
	}
};

int main()
{
	int n, m;
	int p, q;

	scanf("%d %d", &n, &m);

	adjListGraph g(n);

	for (int i = 0; i < m; ++ i) {
		scanf("%d %d", &p, &q);
		g.insert(q-1, p-1);
	}

	printf("%d\n", g.topo());

    return 0;
}

// -------------------------

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
