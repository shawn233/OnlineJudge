#include <iostream>
#include <cstdio>
#define INT 1000000000
#define MAX 200000

using namespace std;

struct Node {
    int val, pos;
    Node * next, * prev;
    Node (int v, int p): val(v), pos(p), next(NULL), prev(NULL) {}
};

class myqueue {
private:
    Node * head, * last;
    int width, ans;

public:
    myqueue(int k): width(k), ans(INT) {
        last = head = new Node (0, 0);
    }

    ~myqueue() {
        Node * ptr = head->next, *tmp;
        while(ptr != NULL) {
            tmp = ptr->next;
            delete ptr;
            ptr = tmp;
        }
        delete head;
    }

    void insertBack(int val, int pos, bool flag) {
        Node * tmp;
        while(last != head && last->val < val) {
            tmp = last->prev;
            delete last;
            last = tmp;
        }

        last->next = new Node(val, pos);
        last->next->prev = last;
        last = last->next;

        if(pos-head->next->pos >= width) {
            tmp = head->next;
            head->next = head->next->next;
            if (head->next != NULL)
                head->next->prev = head;
            delete tmp;
        }

        if (flag) {
            ans = min(ans, head->next->val);
        }
    }

    int getAns() {
        return ans;
    }
};

int main()
{
    int arr[MAX], n, k;

    freopen("in", "r", stdin);

    scanf("%d %d", &n, &k);
    for (int i = 0; i < n; ++ i)
        scanf("%d", &arr[i]);

    myqueue q(k);

    for (int i = 0; i < n; ++ i)
        q.insertBack(arr[i], i, i>=(k-1));

    for (int i = 0; i < k-1; ++ i)
        q.insertBack(arr[i], i+n, true);

    printf("%d\n", q.getAns());

    fclose(stdin);

    return 0;
}
