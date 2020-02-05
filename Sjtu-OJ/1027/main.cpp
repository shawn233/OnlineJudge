#include <iostream>
#include <cstdio>

using namespace std;

struct Plane {
    int arv,   //t_i
        a2b,   //delta a->b
        fly,   //delta a
        ind;
    Plane * next;

    Plane(int arrive, int atob, int refly_time, int i):
        arv(arrive), a2b(atob), fly(refly_time), ind(i), next(NULL) {}
    void refly() {arv += fly; next = NULL;}
};


struct PlaneQueue {
    Plane * head, * last;
    int ground, tb;

    PlaneQueue(int dtb):tb(dtb), ground(-dtb) {
        last = head = new Plane(0, 0, 0, 0);
    }

    ~PlaneQueue() {
        Plane * ptr = head->next, *tmp;
        while (ptr != NULL) {
            tmp = ptr->next;
            delete ptr;
            ptr = tmp;
        }
        delete head;
    }

    void in(int arrive, int atob, int refly_time, int i) {
        Plane * ptr = new Plane(arrive, atob, refly_time, i);
        if (last->arv>arrive)
            reflyin(ptr);
        else {
            last->next = ptr;
            last = ptr;
        }
    }

    Plane * front() {
        return head->next;
    }

    bool pop() {
        if(head->next == NULL)
            return false;
        Plane * tmp = head->next->next;
        head->next =  tmp;
        if(head->next == NULL)
            last = head;
        return true;
    }

    bool empty() {
        return (head->next == NULL);
    }

    void reflyin(Plane * ptr) {
        Plane * tmp = head->next;
        Plane * prev = head;
        while (tmp!=NULL && tmp->arv<=ptr->arv) {
            prev = tmp;
            tmp = tmp->next;
        }
        ptr->next = tmp;
        prev->next = ptr;
        if(last->next != NULL)
            last = last->next;
    }

    bool canground(Plane * ptr) {
        return (ptr->arv+ptr->a2b-tb>=ground);
    }

    bool exceed(int num) {
        return ground>num;
    }

    void groundplane(Plane * ptr) {
        ground = ptr->arv+ptr->a2b;
    }
};

int main()
{
    Plane * tmp1, * tmp2;
    int N, Max, S, arrive, atob, refly_time;
    int ground_record[2000]; //max(N) = 1000

    //input
    freopen("in", "r", stdin);
    scanf("%d %d %d", &N, & Max, &S);

    PlaneQueue q(S);
    for (int itr = 0; itr < N; ++ itr) {
        scanf("%d %d %d", &arrive, &atob, &refly_time);
        q.in(arrive, atob, refly_time, itr);
    }

    while (!q.empty()) {
        tmp1 = q.front();
        q.pop();

        if(tmp1->arv>Max) {
            printf("GO DATING\n");
            return 0;
        }

        if(!q.empty()) {
            tmp2 = q.front();
            if (tmp1->arv == tmp2->arv) {
                printf("CHANGE BOYFRIEND\n");
                return 0;
            }
        }

        if (q.canground(tmp1)) {
            q.groundplane(tmp1);
            ground_record[tmp1->ind] = q.ground;
            delete tmp1;
        } else {
            tmp1->refly();
            q.reflyin(tmp1);
            //cout << "REFLY! | " << tmp1->ind << endl;
        }
    }

    for (int i = 0; i < N; ++ i) {
        printf("%d\n", ground_record[i]);
    }

    fclose(stdin);
    return 0;
}
