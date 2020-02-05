#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#define MAX 100005

using namespace std;

int main() {
    int n;
    int t[MAX];

    //freopen("in.txt", "r", stdin);

    cin >> n;
    for (int i = 0; i < n; ++ i) cin >> t[i];

    int t_all = 0;
    for (int i = 0; i < n; ++ i) t_all += t[i];

    double t_half = (double)t_all / 2;
    int t_alice = 0, n_alice = 0;
    for (int i = 0; i < n && t_alice + t[i] <= t_half; ++ i, ++ n_alice) t_alice += t[i];
    int t_bob = t_all - t[n_alice] - t_alice;
    int n_bob = n - n_alice - 1;
    if (t_alice < t_bob) ++ n_alice;
    else if (t_bob < t_alice) ++ n_bob;
    else ++ n_alice;
    
    printf("%d %d\n", n_alice, n_bob);
    //fclose(stdin);

    return 0;
}