#include <iostream>
#include <cstdio>
#define MAX 100000

using namespace std;

int get_min(long long * c) {
    int res = c[0];
    if (c[1] < res)
        res = c[1];
    if (c[2] < res)
        res = c[2];
    return res;
}

int choose_id (long long * c) {
    int m = get_min(c);
    for (int i = 0; i < 3; ++ i) {
        if (c[i] == m)
            return i;
    }
    cout << "error in choose_id: no minimum" << endl;
    return 0;
}

int get_max(long long * s) {
    int res = s[0];
    if (s[1] > res)
        res = s[1];
    if (s[2] > res )
        res = s[2];
    return res;
}

int main()
{
    long long N, total_wait, end_time, total_wait_new, end_time_new, wait_time_new;
    long long c[3], d[3], s[3];
    long long a[MAX];

    freopen("in.txt", "r", stdin);

    cin >> N;
    for (int i = 0; i < N; ++ i) {
        cin >> a[i];
    }

    //input test
    /*
    cout << "N -- " << N << endl;
    for (int i = 0; i < N; ++ i)
        cout << a[i] << " ";
    cout << endl;*/

    d[0] = d[1] = d[2] = c[0] = c[1] = c[2] = s[0] = s[1] = s[2] = total_wait_new = wait_time_new = total_wait = 0;
    for (int i = 0; i < N; ++ i) {
        int id = choose_id(c); //choose one from three
        //cout << "id -- " << id << endl;
        ++ c[id];
        total_wait += s[id];
        s[id] += a[i];

        id = choose_id(d);
        wait_time_new += d[id];
        total_wait_new += wait_time_new;
        int dif = d[id];
        for (int j = 0; j < 3; ++ j) {
            d[j] -= dif;
        }
        d[id] += a[i];
    }

    end_time = get_max(s);
    end_time_new = wait_time_new + get_max(d);

    cout << total_wait << " " << end_time << endl << total_wait_new << " " << end_time_new << endl;

    fclose(stdin);

    return 0;
}
