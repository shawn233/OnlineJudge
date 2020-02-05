#include <iostream>
#include <cstdio>
#include <algorithm>
#define MAX 100000

using namespace std;

struct Data {
    int employees[MAX];
    int cur_size, dif, min_pay, total_leave;

    Data (int mm): cur_size(0), dif(0), min_pay(mm), total_leave(0) {}

    void percolateUp(int ind) {
        employees[0] = employees[ind];
        for (; ind > 1 && employees[ind/2] > employees[0]; ind /= 2) {
            employees[ind] = employees[ind/2];
        }
        employees[ind] = employees[0];
    }

    void percolateDown (int ind) {
        employees[0] = employees[ind];
        for (int child = 0; ind * 2 <= cur_size; ind = child) {
            child = ind * 2;
            if (child < cur_size && employees[child] > employees[child+1])
                ++ child;
            if (employees[child] < employees[0]) {
                employees[ind] = employees[child];
            } else
                break;
        }
        employees[ind] = employees[0];
    }

    int deleteMin () {
        int res = employees[1];
        employees[1] = employees[cur_size];
        -- cur_size;
        percolateDown(1);
        return res;
    }

    void buildHeap () {
        for (int i = cur_size/2; i > 0; -- i)
            percolateDown(i);
    }

    void insert (int num) {
        if (num < min_pay)
            return;
        ++ cur_size;
        employees[cur_size ] = num - dif;
        percolateUp(cur_size);
    }

    void increase (int num) {
        dif += num;
    }

    void decrease (int num) {
        dif -= num;
        while (cur_size > 0 && employees[1]+dif < min_pay) {
            deleteMin();
            ++ total_leave;
        }
    }

    int findK (int k) {
        if (k > cur_size)
            return -1;
        int tmp_size = cur_size;
        int tmp_num;
        k = cur_size - k + 1;
        for (int i = 1; i < k; ++ i) {
            tmp_num = deleteMin();
            employees[cur_size+1] = tmp_num;
        }
        tmp_num = employees[1];
        cur_size = tmp_size;
        buildHeap();
        return tmp_num+dif;
    }

    int findKBySort(int k) {
        if (k > cur_size)
            return -1;
        sort(begin(employees)+1, begin(employees)+cur_size+1, greater<int>());
        int ans = employees[k];
        buildHeap();
        return ans + dif;
    }

    int findKByQuickSelect(int k) {

    }

    int getLeave() {
        return total_leave;
    }

    void output1() {
        for (int i = 1; i <= cur_size; ++ i) {
            printf("%d ", employees[i]);
        }
        printf("\n");
    }
};
int main()
{
    int n, min_pay, tmp;
    char op;

    freopen("in.txt", "r", stdin);

    scanf("%d %d", &n, &min_pay);

    Data data(min_pay);

    for (int i = 0; i < n; ++ i) {
        do {
            scanf("%c", &op);
        } while (op == ' ' || op == '\n');
        scanf("%d", &tmp);
        switch(op) {
        case 'I':
            data.insert(tmp);
            break;
        case 'A':
            data.increase(tmp);
            break;
        case 'S':
            data.decrease(tmp);
            break;
        case 'F':
            printf("%d\n", data.findKBySort(tmp));
            break;
        default:
            printf("<error> unknown command\n");
        }
        //cout << data.cur_size << endl;
    }

    printf("%d\n", data.getLeave());

    fclose(stdin);

    return 0;
}
