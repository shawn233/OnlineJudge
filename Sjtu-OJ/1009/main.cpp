#include <iostream>
#include <cstdio>
#include <iomanip>

using namespace std;

struct op {
    int t, amount, type;
};

int abs(int sth) {
    return (sth>0)?sth:-sth;
}

int main()
{
    int m, n;
    int init_tm, init_pc, tm, pc, ind;
    op ops[50];
    long double ans = 0;

    freopen("in", "r", stdin);

    scanf("%d", &m);
    for (int i = 0; i < m; ++ i) {
        scanf("%d %d %d", &ops[i].t, &ops[i].amount, &ops[i].type);
    }

    scanf("%d", &n);
    ind = 0;
    scanf("%d %d", &init_tm, &init_pc);
    for (int i = 1; i < n; ++ i) {
        scanf("%d %d", &tm, &pc);
        if(ind < m) {
            if(ops[ind].t >= tm) {
                init_pc = pc;
                init_tm = tm;
                continue;
            }
        } else {
            break;
        }

        long double sale = ops[ind].amount * 100 * init_pc;
        ans -= (max(0.002*sale, (long double)5)+0.1*ops[ind].amount+1);
        if(ops[ind].type == 1) {
            //buy
            ans -= sale;

        } else {
            //sell
            ans += sale;
            ans -= 0.001*sale;
        }

        ++ ind;
    }

    for (; ind < m; ++ ind) {
        long double sale = ops[ind].amount * 100 * init_pc;
        ans -= (max(0.002*sale, (long double)5)+0.1*ops[ind].amount+1);
        if(ops[ind].type == 1) {
            //buy
            ans -= sale;

        } else {
            //sell
            ans += sale;
            ans -= 0.001*sale;
        }
    }

    printf("%.2Lf\n", ans);

    fclose(stdin);

    return 0;
}
