#include <iostream>
#include <cstdio>
#include <cstring>
#define MAX 200000

using namespace std;

//use long long int to make sure operation doesn't overflow | spent 30 minutes on this mistake...
int main() {
	long long T[MAX+1], R[MAX+1];
	long long left, right, res, ways, max_res;
	
	freopen("in.txt", "r", stdin);
	
	scanf("%lld %lld", &left, &right);
	
	for(int i = left; i <= right; ++ i)
		T[i] = R[i] = 1;
	
	max_res = 1;
	for (int num = left+1; num <= right; ++ num) {
		res = ways = 1;
		for (int i = 1; i <= 100; ++ i) {
			if(!((100*num)%(100+i))) {
				if(T[(100*num)/(100+i)]+1>res) {
					res = T[(100*num)/(100+i)]+1;
					ways = R[(100*num)/(100+i)];
				} else if(T[(100*num)/(100+i)]+1==res)
					ways += R[(100*num)/(100+i)];
			}
		}
		T[num] = res;
		R[num] = ways;
		max_res = max(max_res, res);
	}
	
	printf("%lld\n", max_res);
	ways = 0;
	for (int i = right; i >= left  ; -- i) {
		if(T[i] == max_res)
			ways += R[i];
	}
	printf("%lld\n", ways);
	
	fclose(stdin);
	
	return 0;
}