#include <iostream>
#include <cstdio>
#include <queue>
#include <string>
#include <vector>
#define MAX 50005

using namespace std;

struct nnode {
    long long ind;
    long long dif;
};

ostream & operator << (ostream & os, const struct nnode & n) {
    os << n.ind << "\t" << n.dif;
    return os;
}

typedef struct nnode node;

typedef struct {
    bool operator () (const node & n1, const node & n2) {
        return n1.dif > n2.dif;
    }
} comp;

int main () {
    string seq;
    priority_queue <node, vector<node>, comp> pq;

    cin >> seq;

    int cnt = 0;
    long long r, l;
    node n;
    long long cost = 0;
    for (int i = 0; i < (int)seq.size(); ++ i) {
        if (seq[i] == '(')
            ++ cnt;
        else {
            if (seq[i] == ')')
                -- cnt;
            else {
                seq[i] = ')';
                -- cnt;
                cin >> l >> r;
                n.ind = i;
                n.dif = (l - r);
                pq.push (n);
                cost += r;
            }
            if (cnt < 0) {
                if (pq.empty()) {
                    cout << -1 << endl;
                    return 0;
                }
                seq[pq.top().ind] = '(';
                cost += pq.top().dif;
                cnt += 2;
                pq.pop();
            }
        }
    }
    if (cnt > 0) {
        cout << -1 << endl;
        return 0;
    }
    cout << cost << endl;
    cout << seq << endl;

    return 0;
}