#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>

using namespace std;

int index(char c) {
    return (c-'A');
}

int bound(int n, int upper, int lower) {
    n = min(n, upper);
    n = max(n, lower);
    return n;
}

int main() {
    int colors[30];
    char room[110][110];
    int n, m;
    char pres;
    int deltas[3] = {-1, 0, 1};

    //freopen("in.txt", "r", stdin);

    scanf("%d %d %c\n", &n, &m, &pres);

    memset(colors, 0, 30*sizeof(int));

    for (int i = 0; i < n; ++ i) {
        for (int j = 0; j < m; ++ j) {
            scanf("%c", &room[i][j]);
            //cout << room[i][j];
        }
        getchar();
        //cout << endl;
    }

    for (int i = 0; i < n; ++ i) {
        for (int j = 0; j < m; ++ j) {
            if (room[i][j] == pres) {
                for (int di = 0; di < 3; ++ di) {
                    for (int dj = 0; dj < 3; ++ dj) {
                        if (abs(deltas[di]) == abs(deltas[dj])) continue;
                        char ch = room[bound(i+deltas[di], n-1, 0)][bound(j+deltas[dj], m-1, 0)];
                        if (ch != '.' and ch != pres) colors[index(ch)] = 1;
                    }
                }
            }
        }
    }

    int ans = 0;
    for (int i = 0; i < 30; ++ i) ans += colors[i];

    printf("%d\n", ans);

    //fclose(stdin);

    return 0;
}