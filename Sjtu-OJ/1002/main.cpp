#include <iostream>
#include <cstdio>

using namespace std;

int main () {
	int L, W, t, a, b, res;
	int s[100][100];
	//int s[1000][1000];
	
	freopen("in.txt", "r", stdin);
	
	scanf("%d %d", &L, &W);
	
	scanf("%d", &t);
	s[0][0] = t;
	
	for(int i = 1; i < W; ++ i) {
		scanf("%d", &t);
		s[0][i] = t+s[0][i-1];
	}
	
	for (int i = 1; i < L; ++ i) {
		for (int j = 0; j < W; ++ j) {
			scanf("%d", &t);
			if(j == 0) 
				s[i][0] = t+s[i-1][0];
			else 
				s[i][j] = t+s[i-1][j]+s[i][j-1]-s[i-1][j-1];
		}
	}
	
	scanf("%d %d", &a, &b);
	
	res = 0;
	
	for (int i = a-1; i < L; ++ i) {
		for (int j = b-1; j < W; ++ j) {
			int tmp = s[i][j];
			if(i != (a-1))
				tmp -= s[i-a][j];
			if(j != (b-1))
				tmp -= s[i][j-b];
			if(i != (a-1) && j!= (b-1))
				tmp += s[i-a][j-b];
			res = max(res, tmp);
		}
	}
	
	printf("%d\n", res);
	
	fclose(stdin);
	
	return 0;
}