#include <iostream>
#include <cstdio>
#define MAX 10000

using namespace std;

void quickSort(int *arr, int left, int right) {
    if (left >= right)
        return;
    int l = left, r = right, tmp = arr[left];
    while (l < r) {
        while (l < r && arr[r]>=tmp)
            --r;
        arr[l] = arr[r];
        while (l < r && arr[l]<= tmp)
            ++ l;
        arr[r] = arr[l];
    }
    arr[l] = tmp;
    quickSort(arr, left, l-1);
    quickSort(arr, l+1, right);
}

int main()
{
    int N, M;
    int n[MAX], m[MAX];

    freopen("in.txt", "r", stdin);

    scanf("%d %d", &N, &M);
    for (int i = 0; i < N; ++ i)
        scanf("%d", &n[i]);
    for (int j = 0; j < M; ++ j)
        scanf("%d", &m[j]);

    quickSort(n, 0, N-1);
    quickSort(m, 0, M-1);
/*
    for (int i = 0; i < N; ++ i)
        cout << n[i] << " ";
    cout << endl;
    for (int j = 0; j < M; ++ j)
        cout << m[j] << " ";
    cout <<endl;
*/
    int ind = M-1;
    int ans = 0;
    for (int i = N-1; i >= 0; -- i ) {
        if (ind == -1)
            ans += 1;
        else {
            while (ind >= -1 && m[ind] >= n[i])
                -- ind;
            if (ind != -1) {
                -- ind ;
                ans += 2;
            } else {
                ans += 1;
            }
        }
    }

    printf("%d\n", ans);

    fclose(stdin);
    return 0;
}
