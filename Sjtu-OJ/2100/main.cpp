#include <iostream>
#include <cstdio>
#define MAX 50050

using namespace std;

struct Node {
    int weight;
    Node * parent;
    Node (int w, Node * pt=NULL): weight(w), parent(pt) {}
};

class BinaryHeap {
private:
    Node ** arr;
    int currentSize, maxSize;

    void doubleSpace();
    void buildHeap();

    void percolateUp(int hole);
    void percolateDown(int hole);

public:
    explicit BinaryHeap(int capacity=100);
    explicit BinaryHeap(Node ** items, int n);
    ~BinaryHeap();

    void insert(Node * x);
    Node * getMin() const;
    void deleteMin();
    void clear();

    bool isEmpty() const;
};

int findParentPath(Node * node, Node * root) {
    int ans = 0;
    while (node != root) {
        ++ ans;
        node = node->parent;
    }
    return ans;
}

long long encoder(int * w, int sz) {
    long long ans = 0;
    Node * root=NULL, *p1, *p2, *p3;
    Node * leafnodes[MAX];
    for (int i = 0; i < sz; ++ i)
        leafnodes[i] = new Node (w[i]);
    BinaryHeap heap(leafnodes, sz);
    while (1) {
        p1 = heap.getMin();
        heap.deleteMin();
        if (heap.isEmpty())
            break;
        p2 = heap.getMin();
        heap.deleteMin();

        p3 = new Node (p1->weight + p2->weight);
        p1->parent = p2->parent = p3;
        heap.insert(p3);
    }

    root = p1;

    for (int i = 0; i < sz; ++ i) {
        ans += (leafnodes[i]->weight * findParentPath(leafnodes[i], root));
    }

    return ans;
}

//-----------------------------------------------

int main () {
    int N;
    int f[MAX];

    scanf("%d", &N);
    for (int i = 0; i < N; ++ i)
        scanf("%d", &f[i]);

    printf("%lld\n", encoder(f, N));

    return 0;
}

//-----------------------------------------------

void BinaryHeap::doubleSpace() {
    Node ** tmp = new Node *[2 * maxSize];
    for (int i = 1; i <= currentSize; ++ i) {
        tmp[i] = arr[i];
    }
    maxSize *= 2;
    delete [] arr;
    arr = tmp;
}

void BinaryHeap::buildHeap() {
    for (int i = currentSize/2; i > 0; -- i)
        percolateDown(i);
}

void BinaryHeap::percolateDown(int hole) {
    int child;
    Node * tmp = arr[hole];
    for (; 2 * hole <= currentSize; hole=child) {
        child = 2 * hole;
        if (child != currentSize && arr[child+1]->weight < arr[child]->weight)
            ++ child;
        if (arr[child]->weight < tmp->weight)
            arr[hole] = arr[child];
        else
            break;
    }
    arr[hole] = tmp;
}

void BinaryHeap ::percolateUp(int hole) {
    Node * tmp = arr[hole];
    for (; hole > 1 && tmp->weight < arr[(hole>>1)]->weight; hole = (hole>>1)) {
        arr[hole] = arr[(hole>>1)];
    }
    arr[hole] = tmp;
}

BinaryHeap::BinaryHeap(int capacity):
    maxSize(capacity), currentSize(0) {
    arr = new Node *[maxSize];
}

BinaryHeap::BinaryHeap(Node ** items, int n):
    maxSize(n+10), currentSize(n) {
    arr = new Node *[maxSize];
    for (int i = 0; i < n; ++ i)
        arr[i+1] = items[i];
    buildHeap();
}

BinaryHeap::~BinaryHeap() {
    delete [] arr;
}

void BinaryHeap::insert(Node * x) {
    if (currentSize == maxSize - 1)
        doubleSpace();
    ++ currentSize;
    arr[currentSize] = x;
    percolateUp(currentSize);
}

Node * BinaryHeap::getMin() const {
    return arr[1];
}

void BinaryHeap::deleteMin() {
    arr[1] = arr[currentSize];
    -- currentSize;
    percolateDown(1);
}

void BinaryHeap::clear() {
    currentSize = 0;
}

bool BinaryHeap::isEmpty() const {
    return currentSize == 0;
}
