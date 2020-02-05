#include <iostream>
#include <cstdio>
#define MAX 10000

using namespace std;

int main()
{
    int M;
    long long K[MAX];
    int res = 0;

    freopen("in.txt", "r", stdin);

    scanf ("%d", &M);
    for (int i = 0; i < M-1; ++ i)
        cin >> K[i];

    for (int i = 2; i <= M; ++ i) {
        res = (res + K[M-i])%i;
    }

    printf("%d", res+1);

    fclose(stdin);

    return 0;
}
