#include <iostream>
#include <cstdio>
#define MAX 1000010

using namespace std;

class BigInt {
private:
    struct node {
        int data;
        node * next;
        node ():next(NULL), data(0) {}
        node (int d, node * ptr): data(d), next(ptr) {}
    };
    node * head, * rear;
    int currentLength; //for faster speed

public:
    BigInt(): currentLength(0) {
        head = rear = new node;
    }
    ~BigInt() {
        node * ptr = head, * tmp;
        while (ptr != NULL) {
            tmp = ptr;
            ptr = ptr->next;
            delete tmp;
        }
    }

    int length () {
        return currentLength;
    }

    void push_back(int n) {
        rear->next = new node (n, NULL);
        rear = rear->next;
        ++ currentLength;
    }

    void loadNum(const char * num) {
        int i = 0, len = 0;
        if (num == NULL) {
            printf("[error] null pointer\n");
        }
        for (; num[len] != '\0'; ++ len);
        for (i = len-1; i >= 0; -- i) {
            push_back(num[i] - '0');
        }
    }

    void add(BigInt & num1, BigInt & num2) {
        int len = max(num1.currentLength, num2.currentLength);
        node * ptr1 = num1.head->next, * ptr2 = num2.head->next;
        int carry = 0, n1, n2;
        //cout << "len1 -- " << len1 << " len2 -- " << len2 << endl;
        for (int i = 0; i < len; ++i) {
            if (ptr1) {
                n1 = ptr1->data;
                ptr1 = ptr1->next;
            } else {
                n1 = 0;
            }
            if (ptr2) {
                n2 = ptr2->data;
                ptr2 = ptr2->next;
            } else {
                n2 = 0;
            }
            n1  = n1 + n2 + carry;
            carry = n1/10;
            n1 %= 10;
            push_back(n1);
        }
        if (carry) {
            push_back(carry);
        }
    }

    void show () {
        int tmp [currentLength];
        node * ptr = head->next;
        for (int i = currentLength - 1; i >= 0; -- i, ptr = ptr->next) {
            tmp[i] = ptr->data;
        }
        for (int i = 0; i < currentLength; ++ i) {
            printf("%d", tmp[i]);
        }
    }
};

void readline(char * str) {
    char ch;
    int i;
    for (i = 0;; ++ i) {
        scanf("%c", &ch);
        if (ch == '\n')
            break;
        else if (ch == ' ')
            continue;
        else {
            str[i] = ch;
        }
    }
    str[i] = '\0';
}

int main () {
    char num1[MAX], num2[MAX];
    BigInt n1, n2, n3;

    readline(num1);
    readline(num2);

    n1.loadNum(num1);
    n2.loadNum(num2);
    n3.add(n1, n2);
    n3.show();
    printf("\n");
    return 0;
}
