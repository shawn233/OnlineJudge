#include <iostream>
#include <cstdio>

using namespace std;

class myQueue {
private:
    int * data;
    int front, rear;
    int maxSize;

    void doubleSpace() {
        int * tmp = data;
        data = new int [2 * maxSize];
        for (int i = 1; i < maxSize; ++ i)
            data[i] = tmp[front+i];
        front = 0;
        rear = maxSize - 1;
        maxSize *= 2;
        delete [] tmp;
    }

public:
    myQueue(int initsize = 1000):front(0), rear(0), maxSize (initsize) {
        data = new int [maxSize];
    }

    ~myQueue () {
        delete [] data;
    }

    void enQueue (int x) {
        if ((rear+1)%maxSize == front)
            doubleSpace();
        rear = (rear+1)%maxSize;
        data[rear] = x;
    }

    int deQueue() {
        front = (front + 1)%maxSize;
        return data[front];
    }

    int getHead() {
        return data[(front+1)%maxSize];
    }

    bool isEmpty() {
        return front == rear;
    }
};

int main()
{
    myQueue bus, truck;
    int N, tmp, bus_cnt, truck_cnt, bus_tm, truck_tm, tm;
    int tmp_bus_cnt, tmp_truck_cnt, ferry_cnt;

    bus_cnt = truck_cnt = bus_tm = truck_tm = tm = 0;

    freopen("in.txt", "r", stdin);

    scanf("%d", &N);

    for (int i = 0; i < N; ++ i) {
        scanf("%d", &tmp);
        if (tmp) {
            scanf("%d", &tmp);
            ++ truck_cnt;
            truck.enQueue(tmp);
        } else {
            scanf("%d", &tmp);
            ++ bus_cnt;
            bus.enQueue(tmp);
        }
    }

    //cout << "done!" << endl;

    ferry_cnt = tmp_bus_cnt = tmp_truck_cnt = 0;
    while ((!bus.isEmpty())||(!truck.isEmpty())) {
        //cout << "tm -- " << tm << " ferry_cnt -- " << ferry_cnt << " tmp_bus_cnt -- " << tmp_bus_cnt << " tmp_truck_cnt -- " <<tmp_truck_cnt << endl;
        if (!bus.isEmpty() && bus.getHead() <= tm && ferry_cnt < 10 &&
            ((tmp_bus_cnt % 4 || (tmp_bus_cnt%4 == 0 && tmp_bus_cnt/4 == tmp_truck_cnt))
            ||(truck.isEmpty() || truck.getHead() > tm))) {
            //cout << "in-bus\n";
            bus_tm += (tm - bus.deQueue());
            ++ tmp_bus_cnt;
            ++ ferry_cnt;
        }
        if (!truck.isEmpty() && truck.getHead() <= tm && ferry_cnt < 10 &&
            ((tmp_bus_cnt % 4 == 0 && tmp_bus_cnt/4 > tmp_truck_cnt)
            ||(bus.isEmpty() || bus.getHead() > tm))) {
            //cout << "in-truck\n";
            truck_tm += (tm - truck.deQueue());
            ++ tmp_truck_cnt;
            ++ ferry_cnt;
        }
        if (ferry_cnt == 10 || ((bus.isEmpty() || bus.getHead() > tm) && (truck.isEmpty() || truck.getHead() > tm))) {
            //cout << "in-ferry\n";
            tm += 10;
            ferry_cnt = tmp_bus_cnt = tmp_truck_cnt = 0;
        }
    }

    printf("%.3f %.3f\n", double(bus_tm)/bus_cnt, double(truck_tm)/ truck_cnt);

    fclose(stdin);

    return 0;
}
