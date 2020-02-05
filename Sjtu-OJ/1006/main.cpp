#include <iostream>
#include <cstdio>

using namespace std;

int main() {
	//actually the size should be 1,000,000 | but my computer seems ...
	int arr[100000];
	int res[100000];
	int len,  max_sum;
	
	freopen("in.txt", "r", stdin);
	
	scanf("%d", &len);
	for (int i = 0; i < len; ++ i) 
		scanf("%d", &arr[i]);
	
	res[0] = arr[0];
	max_sum = 0;
	
	//res[i]:the max sum among sequences ended with arr[i]
	for (int i = 1; i < len; ++ i) {
		res[i] = max(arr[i]+arr[i-1], arr[i]+res[i-1]);
		max_sum = max(max_sum, res[i]);
	}
	
	if (max_sum > 0)
		printf("%d\n", max_sum);
	else
		printf("Game Over\n");
	
	fclose(stdin);
	
	return 0;
}
