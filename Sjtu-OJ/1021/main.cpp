#include <iostream>
#include <iomanip>
#include <cstdio>
#define MAX 150

using namespace std;

int func (int (* arr)[150] , int n, int w, int val) {
    arr[n][n] = val;
    //cout << "val -- " << val << " n -- " << n << " w -- " << w << endl;
    for(int i = 1; i < w; ++ i)
        arr[n][n+i] = arr[n][n+i-1]+1;
    for (int i = 1; i < w; ++ i)
        arr[n+i][n+w-1] = arr[n+i-1][n+w-1]+1;
    for (int i = 1; i < w; ++ i)
        arr[n+w-1][n+w-1-i] = arr[n+w-1][n+w-i]+1;
    for (int i = 1; i < w-1; ++ i)
        arr[n+w-1-i][n] = arr[n+w-i][n] + 1;
    return arr[n+1][n];
}


int main()
{
    int N, val = 0;
    int arr[MAX][MAX];
    scanf("%d", &N);

    for (int i = 0; i <= (N-1)/2; ++ i) {
        val = func(arr, i, N-2*i, val+1);
    }

    for (int i = 0; i < N; ++ i) {
        for (int j = 0; j < N; ++ j)
            cout << setw(6) << arr[i][j];
        cout << endl;
    }

    return 0;
}
