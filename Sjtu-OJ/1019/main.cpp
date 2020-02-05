#include <iostream>
#include <string>
#include <cstdio>

using namespace std;

int main () {
	string str;
	int st = 0, N;
	
	scanf("%d", &N);
	for (int i = 0; i < N; ++ i) {
		cin >> str;
		st = 0;
		for (char ch: str) {
			if (ch == '(') {
				st += 1;
			} else {
				if(st == 0) {
					st = 1;
					break;
				}
				else
					st -= 1;
			}
		}
		if(st == 0)
			printf("YES\n");
		else
			printf("NO\n");
	}
	
	return 0;
}