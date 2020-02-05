#include <iostream>
#include <cstdio>
#define MAX 50010

using namespace std;

struct Cow {
    int pos, height;
    Cow (int p=0, int h=0): pos(p), height(h) {}
};

bool operator < (const Cow & c1, const Cow & c2) {
    return (c1.height < c2.height);
}

ostream & operator << (ostream & os, const Cow & obj) {
    os << "A cow with height " << obj.height << " at position " << obj.pos;
    return os;
}

int main()
{
    int N, D, pos, height;
    Cow cows[MAX];
    int ans = 0, tmp, lim;
    bool flag_r, flag_l;

    scanf("%d %d", &N, &D);

    for (int i = 0; i < N; ++ i) {
        scanf("%d %d", &pos, &height);
        cows[i].pos = pos;
        cows[i].height = height;
    }

    return 0;

    /**
    // N^2 method, time limited exceeded
    for (int i = 0; i < N; ++ i) {
        flag_l = flag_r = false;
        lim = 2 * cows[i].height;
        for (int j = 0; j < N; ++ j) {
            if (cows[j].height >= lim) {
                tmp = cows[i].pos - cows[j].pos;
                if (tmp > 0 && tmp <= D) {
                    flag_r = true;
                } else if (tmp < 0 && -tmp <= D) {
                    flag_l = true;
                }
                if (flag_l && flag_r)
                    break;
            }
        }
        if (flag_l && flag_r)
            ++ ans;
    }

    printf("%d\n", ans);

    return 0;
    **/
}
