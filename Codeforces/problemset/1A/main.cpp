#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cmath>

using namespace std;

int main () {
    int n, m, a;

    cin >> n >> m >> a;
    
    cout << (long long) ceil (double(n)/a) *  (long long) ceil (double (m)/a) << endl;

    return 0;
} 