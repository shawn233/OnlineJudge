#include <iostream>
#include <cstdio>
#include <sstream>
#define MAX 100

using namespace std;

struct Book {
    int num;
    Book * next;

    Book (int n): num(n), next(NULL) {}
};

class Shelf {
private:
    Book * arr[MAX], *rear[MAX];
    int n;

public:
    Shelf(int num): n(num) {
        for (int i = 0; i < n; ++ i) {
            arr[i] = new Book(0);
            rear[i] = arr[i];
        }
    }

    ~Shelf() {
        Book * ptr, * next_ptr;
        for(int i = 0; i < n; ++ i) {
            ptr = arr[i]->next;
            while(ptr != NULL) {
                next_ptr = ptr->next;
                delete ptr;
                ptr = next_ptr;
            }
            delete arr[i];
        }
    }

    void insert(int floor, int num) {
        //book <num> insert in the arr[<floor>]
        rear[floor]->next = new Book(num);
        rear[floor] = rear[floor]->next;
    }

    void move(int beg, int dest) {
        rear[dest]->next = arr[beg]->next;
        arr[beg]->next = NULL;
        rear[dest] = rear[beg];
        rear[beg] = arr[beg];
    }

    void show() {
        for (int i = 0; i < n; ++ i) {
            Book * ptr = arr[i]->next;
            while(ptr != NULL) {
                printf("%d ", ptr->num);
                ptr = ptr->next;
            }
            printf("\n");
        }
    }

    void showAns () {
        for (int i = n-1; i >= 0; -- i) {
            if (arr[i]->next != NULL) {
                Book * ptr = arr[i]->next;
                while(ptr != NULL) {
                    printf("%d ", ptr->num);
                    ptr = ptr->next;
                }
                printf("\n");
                break;
            }
        }
    }
};

int main()
{
    int n, num, dest;

    freopen("in", "r", stdin);

    scanf("%d\n", &n);
    Shelf obj(n);

    for (int i = 0; i < n; ++ i) {
        string line;
        getline(cin, line);
        stringstream ss(line);
        while(ss >> num)
            obj.insert(i, num);
    }

    //obj.show();

    for (int i = 1; i < n; ++ i) {
        scanf("%d %d", &num, &dest);
        obj.move(num-1, dest-1);
    }

    obj.showAns();

    fclose(stdin);

    return 0;
}
