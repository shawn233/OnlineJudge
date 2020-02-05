#include <iostream>
#include <cstdio>
#include <string>

using namespace std;

int dist (int x1, int y1, int x2, int y2) {
    int a = min(abs(x1 - x2), abs(y1 - y2));
    return abs(x1 - x2) + abs(y1 - y2) - a;
}

int main () {
    string s, t;
    int sx, sy, tx, ty;
    int dx[] = {1, 0, -1, 1, -1, 1, 0, -1};
    int dy[] = {1, 1, 1, 0, 0, -1, -1, -1};
    string dir[] = {"RU", "U", "LU", "R", "L", "RD", "D", "LD"};
    int min_dist, min_ind;

    cin >> s >> t;

    sx = s[0] - 'a';
    sy = s[1] - '1';
    tx = t[0] - 'a';
    ty = t[1] - '1';

    //printf ("%d %d %d %d %d\n", sx, sy, tx, ty, dist (sx, sy, tx, ty));

    cout << dist (sx, sy, tx, ty) << endl;
    
    int sxx, syy, tmp_dist;
    while (sx != tx || sy != ty) {
        min_dist = 1000;
        min_ind = -1;
        for (int i = 0; i < 8; ++ i) {
            sxx = sx + dx[i];
            syy = sy + dy[i];
            if (sxx < 0 || sxx > 7 || syy < 0 || syy > 7)
                continue; // otherwise some moves will exceed the chessboard
            tmp_dist = dist (sxx, syy, tx, ty);
            if (tmp_dist < min_dist) {
                min_dist = tmp_dist;
                min_ind = i;
            }
        }
        sx += dx[min_ind];
        sy += dy[min_ind];
        cout << dir[min_ind] << endl;
    }

    return 0;
}