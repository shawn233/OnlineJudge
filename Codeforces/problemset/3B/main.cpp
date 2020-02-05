#include <iostream>
#include <cstdio>
#include <algorithm>
#define MAX_N 100005

using namespace std;

typedef struct {
    int i;
    int w; // weight
    int v; // value
    double r; // ratio
} boat;

bool comp (boat b1, boat b2) {
    return b1.r > b2.r;
}

int main () {
    int n, weight;
    boat b[MAX_N];

    cin >> n >> weight;
    for (int i = 0; i < n; ++ i) {
        cin >> b[i].w >> b[i].v;
        b[i].i = i + 1;
        b[i].r = (double)b[i].v / b[i].w;
    }

    sort (b, b+n, comp);

    int ind = 0; // index
    int res = 0; // result
    int res_num [MAX_N];
    int res_num_ind = 0;
    int min_ind; // object of weight 1, minimum value
    while (ind != n && weight > 1) {
        weight -= b[ind].w;
        res += b[ind].v;
        res_num[res_num_ind ++] = b[ind].i;
        if (b[ind].w == 1)
            min_ind = ind;
        ++ ind;
    }
    
    if (weight == 1) {
        int next_w2 = -1, next_w1 = -1; // next object of certain weight
        while (ind < n && (next_w2 == -1 || next_w1 == -1)) {
            if (b[ind].w == 1 && next_w1 == -1)
                next_w1 = ind;
            if (b[ind].w == 2 && next_w2 == -1)
                next_w2 = ind;
            ind ++;
        }
        //cout << "next_w1: " << next_w1 << " next_w2: " << next_w2 << endl; 
        
        if (next_w1 == -1 && next_w2 == -1) {
            //cout << "0" << endl;
            ;
        } else if (next_w1 == -1) {
            //cout << "1" << endl;
            if (b[min_ind].v < b[next_w2].v) {
                res = res + b[next_w2].v - b[min_ind].v;
                cout << res << endl;
                for (int i = 0; i < res_num_ind; ++ i) {
                    if (res_num[i] == b[min_ind].i)
                        continue;
                    cout << res_num[i] << " ";
                }
                cout << b[next_w2].i << endl;
                return 0;
            }
        } else if (next_w2 == -1) {
            //cout << "2" << endl;
            res += b[next_w1].v;
            cout << res << endl;
            for (int i = 0; i < res_num_ind; ++ i) {
                cout << res_num[i] << " ";
            }
            cout << b[next_w1].i << endl;
            return 0;
        } else {
            if (b[min_ind].v + b[next_w1].v < b[next_w2].v) {
                //cout << "3" << endl;
                res = res + b[next_w2].v - b[min_ind].v;
                cout << res << endl;
                for (int i = 0; i < res_num_ind; ++ i) {
                    if (res_num[i] == b[min_ind].i)
                        continue;
                    cout << res_num[i] << " ";
                }
                cout << b[next_w2].i << endl;
                return 0;
            } else {
                //cout << "4" << endl;
                res += b[next_w1].v;
                cout << res << endl;
                for (int i = 0; i < res_num_ind; ++ i) {
                    cout << res_num[i] << " ";
                }
                cout << b[next_w1].i << endl;
                return 0;
            }
        }
    }
    cout << res << endl;
    for (int i = 0; i < res_num_ind; ++ i) {
        cout << res_num[i] << " ";
    }
    cout << endl;

    return 0;
}