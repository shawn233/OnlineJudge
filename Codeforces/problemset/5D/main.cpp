#include<iostream>
#include<cstdio>
#include<cmath>

using namespace std;

int main() {
    double a, v, l, d, w;
    double t_1, t_2;
    cin >> a >> v;
    cin >> l >> d >> w;


    // stage 1: before speed limit sign
    double v_1 = sqrt(2*a*d);
    double v_0; // initial speed for stage 1
    if (v_1 <= min(v, w)) {
        t_1 = v_1 / a;
        v_0 = v_1;
    } else {
        double v_m = sqrt((2*a*d+w*w)/2.0);
        //cout << "v_m:" << v_m << endl;
        if (v_m <= v) {
            t_1 = (2*v_m - w)/a;
        } else {
            w = min(w, v);
            t_1 = (2*v-w)/a + d/v - (2*v*v-w*w) / (2*a*v);
        }
        v_0 = w;
    }
    //cout << "[stage 1] v_1:" << v_1 << " t_1:" << t_1 << endl;

    // stage 2: after speed limit sign
    v_1 = sqrt(2*a*(l-d) + v_0*v_0);
    if (v_1 <= v) {
        t_2 = (v_1 - v_0) / a;
    } else {
        t_2 = (v - v_0) / a + (l-d-(v*v-v_0*v_0)/(2*a))/v;
    }
    //cout << "[stage 2] v_1:" << v_1 << " t_2:" << t_2 << endl;

    printf("%f\n", t_1+t_2);

    return 0;
}