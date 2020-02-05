#include <iostream>
#include <cstdio>
#include <cstring>

#define MAX 50000

using namespace std;

class OutOfBound {};

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

class BinaryTree {
private:
    int left[MAX], right[MAX];
    int n, root;

    bool findPath(int x, seqStack<int> & res_st) {
		seqStack<int> st, cnt_st;
		int tmp, cnt;

		st.push(root);
		cnt_st.push(0);
		while (!st.isEmpty()) {
			tmp = st.top();
            cnt = cnt_st.pop();
            if (tmp == x)
				break;
            switch(cnt) {
			case 0:
				cnt_st.push(1);
				if (left[tmp]) {
					st.push(left[tmp]);
					cnt_st.push(0);
				}
				break;
			case 1:
				cnt_st.push(2);
				if (right[tmp]) {
					st.push(right[tmp]);
					cnt_st.push(0);
				}
				break;
			case 2:
				st.pop();
				break;
            }
		}

		if (st.isEmpty()) {
			printf("[warning] cannot find %d in this tree\n", x);
			return false;
		} else {
            while (!st.isEmpty())
				res_st.push(st.pop());
			return true;
		}
    }

public:
    BinaryTree(int N): n(N), root(0) {}

    void initialize() {
    	int isroot[MAX];
    	memset(isroot, n, 0);
        for (int i = 1; i <= n; ++ i) {
            scanf("%d %d", &left[i], &right[i]);
            isroot[left[i]] = isroot[right[i]] = 1;
        }
        for (root = 1; root <= n; ++ root) {
			if (!isroot[root])
				break;
        }
    }

    int findCommonAncestor (int x, int y) {
    	seqStack<int> x_st, y_st;
    	int tmp_x, tmp_y;
    	findPath(x, x_st);
    	findPath(y, y_st);
		while (!x_st.isEmpty() && !y_st.isEmpty()) {
			if (x_st.top() != y_st.top())
				break;
			tmp_x = x_st.pop();
			tmp_y = y_st.pop();
		}
		return tmp_x;
    }
};

int main()
{
    int N, X, Y;

    freopen("in.txt", "r", stdin);

    scanf("%d %d %d", &N, &X, &Y);
    BinaryTree tree(N);
    tree.initialize();
    printf("%d\n", tree.findCommonAncestor(X, Y));

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

