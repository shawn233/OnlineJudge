#include<iostream>
#include<cstdio>
#include<cstdlib>

using namespace std;

int main() {
    int edges[4];
    bool triangle, segment;
    triangle = segment = false;

    for (int i = 0; i < 4; ++ i)
        cin >> edges[i];

    for (int i1 = 0; i1 < 4; ++ i1) {
        for (int i2 = (i1+1)%4; i2 != i1; i2 = (i2+1)%4) {
            for (int i3 = (i1+1)%4; i3 != i1; i3 = (i3+1)%4) {
                if (i2 == i3) continue;
                //printf("i1:%d i2:%d i3:%d\n", i1, i2, i3);
                int sum = edges[i1] + edges[i2];
                int dif = abs(edges[i1] - edges[i2]);
                if (sum > edges[i3] && dif < edges[i3]) {
                    triangle = true;
                    break;
                } else if (sum == edges[i3]) {
                    segment = true;
                }
            }
            if (triangle) break;
        }
        if (triangle) break;
    }

    if (triangle) {
        printf("TRIANGLE\n");
    } else if (segment) {
        printf("SEGMENT\n");
    } else {
        printf("IMPOSSIBLE\n");
    }

    return 0;
}