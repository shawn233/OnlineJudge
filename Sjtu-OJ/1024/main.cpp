#include <iostream>
#include <cstdio>

using namespace std;

void qsort(int * arr, int left, int right) {
    if (left >= right )
        return;
    int mid = arr[left];
    int orig_left = left, orig_right = right;
    while(left < right) {
        while(left < right && arr[right] >= mid)
            -- right;
        arr[left] = arr[right];
        while(left < right && arr[left] <= mid)
            ++ left;
        arr[right] = arr[left];
    }

    arr[left] = mid;

    qsort(arr, orig_left, left - 1);
    qsort(arr, left + 1, orig_right);
}

int main()
{
    int n;
    int arr[10000];

    freopen("in", "r", stdin);

    scanf("%d", &n);
    for (int i = 0; i < n; ++ i)
        scanf("%d", &arr[i]);
    qsort(arr, 0, n-1);
    for (int i = 0; i < n; ++ i)
        printf("%d ", arr[i]);

    fclose(stdin);

    return 0;
}
