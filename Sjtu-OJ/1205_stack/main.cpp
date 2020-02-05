#include <iostream>
#include <cstdio>

using namespace std;

class myStack {
private:
    int * data;
    int tp;
    int maxSize;

    void doubleSize() {
        int * ptr = new int [2*maxSize];
        for (int i = 0; i < maxSize; ++ i)
            ptr[i] = data[i];
        delete [] data;
        data = ptr;
        maxSize *= 2;
    }

public:
    myStack(int initSize = 1000): maxSize(initSize), tp(-1) {
        data = new int[maxSize];
    }

    ~myStack() {delete [] data;}

    void push (int x) {
        if (tp == maxSize - 1)
            doubleSize();
        data[++tp] = x;
    }

    int pop () {
        return data[tp--];
    }

    int top () const {
        return data[tp];
    }

    bool isEmpty() const {
        return (tp == -1);
    }
};

int ack (int m, int n) {
    myStack stm, stn;
    int mm, nn;
    stm.push(m);
    stn.push(n);
    while (!stm.isEmpty()) {
        mm = stm.pop();
        nn = stn.pop();
        if (mm > 0 && nn > 0) {
            stm.push(mm-1);
            stm.push(mm);
            stn.push(nn-1);
        } else if (mm > 0 && nn == 0) {
            stm.push(mm-1);
            stn.push(1);
        } else if (mm == 0) {
            stn.push(nn+1);
        } else {
            printf("[error] m = %d is negative, while n = %d\n", mm, nn);
        }
    }
    return stn.pop();
}

int main()
{
    int m, n;
    scanf ("%d %d", &m, &n);

    printf("%d\n", ack(m, n));

    return 0;
}
