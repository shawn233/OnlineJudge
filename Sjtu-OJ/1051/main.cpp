#include <iostream>
#include <cstdio>
#define MAX 10005

using namespace std;

struct Node {
    int val;
    Node * next;
    Node (int v): val(v), next(NULL) {}
};

int main()
{
    long long cnt = 0;
    int n, m, tmp;
    Node * head, *rear, *ptr;

    head = new Node (0);
    rear = head;

    freopen("in.txt", "r", stdin);

    scanf("%d", &n);
    for (int i = 0; i < n; ++ i) {
        scanf("%d", &tmp);
        rear->next = new Node (tmp);
        rear = rear->next;
    }

    scanf("%d", &m);
    for (int i = 0; i < m; ++ i) {
        scanf("%d", &tmp);
        for (ptr = head->next; ptr != NULL && ptr->val != tmp; ptr = ptr->next, ++ cnt);
        if (ptr != NULL) {
            ++ cnt;
            if (ptr->next != NULL) {
                ptr->val = ptr->next->val;
                rear = ptr->next;
                ptr->next = rear->next;
                delete rear;
            } else {
                for (rear = head; rear->next != ptr; rear = rear->next);
                delete ptr;
                rear->next = NULL;
            }
            rear = head->next;
            head->next = new Node (tmp);
            head->next->next = rear;
        }
    }

    cout << cnt << endl;

    fclose(stdin);

    return 0;
}
