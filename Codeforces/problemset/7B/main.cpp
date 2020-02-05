#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>

using namespace std;

struct bblock {
    int id, start, end;
    struct bblock * next;

    bblock(int id_, int start_, int end_, struct bblock * ptr=NULL):
        id(id_), start(start_), end(end_), next(ptr) {}
};

typedef struct bblock block; 

int main() {
    int t, m;
    char ch;
    int tmp;
    int id = 1;
    block * ptr;
    bool flag;

    cin >> t >> m;

    block * head = new block(0, 0, 0);
    head->next = new block(0, m, m);

    for (int i = 0; i < t; ++ i) {
        while(getchar()!='\n');
        ch = getchar();
        //printf("[info] %c ", ch);
        switch(ch) {
        case 'a': // alloc
            while (getchar()!=' ');
            scanf("%d", &tmp);
            //printf("%d\n", tmp);
            flag = false; // true if the allocation is successful
            ptr = head;
            while (ptr->next != NULL) {
                int free_space = ptr->next->start - ptr->end;
                if (free_space >= tmp) {
                    ptr->next = new block(id++, ptr->end, ptr->end+tmp, ptr->next);
                    flag = true;
                    printf("%d\n", ptr->next->id);
                    break;
                }
                ptr = ptr->next;
            }
            if (!flag) printf("NULL\n");
            break;
        case 'e': // erase
            while (getchar()!=' ');
            scanf("%d", &tmp);
            //printf("%d\n", tmp);
            flag = false; // true if erase is successful
            ptr = head;
            while (ptr->next->next != NULL) {
                if (ptr->next->id == tmp) { // delete block ptr->next
                    block * ptr_tmp = ptr->next;
                    ptr->next = ptr_tmp->next;
                    delete ptr_tmp;
                    flag = true;
                    break;
                }
                ptr = ptr->next;
            }
            if (!flag) printf("ILLEGAL_ERASE_ARGUMENT\n");
            break;
        case 'd': // defragment
            //printf("\n");
            ptr = head;
            while (ptr->next->next != NULL) { // loop stops at the last but one block
                ptr->next->end = ptr->end + ptr->next->end - ptr->next->start;
                ptr->next->start = ptr->end;
                ptr = ptr->next;
            }
            break;
        }
    }

    ptr = head;
    block * prev = NULL;
    while (ptr != NULL) {
        //printf("%d %d %d\n", ptr->id, ptr->start, ptr->end);
        prev = ptr;
        ptr = ptr->next;
        delete prev;
    }

    return 0;
}
