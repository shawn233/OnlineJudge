#include <iostream>
#include <algorithm>
#define MAX 5002

using namespace std;

struct env_struct {
    int w;
    int h;
    int ind;

    bool operator < (const struct env_struct & a) {
        if (w == a.w)
            return h < a.h;
        return w < a.w;
    }
};

typedef struct env_struct env;

int main () {
    int dp[MAX];
    int print[MAX];
    env e[MAX];
    int ans [MAX];
    int n, w, h;
    int tmp, start_i, tmp_i;

    cin >> n >> w >> h;

    for (int i = 0; i < n; ++ i) {
        cin >> e[i].w >> e[i].h;
        e[i].ind = i + 1;
    }

    sort (begin(e), begin(e) + n);

    for (start_i = 0; start_i < n; ++ start_i) {
        if (w < e[start_i].w && h < e[start_i].h)
            break;
    }
    if (start_i == n) {
        cout << 0 << endl;
        return 0;
    }

    for (int i = start_i; i < n; ++ i) {
        tmp = 0;
        tmp_i = -1;
        if (e[i].w <= w || e[i].h <= h) {
            dp[i] = -1;
            print[i] = -1;
            continue;
        }
        for (int j = start_i; j < i; ++ j) {
            if (e[j].h < e[i].h && e[j].w < e[i].w && dp[j] > tmp) {
                tmp = dp[j];
                tmp_i = j;
            }
        }
        dp[i] = tmp + 1;
        print [i] = tmp_i;
    }

    cout << dp[n-1] << endl;
    
    tmp_i = 0;
    tmp = n-1;
    while (tmp != -1) {
        ans[tmp_i ++] = e[tmp].ind;
        tmp = print[tmp];
    }
    for (int i = tmp_i - 1; i >= 0; -- i) {
        cout << ans[i];
        if (i != 0)
            cout << " ";
    }
    cout << endl;


    return 0;
}