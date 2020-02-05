#include <iostream>
#include <cstdio>
#define MOD 2010

using namespace std;

int fib[2][2] = {{1,1},{1,0}};
int res[2][2] = {{1,0},{0,1}};

void multiply(int mat1[2][2], int mat2[2][2]) {
    // mat1 *= mat2
    int mat00, mat01, mat10, mat11;
    mat00 = (mat1[0][0]*mat2[0][0])%MOD+(mat1[0][1]*mat2[1][0])%MOD;
    mat01 = (mat1[0][0]*mat2[0][1])%MOD+(mat1[0][1]*mat2[1][1])%MOD;
    mat10 = (mat1[1][0]*mat2[0][0])%MOD+(mat1[1][1]*mat2[1][0])%MOD;
    mat11 = (mat1[1][0]*mat2[0][1])%MOD+(mat1[1][1]*mat2[1][1])%MOD;
    mat1[0][0] = mat00;
    mat1[0][1] = mat01;
    mat1[1][0] = mat10;
    mat1[1][1] = mat11;
}

/*
void show(int mat[2][2]) {
    for (int i = 0; i < 2; ++ i) {
        for (int j = 0; j < 2; ++ j)
            cout << mat[i][j] << " ";
        cout << endl;
    }
}
*/

void calfib(long long n) {
    while (n != 0) {
        if(n&1) {
            multiply(res, fib);
        }
        multiply(fib,fib);
        n >>= 1;
    }
}

int main()
{
    long long n;

    scanf("%lld", &n);
    calfib(n-1);
    printf("%d\n", res[0][0]%MOD);

    return 0;
}
