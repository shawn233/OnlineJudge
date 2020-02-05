#include <iostream>
#include <cstdio>

using namespace std;

template <class T>
class BinaryHeap {
protected:
    T * arr;
    int currentSize, maxSize;

    void doubleSpace();
    void buildHeap();

    void percolateUp(int hole);
    void percolateDown(int hole);

public:
    explicit BinaryHeap(int capacity=100);
    explicit BinaryHeap(const T * items, int n);
    ~BinaryHeap();

    void insert(const T & x);
    const T & getMin() const;
    void deleteMin();
    void clear();

    bool isEmpty() const;
};

class PriorityQueue: public BinaryHeap<int> {
public:
    PriorityQueue(int initsize=100):
        BinaryHeap(initsize) {}

    int findx(int x) {
        int ans = -1;
        int tmp = (1 << 31) - 1;
        for (int i = 1; i <= currentSize; ++ i) {
            if (arr[i] > x && arr[i] < tmp) {
                ans = i;
                tmp = arr[i];
            }
        }
        return ans;
    }

    void decreaseKey(int pos, int amt) {
        arr[pos] -= amt;
        percolateUp(pos);
    }
};

//-----------------------------------------------------

int main()
{
    PriorityQueue q;
    int M, tmp, tmp0;
    char cmd[10];

    freopen("in.txt", "r", stdin);

    scanf("%d", &M);
    for (int i = 0; i < M; ++ i) {
        cin >> cmd;
        switch(cmd[0]) {
        case 'i':
            cin >> tmp;
            q.insert(tmp);
            break;
        case 'f':
            cin >> tmp;
            printf("%d\n", q.findx(tmp));
            break;
        case 'd':
            cin >> tmp >> tmp0;
            q.decreaseKey(tmp, tmp0);
            break;
        default:
            printf("[error] unknown command\n");
        }
    }

    fclose(stdin);

    return 0;
}

//-----------------------------------------------------

template <class T>
void BinaryHeap<T>::doubleSpace() {
    T * tmp = new T[2 * maxSize];
    for (int i = 1; i <= currentSize; ++ i) {
        tmp[i] = arr[i];
    }
    maxSize *= 2;
    delete [] arr;
    arr = tmp;
}

template <class T>
void BinaryHeap<T>::buildHeap() {
    for (int i = currentSize/2; i > 0; -- i)
        percolateDown(i);
}

template <class T>
void BinaryHeap<T>::percolateDown(int hole) {
    int child;
    T tmp = arr[hole];
    for (; 2 * hole <= currentSize; hole=child) {
        child = 2 * hole;
        if (child != currentSize && arr[child+1] < arr[child])
            ++ child;
        if (arr[child] < tmp)
            arr[hole] = arr[child];
        else
            break;
    }
    arr[hole] = tmp;
}

template <class T>
void BinaryHeap <T>::percolateUp(int hole) {
    T tmp = arr[hole];
    for (; hole > 1 && tmp < arr[(hole>>1)]; hole = (hole>>1)) {
        arr[hole] = arr[(hole>>1)];
    }
    arr[hole] = tmp;
}

template <class T>
BinaryHeap<T>::BinaryHeap(int capacity):
    maxSize(capacity), currentSize(0) {
    arr = new T[maxSize];
}

template <class T>
BinaryHeap<T>::BinaryHeap(const T * items, int n):
    maxSize(n+10), currentSize(n) {
    arr = new T[maxSize];
    for (int i = 0; i < n; ++ i)
        arr[i+1] = items[i];
    buildHeap();
}

template <class T>
BinaryHeap<T>::~BinaryHeap() {
    delete [] arr;
}

template <class T>
void BinaryHeap<T>::insert(const T & x) {
    if (currentSize == maxSize - 1)
        doubleSpace();
    ++ currentSize;
    arr[currentSize] = x;
    percolateUp(currentSize);
}

template <class T>
const T & BinaryHeap<T>::getMin() const {
    return arr[1];
}

template <class T>
void BinaryHeap<T>::deleteMin() {
    arr[1] = arr[currentSize];
    -- currentSize;
    percolateDown(1);
}

template <class T>
void BinaryHeap<T>::clear() {
    currentSize = 0;
}

template <class T>
bool BinaryHeap<T>::isEmpty() const {
    return currentSize == 0;
}
