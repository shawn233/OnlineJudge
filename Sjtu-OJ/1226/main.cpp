#include <iostream>
#include <cstdio>

using namespace std;

inline void swap_(int & n1, int &n2) {
    int tmp = n1;
    n1 = n2;
    n2 = tmp;
}

int median3 (int * arr, int left, int right) {
    int center = (left + right) / 2;
    if (arr[center] < arr[left])
        swap_(arr[left], arr[center]);
    if (arr[right] < arr[left])
        swap_(arr[right], arr[left]);
    if (arr[right] < arr[center])
        swap_(arr[right], arr[center]);

    swap_(arr[right-1], arr[center]);
    return arr[right-1];
}

void quickSort(int * arr, int left, int right) {
    //cout << "left -- " << left << " right -- " << right << endl;

    if (left == right - 1) {
        if (arr[right] < arr[left])
            swap(arr[left], arr[right]);
        return;
    } else if (right <= left)
        return;

    int pivot = median3(arr, left, right);
    int i = left, j = right-1;

    while(1) {
        while(arr[++i] < pivot);
        while (arr[--j] > pivot);
        if (i < j)
            swap_(arr[i], arr[j]);
        else
            break;
    }

    swap_(arr[i], arr[right-1]);

    quickSort(arr, left, i-1);
    quickSort(arr, i+1, right);
}

void quickSort(int * arr, int n) {
    quickSort(arr, 0, n-1);
}

int main()
{
    int * arr, n;

    scanf("%d", &n);
    arr = new int [n];

    for (int i = 0; i < n; ++ i)
        scanf("%d", &arr[i]);

    quickSort(arr, n);

    for (int i = 0; i < n; ++ i)
        printf("%d ", arr[i]);

    delete [] arr;
    return 0;
}
