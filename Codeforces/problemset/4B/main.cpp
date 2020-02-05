#include <iostream>
#define MAX_D 31

using namespace std;

int main () {
    int d, sum_time;
    int max_t[MAX_D], min_t[MAX_D];
    int sum_min, sum_max;
    sum_max = sum_min = 0;

    cin >> d >> sum_time;
    for (int i = 0;i < d; ++i) {
        cin >> min_t[i] >> max_t[i];
        sum_min += min_t[i];
        sum_max += max_t[i];
    }
    
    if (sum_min > sum_time || sum_max < sum_time) {
        cout << "NO" << endl;
        return 0;
    }

    cout << "YES" << endl;

    sum_time -= sum_min;
    int dif;
    for (int i = 0; i < d; ++ i) {
        dif = min(max_t[i] - min_t[i], sum_time);
        cout << min_t[i] + dif << " ";
        sum_time -= dif;
    }

    cout << endl;
    return 0;
}