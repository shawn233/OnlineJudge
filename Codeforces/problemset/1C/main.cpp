#include <iostream>
#include <cstdio>
#include <cmath>
#include <iomanip>
 
#ifndef M_PI
    #define M_PI 3.14159265358979323846
#endif
 
using namespace std;
 
long double dist (long double x1, long double y1, long double x2, long double y2) {
    long double res;
 
    res = sqrt ((x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2));
    return res; 
}
 
long double dist_with_mid (long double xc, long double yc, long double x1, 
                            long double y1, long double x2, long double y2) {
    long double xm, ym;
 
    xm = (x1 + x2) / 2;
    ym = (y1 + y2) / 2;
    
    return dist (xc, yc, xm, ym);
}
 
long double get_ang (long double d, long double l) {
    return 360 * atan (l/(2*d)) / M_PI;
}
 
/*
int round (long double x) {
    int x_floor = floor (x);
 
    if (x - x_floor < 0.5) {
        return x_floor;
    } else {
        return ceil (x);
    }
}
*/
 
bool is_small_dif (long double x) {
    int r_x = round (x);
    //cout << "x -- " << x << " round_x -- " << r_x << endl;
    if (abs(x - r_x) < 0.00001) {
        return true;
    } else {
        return false;
    }
}
 
void exocenter (long double & xc, long double & yc,
                long double x1, long double y1,
                long double x2, long double y2,
                long double x3, long double y3) {
    long double a1, b1, c1, a2, b2, c2;
    a1 = 2 * (x2 - x1);
    b1 = 2 * (y2 - y1);
    c1 = x2 * x2 + y2 * y2 - x1 * x1 - y1 * y1;
    a2 = 2 * (x3 - x2);
    b2 = 2 * (y3 - y2);
    c2 = x3 * x3 + y3 * y3 - x2 * x2 - y2 * y2;
 
    xc = ((c1 * b2) - (c2 * b1)) / ((a1 * b2) - (a2 * b1));
    yc = ((a1 * c2) - (a2 * c1)) / ((a1 * b2) - (a2 * b1));
} 

int main () {
    long double x1, y1, x2, y2, x3, y3;
    long double xc, yc;
    long double l1, l2, l3, d1, d2, d3;
    long double ang1, ang2, ang3;
    int n_ang;
    
    cin >> x1 >> y1 >> x2 >> y2 >> x3 >> y3;
 
    exocenter (xc, yc, x1, y1, x2, y2, x3, y3);
 
    //cout << " xc -- " << xc << " yc -- " << yc << " " << dist (xc, yc, x1, y1) << " " << dist (xc, yc, x2, y2) <<
    //        " " << dist (xc, yc, x3, y3) << endl;
 
    l1 = dist (x1, y1, x2, y2);
    l2 = dist (x2, y2, x3, y3);
    l3 = dist (x3, y3, x1, y1);
 
    d1 = dist_with_mid (xc, yc, x1, y1, x2, y2);
    d2 = dist_with_mid (xc, yc, x2, y2, x3, y3);
    d3 = dist_with_mid (xc, yc, x3, y3, x1, y1);
 
    ang1 = get_ang (d1, l1);
    ang2 = get_ang (d2, l2);
    ang3 = get_ang (d3, l3);
 
    //cout << "ang1 -- " << ang1 << " ang2 -- " << ang2 << " ang3 -- " << ang3 << endl;
 
    bool flag;
    long double ang;
    for (n_ang = 3; n_ang < 101; ++ n_ang) {
        ang = (long double) 360 / n_ang;
        //cout << "n_ang -- " << n_ang << endl;
        flag = is_small_dif (ang1 / ang) && is_small_dif (ang2 / ang) && is_small_dif (ang3 / ang);
        if (flag) {
            break;
        }
    }
 
    //cout << "n_ang = " << n_ang << endl;
 
    if (n_ang == 101) {
        cout << "[error] no polygon" << endl;
    } else {
        long double l = dist (xc, yc, x1, y1);
        long double res = 0.5 * l * l * sin (ang*M_PI / 180) * n_ang;
        cout << fixed << setprecision (6) << res << endl;
    }
 
    return 0;
}
