#include <iostream>
#include <cstdio>
#include <string>
#define MAX 100005

using namespace std;

struct Plane {
    int id, height;
    Plane (int idd, int h): id(idd), height(h) {}
    Plane():id(-1), height(-1) {}
};

bool isLessThan(Plane & p1, Plane & p2) {
    if (p1.height > p2.height) {
        return false;
    } else if(p1.height < p2.height) {
        return true;
    } else {
        if (p1.id < p2.id) {
            return true;
        } else if(p1.id > p2.id) {
            return false;
        } else {
            //printf("<error> two planes are the same");
            return false;
        }
    }
}

class MinHeap {
private:
    Plane planes[MAX];
    int index[MAX]; //plane id->index
    int cur_size;
    void percolate_up(Plane pl) {
        int hole = index[pl.id];
        int child = (hole-1)/2;
        for (; child >= 0 && isLessThan(pl, planes[child]);) {
            planes[hole] = planes[child];
            index[planes[hole].id] = hole;
            hole = child;
            child = (hole-1)/2;
            if (hole == 0)
                break;
        }
        planes[hole] = pl;
        index[pl.id] = hole;
    }

    void percolate_down(Plane pl) {
        int hole = index[pl.id];
        int child = 2*hole+1;
        for (; child < cur_size; hole = child) {
            if (child != cur_size-1 && isLessThan(pl, planes[child]))
                ++ child;
            if (isLessThan(planes[child], pl)) {
                index[planes[child].id] = hole;
                planes[hole] = planes[child];
            } else
                break;
        }
        planes[hole] = pl;
        index[pl.id] = hole;
    }

    int findMin(int x, int ind) {
        if (ind >= cur_size) {
            return -1;
        }
        if (planes[ind].height > x) {
            return ind;
        } else {
            int l_r = findMin(x, 2*ind+1);
            int r_r = findMin(x, 2*ind+2);
            if (l_r != -1 && r_r != -1) {
                if (isLessThan(planes[l_r], planes[r_r])) {
                    return l_r;
                } else {
                    return r_r;
                }
            } else if(l_r == -1 && r_r == -1) {
                return -1;
            } else if(l_r == -1) {
                return r_r;
            } else if (r_r == -1) {
                return l_r;
            } else {
                printf("<error> unexpected\n");
                return -1;
            }
        }
    }

public:
    MinHeap():cur_size(0) {}
    void insert(Plane & pl) {
        index[pl.id] = cur_size;
        percolate_up(pl);
        ++ cur_size;
    }

    Plane findMin(int x) {
        return planes[findMin(x, 0)];
    }

    void decrease(int i, int j) {
        int ind = index[i];
        planes[ind].height -= j;
        percolate_up(planes[ind]);
    }
};

int main()
{
    int n, tmp;
    MinHeap heap;
    string cmd;

    freopen("in.txt", "r", stdin);

    scanf("%d", &n);
    for (int i = 1; i <= n; ++ i) {
        scanf("%d", &tmp);
        Plane pl (i, tmp);
        heap.insert(pl);
    }

    while (cin >> cmd) {
        if (cmd == "findmin") {
            scanf("%d", &tmp);
            printf("%d\n", heap.findMin(tmp).id);
        } else if(cmd == "decrease") {
            scanf("%d %d", &n, &tmp);
            heap.decrease(n, tmp);
        }
    }

    fclose(stdin);

    return 0;
}
