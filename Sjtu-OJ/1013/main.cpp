#include <iostream>
#include <cstdio>

using namespace std;

int main() {
	int T[10001], weight[1000], value[1000];
	int V, N, res;
	
	freopen("in.txt", "r", stdin);
	
	scanf("%d %d", &V, &N);
	for (int i = 0; i < N; ++ i)
		scanf("%d %d", &weight[i], &value[i]);
	
	T[0] = 0;
	for (int t = 1; t <= V; ++ t) {
		res = 0;
		for(int i = 0; i < N; ++ i) {
			if(t-weight[i]>=0)
				res = max(res, T[t-weight[i]]+value[i]);
		}
		T[t] = res;
	}
	
	printf("%d", T[V]);
	
	fclose(stdin);
	
	return 0;
}