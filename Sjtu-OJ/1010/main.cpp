#include <iostream>
#include <cstdio>

using namespace std;

int main() {
	int remain = 0, bank = 0, b; //b:badget
	
	freopen("in.txt", "r", stdin);
	
	for (int i = 1; i < 13; ++ i) {
		scanf("%d", &b);
		remain = remain+300-b;
		if(remain < 0) {
			printf("-%d", i);
			return 0;
		}
		bank += (remain / 100);
		remain %= 100;
	}
	
	remain += (bank*120);
	printf("%d", remain);
	
	fclose(stdin);
	
	return 0;
}