#include <iostream>
#include <cstdio>

using namespace std;

class OutOfBound {};

template <class elemType>
class seqStack{
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

class adjListGraph {
private:

    struct edgeNode {
        int end;
        edgeNode * next;
        int weight;

        edgeNode (int e, int w, edgeNode * nt = NULL): end(e), weight(w), next(nt) {}
    };

	struct verNode {
		int ver;
        edgeNode * head;

        verNode (int v=-1, edgeNode * h=NULL): ver(v), head(h) {}

	};

	struct pathNode {
        int ver, dis, last_visit;
        pathNode(int v=-1, int d=-1, int lv=-1):ver(v), dis(d), last_visit(lv) {}
	};

	int vers, edges;
	verNode * verList;

public:

    adjListGraph(int v): vers(v), edges(0) {
        verList = new verNode [v];
    }

    ~adjListGraph() {
        edgeNode * tmp;
        for (int i = 0; i < vers; ++ i) {
            tmp = verList[i].head;
            while (tmp) {
                verList[i].head = tmp->next;
                delete tmp;
                tmp = verList[i].head;
            }
        }
        delete [] verList;
    }

    bool insert(int u, int v, int w) {
        if (u < 0 || u >= vers || v < 0 || v >= vers)
            return false;
        verList[u].head = new edgeNode (v, w, verList[u].head);
        return true;
    }

    int countPath(int start, int M) {
        bool * isvisited = new bool[vers];
        seqStack<pathNode> st;
        edgeNode * edge;
        pathNode path_node(start, 0);
        int ans = 0;

        st.push(path_node);
        //isvisited[start] = true;

        while (!st.isEmpty()) {
            //cout << "1" << endl;
            path_node = st.pop();
            //cout << "ver -- " << path_node.ver << " dis -- " << path_node.dis << " last_visit -- " << path_node.last_visit << endl;
            if (path_node.dis == M) {
                isvisited[path_node.ver] = false;
                ++ ans;
                continue;
            }
            isvisited[path_node.ver] = true;
            edge = verList[path_node.ver].head;
            if (path_node.last_visit != -1) {
                while (edge && (edge->end != path_node.last_visit)) {
                    //cout << "2" << endl;
                    edge = edge->next;
                }
                edge = edge->next;
            }
            while (edge) {
                //cout << "3" << endl;
                //cout << "EDGE | end -- " << edge->end << endl;
                if (!isvisited[edge->end]){
                    path_node.last_visit = edge->end;
                    st.push(path_node);
                    path_node.ver = edge->end;
                    path_node.dis += 1;
                    path_node.last_visit = -1;
                    st.push(path_node);
                    break;
                }
                edge = edge->next;
            }
            if (edge == NULL) {
                isvisited[path_node.ver] = false;
            }
        }

        return ans;
    }
};

// ------------------------------------

int main()
{
    int n, m, start, M, a, b;

    freopen("in.txt", "r", stdin);

    scanf("%d %d %d %d", &n, &m, &start, &M);

    adjListGraph g(n);

    for (int i = 0; i < m; ++ i) {
        scanf("%d %d", &a, &b);
        g.insert(a-1, b-1, 1);
    }

    printf("%d\n", g.countPath(start-1, M));

    fclose(stdin);

    return 0;
}

// -----------------------------------

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
