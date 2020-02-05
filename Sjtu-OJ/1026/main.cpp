#include <iostream>
#include <cstdio>
#include <cstring>
#include <string>
#define MAX 10010

using namespace std;

struct BigInt {
    int arr[MAX];
    int len;
    BigInt() {
        memset(arr, 0, sizeof(arr));
        len = 1;
    }
    BigInt(int num) {
        memset(arr, 0, sizeof(arr));
        len = 0;
        if(num == 0)
            len = 1;
        while(num > 0) {
            arr[len] = num % 10;
            num /= 10;
            ++ len;
        }
    }
    //This is tricky | Now BigInt can process input like 010 | This is why my submission is stuck...
    BigInt(const string & str) {
        memset(arr, 0, sizeof(arr));
        len = str.size();
        //Ignore beginning zeros in the input
        for (int i = 0; i < len && str[i] == '0'; ++ i)
            -- len;
        for (int i = 0; i < len; ++ i)
            arr[i] = str[str.size()-i-1]-'0';
    }
    BigInt(const BigInt & obj) {
        memcpy(arr, obj.arr, sizeof(arr));
        len = obj.len;
    }
    void show() {
        for (int i = len - 1; i >= 0; -- i)
            printf("%d", arr[i]);
    }
};

bool operator<(BigInt & num1, BigInt & num2) {
    if (num1.len < num2.len)
        return true;
    if (num1.len > num2.len)
        return false;
    for (int i = num1.len-1; i >= 0; -- i) {
        if (num1.arr[i] < num2.arr[i])
            return true;
        if (num1.arr[i] > num2.arr[i])
            return false;
    }
    return false;
}

BigInt operator/(BigInt & num1, BigInt & num2) {
    BigInt ans;
    int carry;
    if(num1 < num2)
        return ans;
    int dif = num1.len-num2.len+1;//?
    ans.len = dif;
    for (int i = dif-1; i >= 0; -- i) {
        BigInt tmp;
        tmp.len = num2.len + i;
        for (int j = 0; j < num2.len; ++ j)
            tmp.arr[i+j] = num2.arr[j];
        while(!(num1 < tmp)) {
            ++ ans.arr[i];
            carry = 0;
            for (int t = i; t < num1.len; ++ t) {
                int temp = num1.arr[t] - tmp.arr[t] + carry;
                carry = 0;
                while (temp < 0) {
                    carry = -1;
                    temp += 10;
                }
                num1.arr[t] = temp;
            }
            for (int t = num1.len-1; num1.len > 0 && num1.arr[t] == 0; -- t)
                -- num1.len;
        }
    }
    for (int i = ans.len-1; ans.len > 0  && ans.arr[i] == 0; -- i)
        -- ans.len;
    return ans;
}

int main()
{
    string num1, num2;

    freopen("in", "r", stdin);

    cin >> num1 >> num2;
    BigInt n1(num1), n2(num2);
    (n1/n2).show();

    fclose(stdin);

    return 0;
}
